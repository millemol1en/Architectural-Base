#include "SpatialHashGrid.h"
//////////////////////////
//						//
//	   LOCAL METHODS	//
//						//
//////////////////////////
SpatialHashGrid::SpatialHashGrid(BoundingBox2D _dimensions, int _cellSize, int maxNumObj) : m_globalQueryID(-1)
{
	gridDimensions = {
		_dimensions.m_minX,
		_dimensions.m_minY,
		_dimensions.m_maxX,
		_dimensions.m_maxY
	};
	m_cellSize = _cellSize;
	m_numRows = std::ceil(_dimensions.m_maxY / _cellSize);
	m_numCols = std::ceil(_dimensions.m_maxX / _cellSize);
	m_tableSize = (m_numRows * m_numCols) + 1;

	grid = std::vector<Cell*>(m_tableSize);

	for (int i = 0; i < grid.size(); i++)
	{
		grid[i] = new Cell(i);
	}

	std::cout << "!====Spatial Hash Grid (SHG) Initialization Information====!\n";
	std::cout << "   - Grid Dimesnions	:: " << "\n"
			  << "      - Top Left	 = (" << gridDimensions.m_minX << ", " << gridDimensions.m_minY << "\n"
			  << "      - Bottom Right = (" << gridDimensions.m_maxX << ", " << gridDimensions.m_maxY << "\n";
	std::cout << "   - Table Size		:: " << m_tableSize << "\n";
	std::cout << "   - Cell Size		:: " << m_cellSize << "\n";
	std::cout << "   - Num. Cols		:: " << m_numCols << "\n";
	std::cout << "   - Num. Rows		:: " << m_numRows << "\n";
}

SpatialHashGrid::~SpatialHashGrid()
{
	for (Cell* cell : grid)
	{
		delete cell;
	}
}

// Converts a particles X and Y position in space, into an index.
Vec2i SpatialHashGrid::ConvertPosToIndex(const Vec2f& particlePoint) const
{
	// Dividing the position of the particle by the cell size gives us a position in the cell grid:
	int xIndex = std::floor(particlePoint.x / m_cellSize);
	int yIndex = std::floor(particlePoint.y / m_cellSize);

	return { xIndex, yIndex };
}

// Converts an index position to an approximate value in space.
Vec2i SpatialHashGrid::ConvertIndexToPos(const int _xi, const int _yi) const
{
	int xIndex = std::floor(_xi * m_cellSize);
	int yIndex = std::floor(_yi * m_cellSize);

	return { xIndex, yIndex };
}

// Takes the returned input from "ConvertPosToIndex" and returns the associated grid index:
uint32_t SpatialHashGrid::GetGridIndex(const int _xi, const int _yi) const
{
	return static_cast<uint32_t>(_yi * m_numCols + _xi); // Formula :: index = (xi * height + yi) OR (yi * width + xi)
}

// Takes the returned input from "GetGridIndex" and returns the associated Cell:
Cell* SpatialHashGrid::GetCell(const uint32_t _index) const
{
	return grid[_index];
}

Cell* SpatialHashGrid::GetCell(const Vec2f _pos) const
{
	const Vec2i posToIndex = ConvertPosToIndex(_pos);
	const uint32_t gridIndex = GetGridIndex(posToIndex.x, posToIndex.y);
	return GetCell(gridIndex);
}

int SpatialHashGrid::GetNumCols()
{
	return m_numCols;
}

int SpatialHashGrid::GetNumRows()
{
	return m_numRows;
}

int SpatialHashGrid::GetGridWidth()
{
	return gridDimensions.m_maxX;
}

int SpatialHashGrid::GetGridHeight()
{
	return gridDimensions.m_maxY;
}



//////////////////////////
//						//
//	INHERITED METHODS	//
//						//
//////////////////////////
void SpatialHashGrid::Insert(ISpatialEntity* _newEntity) const
{
	const Vec2i particleIndexPos = ConvertPosToIndex(_newEntity->m_pos);
	const uint32_t indexInGrid = GetGridIndex(particleIndexPos.x, particleIndexPos.y);

	_newEntity->m_gridIndex = indexInGrid; // Change name to be more fitting...


	Cell* targetCell = grid[indexInGrid];
	targetCell->Insert(_newEntity);

	if (_newEntity->m_ID == 0) std::cout << "Target Entity inserted into Cell :: " << targetCell->m_cellID << "\n";
}


void SpatialHashGrid::Delete(ISpatialEntity* _targetEntity) const
{
	const uint32_t storedIndexInGrid = _targetEntity->m_gridIndex;

	Cell* targetCell = grid[storedIndexInGrid];
	targetCell->Remove(_targetEntity);

	if (_targetEntity->m_ID == 0) std::cout << "Target Entity removed from Cell :: " << targetCell->m_cellID << "\n";
}


void SpatialHashGrid::Update(ISpatialEntity* _targetEntity) const
{
	// Actual index:
	const Vec2i actualIndexPos = ConvertPosToIndex(_targetEntity->m_pos);
	const uint32_t actualIndexInGrid = GetGridIndex(actualIndexPos.x, actualIndexPos.y);

	// Stored index:
	const uint32_t storedIndexInGrid = _targetEntity->m_gridIndex;

	if (actualIndexInGrid == storedIndexInGrid) return;

	Delete(_targetEntity);
	Insert(_targetEntity);
}


