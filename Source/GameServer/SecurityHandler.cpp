#include "stdafx.h"
#include "Map.h"
#include "../shared/DateTime.h"
#include <cmath>

void CUser::ItemsDupeDelete()
{
	std::string sNoticeMessage;
	bool iFindItem = false;

	for(int j = 0; j <  INVENTORY_TOTAL; j++)
	{
		if(GetItem(j)->nNum == 0)
			continue;

		std::string strUserID, strAccountID;
		_ITEM_DUPER * pDupers = nullptr;
		
		foreach_stlmap (itr, g_pMain->m_ItemDupersArray)
		{
			pDupers = itr->second;

			if (pDupers->d_ItemID != GetItem(j)->nNum)
				continue;

			if((pDupers->d_Serial ==  (GetItem(j)->nSerialNum)))
			{
				TRACE("Item Deleted pos(%d), ItewmID: %d\n",  j, GetItem(j)->nNum);
				 m_sItemArray[j].nNum = 0;
				 m_sItemArray[j].sCount = 0;
				 m_sItemArray[j].sDuration = 0;
				 m_sItemArray[j].nSerialNum = 0;
				 m_sItemArray[j].bFlag = 0;
				 m_sItemArray[j].sRemainingRentalTime = 0;
				 m_sItemArray[j].nExpirationTime = 0;
				 m_sItemArray[j].IsSelling = false;
				 SendItemMove(2);
				 iFindItem = true;				 
			}
		}
	}

	if(iFindItem)
	{
		sNoticeMessage = string_format("Dupe items were deleted from your inventory : User = %s  .", GetName().c_str());

		if (!sNoticeMessage.empty())
			g_pMain->SendNotice(sNoticeMessage.c_str(),Nation::ALL);
		Disconnect();
	}
}

void CUser::IlegalItemsBanned()
{
	std::string sNoticeMessage;
	bool iFindItem = false;

	for(int e = 0; e <  INVENTORY_TOTAL; e++)
	{
		if(GetItem(e)->nNum == 0)
			continue;

		_ITEM_TABLE	*	pItem= nullptr;
		_ILEGAL_ITEMS * pIlegal = nullptr;
		
		foreach_stlmap (itr, g_pMain->m_IlegalItemsArray)
		{
			pIlegal = itr->second;

			if(!pIlegal)
				continue;

			if (pIlegal->i_ItemID != GetItem(e)->nNum)
				continue;

			if (isGM())
				continue;
			
			if (pIlegal->i_ItemID == GetItem(e)->nNum)
			{	
				pItem= nullptr;

				pItem = g_pMain->m_ItemtableArray.GetData(GetItem(e)->nNum);

				if(!pItem)
					continue;

				sNoticeMessage = string_format("%s have illegal item (%s).", GetName().c_str(), pItem->m_sName.c_str());
				if (!sNoticeMessage.empty())
					g_pMain->SendNotice(sNoticeMessage.c_str(),Nation::ALL);

				g_pMain->WriteCheatLogFile(string_format("%s is currently blocked for item (%s | %d) in illegal activity.\n", GetName().c_str(), pItem->m_sName.c_str(), pItem->m_iNum));
				iFindItem = true;
			}
		}
	}

	if (iFindItem)
	{
		sNoticeMessage = string_format("%s is currently blocked for illegal activity.", GetName().c_str());
		if (!sNoticeMessage.empty())
			g_pMain->SendNotice(sNoticeMessage.c_str(),Nation::ALL);

		m_bAuthority = AUTHORITY_BANNED;
		Disconnect();
	}
}

void CUser::SpeedHackUser()
{
	if (!isInGame() || isGM())
		return;

	int16 nMaxSpeed = 45;

	if (GetFame() == COMMAND_CAPTAIN || isRogue())
		nMaxSpeed = 90;
	else if (isWarrior() || isMage() || isPriest() || isKurPor())
		nMaxSpeed = 67;

	if (m_sSpeed > nMaxSpeed || m_sSpeed < -nMaxSpeed)
	{
		DateTime time;
		Disconnect();
		g_pMain->SendFormattedNotice("%s is currently disconnect for speed hack.",Nation::ALL,GetName().c_str());
		g_pMain->WriteCheatLogFile(string_format("[ SpeedHack - %d:%d:%d ] %s is Disconnected.\n", time.GetHour(),time.GetMinute(),time.GetSecond(),GetName().c_str()));
	}
}

void CUser::SpeedHackTime(Packet & pkt)
{
	if (!isInGame() || isGM())
		return;

	float nSpeed = 45.0f;

	if (GetFame() == COMMAND_CAPTAIN || isRogue())
		nSpeed = 90.0f;
	else if (isWarrior() || isMage() || isPriest() || isKurPor())
		nSpeed = 67.0f;

	nSpeed += 8.0f;

	float nRange = (pow(GetX() - m_LastX, 2.0f) + pow(GetZ() - m_LastZ, 2.0f)) / 100.0f;

	if (nRange >= nSpeed)
	{
		DateTime time;
		g_pMain->WriteCheatLogFile(string_format("[ SpeedHack - %d:%d:%d ] %s is Warp to Last Position.\n", time.GetHour(),time.GetMinute(),time.GetSecond(),GetName().c_str()));
		Warp(uint16(m_LastX) * 10, uint16(m_LastZ) * 10);
	}
	else
	{
		m_LastX = GetX();
		m_LastZ = GetZ();
	}
}


