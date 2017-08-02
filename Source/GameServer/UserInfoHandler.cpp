#include "stdafx.h"
#include "Map.h"
#include "../shared/DateTime.h"
#include <cmath>

void CUser::HandleUserInfo(Packet & pkt)
{		
	Packet result(WIZ_USER_INFO);
	uint16 sCount = 0;

	uint8 command;
	pkt >> command;

	if(command == 0x02)
	{	
		result << uint8(0x02) << uint8(0x01);

		std::string strCharName;
		pkt.SByte();
		pkt >> strCharName;
		CUser* pUser = g_pMain->GetUserPtr(strCharName, TYPE_CHARACTER);

		if(pUser == nullptr)
			return;
			
		result.SByte();
		result << pUser->GetName() << pUser->GetLevel() << pUser->GetClass() << pUser->GetLoyalty() << pUser->GetMonthlyLoyalty() << uint8(1);

		CKnights * pKnights = g_pMain->GetClanPtr(pUser->GetClanID());
		if (pKnights == nullptr)
			result << uint16(0) << uint16(0) << uint16(0) << uint16(0)  ;
		else
			result << pUser->GetClanID() << pKnights->m_sMarkVersion << pKnights->m_byFlag << pKnights->m_byGrade << pKnights->m_strName  << pKnights->m_strChief;

		
		   
		Send(&result);
	}
	if( command == 0x04 )
		RemoveRegionChat();
	if(command == 0x03)
		HandleUserInfoDetail(pkt);
	if(command == 0x01 )
	{
		result << uint8(command) << uint8(0x01) << GetZoneID() << uint8(0) << sCount;
		for(int i=0; i< MAX_USER; i++)
		{
		  CUser *pUser = g_pMain->GetUserPtr(i);
		  if (pUser == nullptr 
		   || !pUser->isInGame()
		   || pUser->GetZoneID() == ZONE_BORDER_DEFENSE_WAR
		   || pUser->GetZoneID() == ZONE_CHAOS_DUNGEON
		   || pUser->GetZoneID() != GetZoneID()
		   || pUser->isGM())
			continue;
		   result.SByte();
		   result << pUser->GetName()
			<< pUser->GetNation() 
			<< uint16(0x01)
			<< pUser->GetSPosX()
			<< pUser->GetSPosZ()
			<< pUser->GetClanID();

		   CKnights * pKnights = g_pMain->GetClanPtr(pUser->GetClanID());
		   if (pKnights == nullptr)
				result << uint16(0) << uint16(0);
		   else
				result << pKnights->m_sMarkVersion << pKnights->m_byFlag << pKnights->m_byGrade;

		   result << uint16(4);

		   sCount++;
		 }
		 result.put(4, sCount);
		 Send(&result);
	}

}

void CUser::RemoveRegionChat()
{
	Packet result(WIZ_USER_INFO,uint8(0x04));
	result.SByte(); 
	result<<GetName();
	g_pMain->Send_Zone(&result,GetZoneID());
}

  void CUser::HandleUserInfoShow(Packet & pkt)
{
	Packet result(WIZ_USER_INFO, uint8(UserInfoShow));
	uint16 resultCode = UserInfoShow;

	pkt.SByte();
	pkt		<< GetName()
			<< uint16(GetNation()) << GetClanID() << GetFame();
	Send(&result);
} 

  void CUser::HandleUserInfoNick(Packet & pkt)
{
	Packet result(WIZ_USER_INFO,uint8(UserInfoNick));

	result
		<<uint8(1)
		<< uint8(KNIGHTS_WAR_SURRENDER)
		<<uint8(0)
		<< GetName()
		<<uint16(0)
		<<uint16(0);
	Send(&result);

}

void CUser::HandleUserInfoDetail(Packet & pkt)
{
	Packet result(WIZ_USER_INFO, uint8(UserInfo));
	result.SByte(); 
	result 
		<< GetName()
		<< GetLevel()
		<< m_sClass
		<< uint16(0)
		<< GetLoyalty()
		<< GetClanID()
		<< GetFame();
	Send(&result);
}