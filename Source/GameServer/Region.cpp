#include "stdafx.h"
#include "Region.h"
#include "User.h"
#include "Npc.h"

void CRegion::Add(CUser * pUser)
{
	if (pUser)
	{
		Guard lock(m_lock);
		m_RegionUserArray.insert(pUser->GetID());
	}
}

void CRegion::Remove(CUser * pUser)
{
	if (pUser)
	{
		Guard lock(m_lock);
		m_RegionUserArray.erase(pUser->GetID());
	}
}

void CRegion::Add(CNpc * pNpc)
{
	Guard lock(m_lock);
	m_RegionNpcArray.insert(pNpc->GetID());
}

void CRegion::Remove(CNpc * pNpc)
{
	Guard lock(m_lock);
	m_RegionNpcArray.erase(pNpc->GetID());
}