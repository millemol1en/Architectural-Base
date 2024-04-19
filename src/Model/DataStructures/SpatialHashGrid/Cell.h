#pragma once
#ifndef CELL_H
#define CELL_H

#include <cstdint>
#include <vector>
#include "../../World/SpatialEntities/ISpatialEntity.h" 

struct Cell
{
	uint32_t m_cellGridIndex;	// Position in 1D index --- Maybe not necessary (at least, it isn't being used currently)
	int m_cellID;				// Cell number

	std::vector<ISpatialEntity*> m_entitiesInCell;

	Cell(int _cellID);
	~Cell() = default;

	void Insert(ISpatialEntity* _newItem);
	void Remove(ISpatialEntity* _remItem);
	std::vector<ISpatialEntity*> GetItems();
};

#endif