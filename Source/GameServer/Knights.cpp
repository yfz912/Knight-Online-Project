#include "stdafx.h"
#include "Knights.h"

using std::string;

CKnights::CKnights()
{
	m_sIndex = 0;
	m_byFlag = ClanTypeNone;
	m_byNation = 0;
	m_byGrade = 5;
	m_byRanking = 0;
	m_sMembers = 1;
	memset(&m_Image, 0, sizeof(m_Image));
	m_nMoney = 0;
	m_sDomination = 0;
	m_nPoints = 0;
	m_nClanPointFund = 0;
	m_sCape = -1;
	m_sAlliance = 0;
	m_sMarkLen = 0;
	m_sMarkVersion = 0;
	m_bCapeR = m_bCapeG = m_bCapeB = 0;
	m_sClanPointMethod = 0;
}

void CKnights::OnLogin(CUser *pUser)
{
	Packet result;

	foreach_array (i, m_arKnightsUser)
	{
		_KNIGHTS_USER * p = &m_arKnightsUser[i];
		if (!p->byUsed
			|| STRCASECMP(p->strUserName.c_str(), pUser->GetName().c_str()) != 0)
			continue;

		p->pSession = pUser;
		p->strUserMemo = pUser->m_strMemo;
		p->m_sClass = pUser->GetClass();
		p->m_bLevel = pUser->GetLevel();
		pUser->m_pKnightsUser = p;
		break;
	}

	std::string buffer = string_format("%s is online.", pUser->GetName().c_str()); 
	ChatPacket::Construct(&result, KNIGHTS_CHAT, &buffer);
	Send(&result);

	if (!m_strClanNotice.empty())
	{
		ConstructClanNoticePacket(&result);
		pUser->Send(&result);
	}
}
void CKnights::OnLogoutAlliance(CUser *pUser)
{
	if (pUser->m_pKnightsUser != nullptr)
	{
		pUser->m_pKnightsUser->pSession = nullptr;
		pUser->m_pKnightsUser = nullptr;
	}

	Packet logoutNotice;
	std::string buffer = string_format("%s is offline.", pUser->GetName().c_str()); 
	ChatPacket::Construct(&logoutNotice, ALLIANCE_CHAT, &buffer);
	Send(&logoutNotice);
}
void CKnights::OnLoginAlliance(CUser *pUser)
{
	Packet result;

	foreach_array (i, m_arKnightsUser)
	{
		_KNIGHTS_USER * p = &m_arKnightsUser[i];
		if (!p->byUsed
			|| STRCASECMP(p->strUserName.c_str(), pUser->GetName().c_str()) != 0)
			continue;

		p->pSession = pUser;
		pUser->m_pKnightsUser = p;
		break;
	}

	std::string buffer = string_format("%s is online.", pUser->GetName().c_str()); 
	ChatPacket::Construct(&result, ALLIANCE_CHAT, &buffer);
	Send(&result);

	if (!m_strClanNotice.empty())
	{
		ConstructClanNoticePacket(&result);
		pUser->Send(&result);
	}
}
void CKnights::ConstructClanNoticePacket(Packet *result)
{
	result->Initialize(WIZ_NOTICE);
	result->DByte();
	*result	<< uint8(4)			
		<< uint8(1)
		<< "Clan Notice"
		<< m_strClanNotice;
}

void CKnights::UpdateClanNotice(std::string & clanNotice)
{
	if (clanNotice.length() > MAX_CLAN_NOTICE_LENGTH)
		return;

	Packet result;

	m_strClanNotice = clanNotice;

	std::string updateNotice = string_format("%s updated the clan notice.", m_strChief.c_str()); 
	ChatPacket::Construct(&result, KNIGHTS_CHAT, &updateNotice);
	Send(&result);

	ConstructClanNoticePacket(&result);
	Send(&result);

	result.Initialize(WIZ_CHAT);
	result << uint8(CLAN_NOTICE) << GetID() << clanNotice;
	g_pMain->AddDatabaseRequest(result);
}

void CKnights::UpdateClanFund()
{
	Packet result(WIZ_KNIGHTS_PROCESS, uint8(KNIGHTS_UPDATE_FUND));
	result << GetID() << uint32(m_nClanPointFund);
	g_pMain->AddDatabaseRequest(result);
}

void CKnights::OnLogout(CUser *pUser)
{
	if (pUser->m_pKnightsUser != nullptr)
	{
		pUser->m_pKnightsUser->pSession = nullptr;
		pUser->m_pKnightsUser = nullptr;
	}

	Packet logoutNotice;
	std::string buffer = string_format("%s is offline.", pUser->GetName().c_str()); 
	ChatPacket::Construct(&logoutNotice, KNIGHTS_CHAT, &buffer);
	Send(&logoutNotice);
}

bool CKnights::AddUser(std::string & strUserID)
{
	for (int i = 0; i < MAX_CLAN_USERS; i++)
	{
		_KNIGHTS_USER * p = &m_arKnightsUser[i];
		if (p->byUsed)
			continue;

		p->byUsed = 1;
		p->strUserName = strUserID;
		p->pSession = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
		if (p->pSession != nullptr)
			p->pSession->m_pKnightsUser = p;

		return true;
	}

	return false;
}

