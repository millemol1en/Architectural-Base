#include "Cell.h"
#include <algorithm>




// TODO ::	DEFINE AN ADDITIONAL I_SPATIAL_DATA_STRUCTURE_ITEM FOR EACH VARYING DS
//			THEN, WE CAN HAVE THAT TAKE A RERFERENCE TO A PARTICLE. 
//			USE THE CLASSIC "PUSH_BACK POP" TECHNIQUE with the world particle std::vector
//			Why is this all caps?



Cell::Cell(int _cellID) : m_cellGridIndex(-1), m_particlesInCell(std::vector<Particle*>())
{
	m_cellID = _cellID;
}

std::vector<Particle*> Cell::GetItems()
{
	return m_particlesInCell;
}

void Cell::Insert(Particle* _newSHGItem)
{
	_newSHGItem->m_indexPosInCell = m_particlesInCell.size();

	m_particlesInCell.push_back(_newSHGItem);
}

// Remove utilizes the good ol'Swap-Pop technique
// Have to test this further, make sure it doesn't break
void Cell::Remove(Particle* _remSHGItem)
{
	/*auto it = std::find(m_circlesPtr.begin(), m_circlesPtr.end(), remCircle);

	if (it != m_circlesPtr.end())
	{
		m_circlesPtr.erase(it);
	}*/


	if (m_particlesInCell.size() > 1) {
		std::iter_swap(m_particlesInCell.begin() + _remSHGItem->m_indexPosInCell, m_particlesInCell.end() - 1);
		m_particlesInCell.pop_back();
	}
	else {
		m_particlesInCell.clear();
	}
}