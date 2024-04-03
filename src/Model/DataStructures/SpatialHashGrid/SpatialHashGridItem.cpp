#include "SpatialHashGridItem.h"

// LOCAL:
SpatialHashGridItem::SpatialHashGridItem(int _itemID, Particle* _spatialEntityPtr) : m_gridIndex(-1), m_indexPosInCell(-1), m_queryID(-1)
{
	m_SDSItemID     = _itemID;
	m_posInSpace	= _spatialEntityPtr->m_pos;
	m_spatialEntityRef = _spatialEntityPtr;
}

void SpatialHashGridItem::SetItemGridIndex(const int _newIndex) { m_gridIndex = _newIndex; }
void SpatialHashGridItem::SetItemPosInCell(const int _newPos) { m_indexPosInCell = _newPos; }
void SpatialHashGridItem::SetQueryID(const int _newQueryID) { m_queryID = _newQueryID;  }

int   SpatialHashGridItem::GetItemGridIndex() const				 { return m_gridIndex;					}
int   SpatialHashGridItem::GetItemPosInCell() const				 { return m_indexPosInCell;				}
int   SpatialHashGridItem::GetQueryID()		 const				 { return m_queryID;					}
bool  SpatialHashGridItem::IsQueryIDAccepted(const int _queryID) { return (_queryID != m_queryID);		}

bool SpatialHashGridItem::operator==(const SpatialHashGridItem& _otherSHGItem) const
{
	return (this->GetItemID() == _otherSHGItem.GetItemID());
}
