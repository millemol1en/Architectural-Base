#pragma once
#ifndef ISPATIAL_DATA_STRUCTURE_H
#define ISPATIAL_DATA_STRUCTURE_H

#include "./ISpatialDataStructureItem.h"
#include "../../View/Graphics.h"
#include "../Constants/CONST_SDS_ENTITY_TYPE.h"
#include "../../View/TransformedView.h"
#include "../Util/BoundingBox.h"
#include "../World/SpatialEntities/Particles/Particle.h"	// [TODO] :: CHANGE TO PARENT TYPE

using EntityList = std::vector<ISpatialEntity*>;

struct ISpatialDataStructure
{

public:
	BoundingBox2D hlComp;

	virtual SDS_TYPE		GetSDSType() const = 0;
	virtual EntityList		QueryNearestNeighbour(ISpatialEntity* _targetEntity) = 0;
	virtual EntityList		QueryNearestNeighbourUsingMouse(const Vec2f& _mosPos) = 0;
	virtual ISpatialEntity* QueryForSpecificEntityUsingMouse(const Vec2f& _mosPos) const = 0;


	virtual void Insert(ISpatialEntity* _spatialEntityPtr) const = 0;
	virtual void Update(ISpatialEntity* _spatialEntityPtr) const = 0;
	virtual void Delete(ISpatialEntity* _spatialEntityPtr) const = 0;
	virtual void Destroy() const = 0;
	virtual void DrawSDS(TransformedView* ptr_tvRef) const = 0;

};

#endif 
