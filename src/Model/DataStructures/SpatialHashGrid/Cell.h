#pragma once
#ifndef CELL_H
#define CELL_H

#include <cstdint>
#include <vector>
#include "../../World/Particle.h"

struct Cell
{
	uint32_t m_cellGridIndex;	// Position in 1D index --- Maybe not necessary (at least, it isn't being used currently)
	int m_cellID;				// Cell number

	std::vector<Particle*> m_particlesInCell;

	Cell(int _cellID);
	~Cell() = default;

	void Insert(Particle* _newItem);
	void Remove(Particle* _remItem);
	std::vector<Particle*> GetItems();
};


#endif