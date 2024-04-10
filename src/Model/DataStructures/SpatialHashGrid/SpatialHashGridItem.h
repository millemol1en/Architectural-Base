#pragma once
#ifndef SPATIAL_HASH_GRID_ITEM_H
#define SPATIAL_HASH_GRID_ITEM_H

#include "../../World/SpatialEntities/Particles/Particle.h"	// [TODO] :: CHANGE TO PARENT TYPE
#include "../ISpatialDataStructureItem.h"


struct SpatialHashGridItem : public ISpatialDataStructureItem
{

protected:
	int m_gridIndex;
	int m_indexPosInCell;


public:
	int m_queryID; // [TODO] Move this to protected and make Getter / Setter for it

	SpatialHashGridItem(int _itemID = -1, Particle* _particlePtr = nullptr);
	~SpatialHashGridItem() = default;

	void SetItemGridIndex(const int _newIndex);
	void SetItemPosInCell(const int _newPos);
	void SetQueryID(const int _newQueryID);

	bool IsQueryIDAccepted(const int _queryID);
	int  GetQueryID()		const;
	int  GetItemGridIndex() const;
	int  GetItemPosInCell() const;




	// [TODO] Make any operators part of the Interface...
	bool operator == (const SpatialHashGridItem& _otherSHGItem) const;
};


#endif 
