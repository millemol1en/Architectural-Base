#pragma once
#ifndef SPATIAL_HASH_GRID_H
#define SPATIAL_HASH_GRID_H

#include "../ISpatialDataStructure.h"
#include "Cell.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>

struct DenseSpatialHashGrid : public ISpatialDataStructure
{
private:
	int m_numRows, m_numCols, m_numCells, m_tableSize, m_cellSize;	// SHG essentials
	int m_globalQueryID;
	std::vector<Cell*> grid;										// A 2-Dimensional array

	BoundingBox2D gridDimensions;

	bool devSnapShot = false;

	//////////////////////////
	//						//
	//	INHERITED METHODS	//
	//						//
	//////////////////////////
	void Destroy() const override;
	void DrawSDS(TransformedView* ptr_tvRef) const override;
	SDS_TYPE GetSDSType() const override;

	void Update(ISpatialEntity* _spatialEntity) const override;
	void Insert(ISpatialEntity* _spatialEntity) const override;
	void Delete(ISpatialEntity* _spatialEntity) const override;
	std::vector<ISpatialEntity*> QueryNearestNeighbour(ISpatialEntity* _targetEntity) override;
	ISpatialEntity* QueryForSpecificEntityUsingMouse(const Vec2f& _mosPos) const override;
	std::vector<ISpatialEntity*> QueryNearestNeighbourUsingMouse(const Vec2f& _mosPos) override;


	//////////////////////////
	//						//
	//	   LOCAL METHODS	//
	//						//
	//////////////////////////

	DenseSpatialHashGrid() = default;
	DenseSpatialHashGrid(BoundingBox2D _dimensions, int _cellSize, int _maxNumObj);
	~DenseSpatialHashGrid();

	Vec2i	 ConvertPosToIndex(const Vec2f& point) const;
	Vec2i	 ConvertIndexToPos(const int xi, const int yi) const;
	uint32_t GetGridIndex(const int xi, const int yi) const;
	Cell* GetCell(const uint32_t index) const;
	Cell* GetCell(const Vec2f pos) const;

	int GetNumCols();
	int GetNumRows();
	int GetGridHeight();
	int GetGridWidth();
	int GetCellIndex(const Vec2f pos);
};




struct SpatialHashGrid : public ISpatialDataStructure
{
private:
	int m_numRows, m_numCols, m_numCells, m_tableSize, m_cellSize;	// SHG essentials
	int m_globalQueryID;
	std::vector<Cell*> grid;										// A 2-Dimensional array

	BoundingBox2D gridDimensions;


public:
	bool devSnapShot = false;

	//////////////////////////
	//						//
	//	INHERITED METHODS	//
	//						//
	//////////////////////////
	void Destroy() const override;
	void DrawSDS(TransformedView* ptr_tvRef) const override;
	SDS_TYPE GetSDSType() const override;

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

	// [TODO] Tidy up this as well as the names and potentially oversaturated arguments.

};


#endif