#include "Cell.h"
#include <algorithm>




// TODO ::	DEFINE AN ADDITIONAL I_SPATIAL_DATA_STRUCTURE_ITEM FOR EACH VARYING DS
//			THEN, WE CAN HAVE THAT TAKE A RERFERENCE TO A PARTICLE. 
//			USE THE CLASSIC "PUSH_BACK POP" TECHNIQUE with the world particle std::vector
//			Why is this all caps?



Cell::Cell(int _cellID) : m_cellGridIndex(-1), m_entitiesInCell(std::vector<ISpatialEntity*>())
{
	m_cellID = _cellID;
}

std::vector<ISpatialEntity*> Cell::GetItems()
{
	return m_entitiesInCell;
}

// [0] Push back insertion:
void Cell::Insert(ISpatialEntity* _newSHGItem)
{
	_newSHGItem->m_indexPosInCell = m_entitiesInCell.size();

	m_entitiesInCell.push_back(_newSHGItem);
}

// [1] Swap-Pop removal method - [TESTED? - NO]:
void Cell::Remove(ISpatialEntity* _remSHGItem)
{
	/*auto it = std::find(m_circlesPtr.begin(), m_circlesPtr.end(), remCircle);

	if (it != m_circlesPtr.end())
	{
		m_circlesPtr.erase(it);
	}*/


	if (m_entitiesInCell.size() > 1) {
		std::iter_swap(m_entitiesInCell.begin() + _remSHGItem->m_indexPosInCell, m_entitiesInCell.end() - 1);
		m_entitiesInCell.pop_back();
	}
	else {
		m_entitiesInCell.clear();
	}
}