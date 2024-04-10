#pragma once
#ifndef ISPATIAL_DATA_STRUCTURE_ITEM_H
#define ISPATIAL_DATA_STRUCTURE_ITEM_H

#include "../World/SpatialEntities/Particles/Particle.h"	// [TODO] :: CHANGE TO PARENT TYPE
#include <iostream>

//////
// - The idea is to add an additional layer of abstraction to the items of the Spatial Data Structure (SDS).
// - For example, while each SDS will have a particle, only the items specific to the SHG SDS need to contain
//   variables related to it like 'indexPos'. 
// 
// - 
// 
////////

struct ISpatialDataStructureItem
{

public:
	int				m_SDSItemID;
	Vec2f		    m_posInSpace;
	Particle* m_spatialEntityRef;

	int			    GetItemID()			     const { return m_SDSItemID; }
	Vec2f		    GetItemPositionInSpace() const { return m_posInSpace; }
	Particle* GetSpatialEntityPtr()          const { return m_spatialEntityRef; }

	void SetSpatialEntityPtr(Particle* _spatialEntityPtr) { m_spatialEntityRef = _spatialEntityPtr; }
};

#endif 