ISpatialEntity* SpatialHashGrid::QueryForSpecificEntityUsingMouse(const Vec2f& _mosPos) const
{	
	const Vec2i    posToIndex = ConvertPosToIndex(_mosPos);
	const uint32_t gridIndex = GetGridIndex(posToIndex.x, posToIndex.y);
	const Cell* targetCell = GetCell(gridIndex);

	for (ISpatialEntity* currEntity : targetCell->m_entitiesInCell)
	{
		switch (currEntity->GetEntityType())
		{
			case ENTITY_TYPE::PARTICLE:

				Particle* particle = (Particle*)currEntity;

				if (particle->IsPointInParticle(_mosPos))
				{
					return particle;
				}

				break;

			//case ENTITY_TYPE::BOID:

			//	// Perform nearest neighbor using simple euclidean distancing...
			//	// This is a narrow phase step and isn't going to be constly...

			//	break;
		}
	}

	return nullptr;
}

std::vector<ISpatialEntity*> SpatialHashGrid::QueryNearestNeighbourUsingMouse(const Vec2f& _mosPos)
{
	std::vector<ISpatialEntity*> locatedEntities;

	const Vec2i    posToIndex = ConvertPosToIndex(_mosPos);
	const uint32_t gridIndex = GetGridIndex(posToIndex.x, posToIndex.y);
	const Cell* targetCell = GetCell(gridIndex);

	for (int dx = -1; dx <= 1; ++dx)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			int currX = std::max(0, std::min((posToIndex.x + dx), m_numCols - 1));
			int currY = std::max(0, std::min((posToIndex.y + dy), m_numRows - 1));

			const uint32_t currCellIndex = GetGridIndex(currX, currY);

			Cell* currCell = GetCell(currCellIndex);

			if (grid.size() >= currCellIndex && !currCell->GetItems().empty())
			{
				for (ISpatialEntity* currEntity : currCell->GetItems())
				{
					locatedEntities.push_back(currEntity);
				}
			}
		}
	}


	return locatedEntities;
}

std::vector<ISpatialEntity*> SpatialHashGrid::QueryNearestNeighbour(ISpatialEntity* _targetParticle)
{
	std::vector<ISpatialEntity*> locatedItems;

	const Vec2i targetPIndices = ConvertPosToIndex(_targetParticle->m_pos);

	const int localQueryID = m_globalQueryID++;
	_targetParticle->m_queryID = localQueryID;		// Prevents the addition of the '_targetSHGItem's particle ptr.

	for (int dx = -1; dx <= 1; ++dx)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			int currX = std::max(0, std::min((targetPIndices.x + dx), m_numCols - 1));
			int currY = std::max(0, std::min((targetPIndices.y + dy), m_numRows - 1));

			const uint32_t currCellIndex = GetGridIndex(currX, currY);

			///////////////////////////DRAW SQUARES///////////////////////////
			// Vec2i squarePos = ConvertIndexToPos(currX, currY);
			// Graphics::DrawBoundingBox(squarePos.x, squarePos.y, squarePos.x + m_cellSize, squarePos.y + m_cellSize, 1, 0xFF77FF33);
			//////////////////////////////////////////////////////////////////
			// A consideration was to have each Spatial Entity have an additional set of attributes associated
			// with it, depending on the type of SDS used. 
			// In the situation of drawing the squares, this would be ideal, as we don't want to pass a reference
			// of the TransformedView to this method.
			// 

			Cell* currCell = GetCell(currCellIndex);

			if (grid.size() >= currCellIndex && !currCell->GetItems().empty())
			{
				for (ISpatialEntity* currEntity : currCell->GetItems())
				{
					if (currEntity->m_ID == _targetParticle->m_ID) continue;
					if (currEntity->m_queryID != localQueryID)
					{
						currEntity->m_queryID = localQueryID;
						locatedItems.push_back(currEntity);
					}
				}
			}

		}
	}

	return locatedItems;
}

//////////////////////////
//						//
//	INHERITED METHODS	//
//						//
//////////////////////////

// [7]
void SpatialHashGrid::DrawSDS(TransformedView* ptr_tvRef) const
{
	for (float x = 0; x < gridDimensions.m_maxX; x += m_cellSize)
	{
		if (x <= gridDimensions.m_maxX)
			ptr_tvRef->DrawLine({ x, 0.0f }, { x, gridDimensions.m_maxY }, 1, 0x1088CC80);
	}

	for (float y = 0; y < gridDimensions.m_maxY; y += m_cellSize)
	{
		if (y <= gridDimensions.m_maxY)
			ptr_tvRef->DrawLine({ 0.0f, y }, { gridDimensions.m_maxX, y }, 1, 0x1088CC80);
	}
}

// [8] Destroy the SDS
void SpatialHashGrid::Destroy() const
{
	this->~SpatialHashGrid();
}


SDS_TYPE SpatialHashGrid::GetSDSType() const
{
	return SDS_TYPE::SPATIAL_HASH_GRID;
}

// [TODO] :: Make an OutOfBounds handler:
bool OutOfBounds()
{
	return true;
}