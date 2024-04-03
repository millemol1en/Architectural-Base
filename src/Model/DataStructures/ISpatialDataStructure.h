#pragma once
#ifndef ISPATIAL_DATA_STRUCTURE_H
#define ISPATIAL_DATA_STRUCTURE_H

#include "./ISpatialDataStructureItem.h"
#include "../../View/Graphics.h"
#include "../Constants/CONST_SDS_ENTITY_TYPE.h"
#include "../../View/TransformedView.h"

using EntityList = std::vector<Particle*>;

struct ISpatialDataStructure
{

public:
	BoundingBox2D hlComp;
	// TODO: Add more variables / methods that these share.
	// We start with "Clear()", as in order for the SDS to be swappable, we
	// have to make a destroy function for all SDSs.

	virtual SDS_TYPE	  GetSDSType() const = 0;
	virtual EntityList	  QueryNearestNeighbour(Particle* _targetEntity) = 0;
	virtual Particle*	  QueryForSpecificUsingMouse(const Vec2f& _mosPos) const = 0;
	virtual BoundingBox2D HighlightSDSComponent(const Vec2f& _mosPos) const = 0;


	// MUST HAVE
	virtual void Insert(Particle* _spatialEntityPtr) const = 0;
	virtual void Update(Particle* _spatialEntityPtr) const = 0;
	virtual void Delete(Particle* _spatialEntityPtr) const = 0;
	virtual void Destroy() const = 0;
	virtual void DrawSDS(TransformedView* ptr_tvRef) const = 0;

};

#endif 
