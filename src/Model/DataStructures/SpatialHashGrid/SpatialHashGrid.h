#pragma once
#ifndef SPATIAL_HASH_GRID_H
#define SPATIAL_HASH_GRID_H

#include "../ISpatialDataStructure.h"
#include "Cell.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <list>

struct DenseSHG
{
	// ... Matthias Muller algo ... it must be ...
	// https://github.com/matthias-research/pages/blob/master/tenMinutePhysics/11-hashing.html
};




////////////////////////////////////
//	- The space to be sliced up is assumbed to be BOUNDED.
//  - Furthermore, the grid dimensions relies on a "power-of-two" size, meaning both X and Y need to be a number which is a power of 2 # Example 1024 - 2^10
//	- 
//	- 
//	- 
//  - 
////////////////////////////////////

struct SpatialHashGrid : public ISpatialDataStructure
{
private:
	int m_numRows, m_numCols, m_gridSize; // Grid info
	int m_cellSize;	
	int m_globalQueryID;
	std::vector<Cell*> grid;

	BoundingBox2D gridDimensions;


public:
	bool devSnapShot = false;

	//////////////////////////
	//						//
	//	INHERITED METHODS	//
	//						//
	//////////////////////////
	void Destroy()								const override;
	void DrawSDS(TransformedView* _ptr_tvRef)	const override;
	SDS_TYPE GetSDSType()						const override;

	void Update(ISpatialEntity* _spatialEntity) const override;
	void Insert(ISpatialEntity* _spatialEntity) const override;
	void Delete(ISpatialEntity* _spatialEntity) const override;
	std::vector<ISpatialEntity*> QueryNearestNeighbour(ISpatialEntity* _targetEntity) override;
	ISpatialEntity*				 QueryForSpecificEntityUsingMouse(const Vec2f& _mosPos) const override;
	std::vector<ISpatialEntity*> QueryNearestNeighbourUsingMouse(const Vec2f& _mosPos) override;

	//////////////////////////
	//						//
	//	   LOCAL METHODS	//
	//						//
	//////////////////////////
	SpatialHashGrid() = default;
	SpatialHashGrid(BoundingBox2D _dimensions, int _cellSize, int _maxNumObj);
	~SpatialHashGrid();

	Vec2i	 ConvertPosToIndex(const Vec2f& point) const;
	Vec2i	 ConvertIndexToPos(const int xi, const int yi) const;
	uint32_t GetGridIndex(const int xi, const int yi) const;
	Cell*    GetCell(const uint32_t index) const;
	Cell*    GetCell(const Vec2f pos) const;

	int GetNumCols();
	int GetNumRows();
	int GetGridHeight();
	int GetGridWidth();

	void DDALineToGrid(); // https://github.com/DoctorB/spatial-hash/blob/master/SpatialHash.cs#L48

};


#endif