bool CKnights::AddUser(CUser *pUser)
{
	if (pUser == nullptr
		|| !AddUser(pUser->GetName()))
		return false;

	pUser->SetClanID(m_sIndex);
	pUser->m_bFame = TRAINEE;
	return true;
}

bool CKnights::RemoveUser(std::string & strUserID)
{
	for (int i = 0; i < MAX_CLAN_USERS; i++)
	{
		_KNIGHTS_USER * p = &m_arKnightsUser[i];
		if (p->byUsed == 0)
			continue;

		if (STRCASECMP(p->strUserName.c_str(), strUserID.c_str()) == 0)
		{
			if (p->nDonatedNP > 0)
				RefundDonatedNP(p->nDonatedNP, nullptr, p->strUserName.c_str());

			p->Initialise();
			return true;
		}
	}

	return false;
}

bool CKnights::RemoveUser(CUser *pUser)
{
	if (pUser == nullptr
		|| pUser->m_pKnightsUser == nullptr)
		return false;

	uint32 nDonatedNP = pUser->m_pKnightsUser->nDonatedNP;
	if (nDonatedNP > 0)
		RefundDonatedNP(nDonatedNP, pUser);

	pUser->SetClanID(0);
	pUser->m_bFame = 0;

	pUser->m_pKnightsUser->Initialise();
	pUser->m_pKnightsUser = nullptr;

	if (!pUser->isClanLeader())
		pUser->SendClanUserStatusUpdate();

	return true;
}

void CKnights::RefundDonatedNP(uint32 nDonatedNP, CUser * pUser /*= nullptr*/, const char * strUserID /*= nullptr*/)
{
		nDonatedNP = (nDonatedNP * 30) / 100;
	m_nClanPointFund -= nDonatedNP;

	if (pUser != nullptr)
	{
		pUser->m_iLoyalty += nDonatedNP;
		return;
	}

	Packet result(WIZ_KNIGHTS_PROCESS, uint8(KNIGHTS_REFUND_POINTS));
	result << strUserID << nDonatedNP;
	g_pMain->AddDatabaseRequest(result);
}

void CKnights::Disband(CUser *pLeader /*= nullptr*/)
{
	string clanNotice;
	g_pMain->GetServerResource(m_byFlag == ClanTypeTraining ? IDS_CLAN_DESTROY : IDS_KNIGHTS_DESTROY, 
		&clanNotice, m_strName.c_str());
	SendChat(clanNotice.c_str());

	foreach_array (i, m_arKnightsUser)
	{
		_KNIGHTS_USER *p = &m_arKnightsUser[i];
		if (!p->byUsed)
			continue;

		if (p->pSession != nullptr)
			RemoveUser(p->pSession);
		else
			RemoveUser(p->strUserName);

	}
	g_pMain->m_KnightsArray.DeleteData(m_sIndex);
	Packet result(WIZ_KNIGHTS_PROCESS, uint8(KNIGHTS_DESTROY));
	result << uint8(1);
	pLeader->Send(&result);
	pLeader->UserDataSaveToAgent();
}

void CKnights::SendUpdate()
{
	CKnights *aKnights = g_pMain->GetClanPtr(GetID());
	if (aKnights != nullptr && isInAlliance())
	{
		Packet result(WIZ_KNIGHTS_PROCESS, uint8(KNIGHTS_UPDATE));
		result	<< GetID() << m_byFlag << GetCapeID(aKnights)
			<< m_bCapeR << m_bCapeG << m_bCapeB << uint8(0);
		Send(&result);
	}
	else
	{
		Packet result(WIZ_KNIGHTS_PROCESS, uint8(KNIGHTS_UPDATE));
		result	<< GetID() << m_byFlag << CapGetCapeID()
			<< m_bCapeR << m_bCapeG << m_bCapeB << uint8(0);
		Send(&result);
	}
}

/*
void CKnights::Mark()
{
	CKnights *pKnights = g_pMain->GetClanPtr(GetID());
	if (pKnights != nullptr)
	{
		Packet result(WIZ_KNIGHTS_PROCESS);
		result	<< uint8(KNIGHTS_MARK_REQ) << uint16(1); // success
		result	<< uint16(pKnights->m_byNation) << GetID();
		result	<< uint16(pKnights->m_sMarkVersion) << uint16(pKnights->m_sMarkLen);
		result.append(pKnights->m_Image, pKnights->m_sMarkLen);
		Send(&result);
	}
}*/

void CKnights::SendChat(const char * format, ...)
{
	char buffer[128];
	va_list ap;
	va_start(ap, format);
	vsnprintf(buffer, 128, format, ap);
	va_end(ap);

	Packet result;
	ChatPacket::Construct(&result, KNIGHTS_CHAT, buffer);
	Send(&result);
}

void CKnights::SendChatAlliance(const char * format, ...)
{
	char buffer[128];
	va_list ap;
	va_start(ap, format);
	vsnprintf(buffer, 128, format, ap);
	va_end(ap);

	Packet result;
	ChatPacket::Construct(&result, ALLIANCE_CHAT, buffer);
	Send(&result);
}

void CKnights::Send(Packet *pkt)
{
	foreach_array (i, m_arKnightsUser)
	{
		_KNIGHTS_USER *p = &m_arKnightsUser[i];
		if (p->byUsed && p->pSession != nullptr)
			p->pSession->Send(pkt);
	}
}

CKnights::~CKnights()
{
}