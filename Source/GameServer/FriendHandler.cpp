#include "stdafx.h"

#define MAX_FRIEND_COUNT	24

void CUser::FriendProcess(Packet & pkt)
{
	uint8 opcode = pkt.read<uint8>();
	switch (opcode)
	{
	case FRIEND_REQUEST:
		FriendRequest();
		break;
	case FRIEND_REPORT:
		FriendReport(pkt);
		break;
	case FRIEND_ADD:
	case FRIEND_REMOVE:
		FriendModify(pkt, opcode);
		break;
	}
}

void CUser::FriendRequest()
{
	Packet result(WIZ_FRIEND_PROCESS, uint8(FRIEND_REQUEST));
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::FriendModify(Packet & pkt, uint8 opcode)
{
	std::string strUserID;
	CUser *pUser;
	pkt >> strUserID;

	if (strUserID.empty() || strUserID.size() > MAX_ID_SIZE 
		|| (opcode == FRIEND_ADD && (pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER)) == nullptr))
		return;

	Packet result(WIZ_FRIEND_PROCESS, opcode);
	if (opcode == FRIEND_ADD)
		result << pUser->GetSocketID();

	result.SByte();
	result << strUserID;
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::FriendReport(Packet & pkt)
{
	Packet result(WIZ_FRIEND_PROCESS, uint8(FRIEND_REPORT));
	uint16 usercount = pkt.read<uint16>();

	if (usercount > MAX_FRIEND_COUNT) 
		return;

	result << usercount;
	for (int i = 0; i < usercount; i++) 
	{
		std::string strUserID;
		int16 sid;

		pkt >> strUserID;
		if (strUserID.empty() || strUserID.size() > MAX_ID_SIZE)
			return;

		uint8 status = GetFriendStatus(strUserID, sid);
		result << strUserID << sid << status;
	}

	Send(&result);
}

uint8 CUser::GetFriendStatus(std::string & charName, int16 & sid)
{
	CUser *pUser;
	if (charName.empty()
		|| (pUser = g_pMain->GetUserPtr(charName, TYPE_CHARACTER)) == nullptr)
	{
		sid = -1;
		return 0; 
	}

	sid = pUser->GetSocketID();
	if (pUser->isInParty())
		return 3;

	return 1;
}

void CUser::RecvFriendModify(Packet & pkt, uint8 opcode)
{
	Packet result(WIZ_FRIEND_PROCESS);
	std::string strUserID;
	int16 sid = -1;
	uint8 bResult = 0;

	if (opcode == FRIEND_ADD)
		pkt >> sid;

	pkt >> bResult;

	pkt.SByte();
	pkt >> strUserID;

	uint8 status = GetFriendStatus(strUserID, sid);
	result << opcode << bResult << strUserID << sid << status;
	Send(&result);
}