#include "stdafx.h"
#include "KingSystem.h"
#include "../shared/DateTime.h"
#include "Map.h"

CKingSystem::CKingSystem()
{
	m_byNation = 0;

	m_byType = ELECTION_TYPE_NO_TERM;
	m_sYear = 0;
	m_byMonth = m_byDay = m_byHour = m_byMinute = 0;

	m_byImType = 0;
	m_sImYear = 0;
	m_byImMonth = m_byImDay = m_byImHour = m_byImMinute = 0;

	m_byNoahEvent = m_byNoahEvent_Day = m_byNoahEvent_Hour = m_byNoahEvent_Minute = 0;
	m_sNoahEvent_Duration = 0;

	m_byExpEvent = m_byExpEvent_Day = m_byExpEvent_Hour = m_byExpEvent_Minute;
	m_sExpEvent_Duration = 0;

	m_nTribute = 0;
	m_nTerritoryTax = m_nNationalTreasury = 0;

	m_bSentFirstMessage = false;
}


void CKingSystem::CheckKingTimer()
{
	uint8	bCurMonth = g_localTime.tm_mon + 1,
		bCurDay = g_localTime.tm_mday,
		bCurHour = g_localTime.tm_hour,
		bCurMinute = g_localTime.tm_min;

	if (m_byNoahEvent || m_byExpEvent)
		CheckSpecialEvent();

	switch (m_byType)
	{
	case ELECTION_TYPE_NO_TERM:
		{
			DateTime dt(m_sYear, m_byMonth, m_byDay, m_byHour, m_byMinute);

			dt.AddDays(-1);
			if (bCurMonth == dt.GetMonth()
				&& bCurDay == dt.GetDay()
				&& bCurHour == dt.GetHour()
				&& bCurMinute == dt.GetMinute())
			{
				UpdateElectionStatus(ELECTION_TYPE_NOMINATION);

				g_pMain->SendFormattedResource(IDS_KING_RECOMMEND_TIME, m_byNation, false);
				SendUDP_ElectionStatus(m_byType);

				ResetElectionLists();
				LoadRecommendList();
			}
		}break;

	case ELECTION_TYPE_NOMINATION:
		{
			DateTime dt(m_sYear, m_byMonth, m_byDay, m_byHour, m_byMinute);

			dt.AddHours(-1);
			dt.AddDays(2);
			if (bCurMonth == dt.GetMonth()
				&& bCurDay == dt.GetDay()
				&& bCurHour == dt.GetHour()
				&& bCurMinute == dt.GetMinute())
			{
				UpdateElectionStatus(ELECTION_TYPE_PRE_ELECTION);

				g_pMain->SendFormattedResource(IDS_KING_RECOMMEND_FINISH_TIME, m_byNation, false);
				LoadRecommendList();
				SendUDP_ElectionStatus(m_byType);
			}

			if (!(bCurMinute % 30) && !m_bSentFirstMessage)
			{
				m_bSentFirstMessage = true;
				g_pMain->SendFormattedResource(IDS_KING_PERIOD_OF_RECOMMEND_MESSAGE, m_byNation, true);
				break;
			}

			m_bSentFirstMessage = false;
		} break;

	case ELECTION_TYPE_PRE_ELECTION:
		{
			DateTime dt(m_sYear, m_byMonth, m_byDay, m_byHour, m_byMinute);
			
			dt.AddDays(2);
			if (bCurMonth == dt.GetMonth()
				&& bCurDay == dt.GetDay()
				&& bCurHour == dt.GetHour()
				&& bCurMinute == dt.GetMinute())
			{
				UpdateElectionStatus(ELECTION_TYPE_ELECTION);
				g_pMain->SendFormattedResource(IDS_KING_ELECTION_TIME, m_byNation, false);
				SendUDP_ElectionStatus(m_byType);
			}
		} break;

	case ELECTION_TYPE_ELECTION:
		{
			DateTime dt(m_sYear, m_byMonth, m_byDay, m_byHour, m_byMinute);

			dt.AddDays(5);
			if (bCurMonth == dt.GetMonth()
				&& bCurDay == dt.GetDay()
				&& bCurHour == dt.GetHour()
				&& bCurMinute == dt.GetMinute())
			{
				UpdateElectionStatus(ELECTION_TYPE_TERM_STARTED);
				GetElectionResult(m_byNation);
				return;
			}

			if (!(bCurMinute % 30) && !m_bSentFirstMessage)
			{
				m_bSentFirstMessage = true;
				g_pMain->SendFormattedResource(IDS_KING_PERIOD_OF_ELECTION_MESSAGE, m_byNation, true);
				break;
			}

			m_bSentFirstMessage = false;
		} break;

	case ELECTION_TYPE_TERM_STARTED:
			{
			DateTime dt(m_sYear, m_byMonth, m_byDay, m_byHour, m_byMinute);

			dt.AddDays(35);
			dt.AddMinutes(0);
			if (bCurMonth == dt.GetMonth()
				&& bCurDay == dt.GetDay()
				&& bCurHour == dt.GetHour()
				&& bCurMinute == dt.GetMinute())
			{
				UpdateElectionStatus(ELECTION_TYPE_TERM_ENDED);
			}
		} break;

	case ELECTION_TYPE_TERM_ENDED:
		{
			DateTime dt(m_sYear, m_byMonth, m_byDay, m_byHour, m_byMinute);

			dt.AddDays(5);
			dt.AddMinutes(1);
			if (bCurMonth == dt.GetMonth()
				&& bCurDay == dt.GetDay()
				&& bCurHour == dt.GetHour()
				&& bCurMinute == dt.GetMinute())
			{
				UpdateElectionStatus(ELECTION_TYPE_NOMINATION);

				g_pMain->SendFormattedResource(IDS_KING_RECOMMEND_TIME, m_byNation, false);
				SendUDP_ElectionStatus(m_byType);

				ResetElectionLists();
				LoadRecommendList();
			}
		} break;
	}

	switch (m_byImType)
	{
	case 1:
		{
			DateTime dt(m_sImYear, m_byImMonth, m_byImDay, m_byImHour, m_byImMinute);
			dt.AddHours(47);
			if (bCurMonth == dt.GetMonth()
				&& bCurDay == dt.GetDay()
				&& bCurHour == dt.GetHour()
				&& bCurMinute == dt.GetMinute())
			{
				// GetImpeachmentRequestResult();
			}
		} break;

	case 2:
		{
			DateTime dt(m_sImYear, m_byImMonth, m_byImDay, m_byImHour, m_byImMinute);
			dt.AddDays(2);
			if (bCurMonth == dt.GetMonth()
				&& bCurDay == dt.GetDay()
				&& bCurHour == dt.GetHour()
				&& bCurMinute == dt.GetMinute())
			{
				m_byImType = 3;
				g_pMain->SendFormattedResource(IDS_KING_IMPEACHMENT_ELECTION_MESSAGE, m_byNation, false);
			}
		} break;

	case 3:
		{
			DateTime dt(m_sImYear, m_byImMonth, m_byImDay, m_byImHour, m_byImMinute);
			dt.AddDays(3);
			if (bCurMonth == dt.GetMonth()
				&& bCurDay == dt.GetDay()
				&& bCurHour == dt.GetHour()
				&& bCurMinute == dt.GetMinute())
			{
				m_byImType = 4;
				//GetImpeachmentElectionResult();
			}
		} break;
	}
}

void CKingSystem::UpdateElectionStatus(uint8 byElectionStatus)
{
	Packet result(WIZ_KING, uint8(KING_ELECTION));
	result	<< uint8(KING_ELECTION) << uint8(KING_ELECTION_UPDATE_STATUS)
			<< m_byNation << byElectionStatus;

	m_byType = byElectionStatus;
	g_pMain->AddDatabaseRequest(result);
}

void CKingSystem::UpdateElectionList(uint8 byElectionListType, bool bDeleteList, uint16 sClanID, std::string & strUserID, CUser * pUser /*= nullptr*/)
{
	Guard lock(m_lock);
	// byElectionListType:
	Packet result(WIZ_KING, uint8(KING_ELECTION));

	result	<< uint8(KING_ELECTION)
		<< uint8(KING_ELECTION_UPDATE_LIST) << m_byNation 
		<< byElectionListType << bDeleteList
		<< sClanID << strUserID;

	g_pMain->AddDatabaseRequest(result, pUser);

	KingElectionList * pList = nullptr;
	switch (byElectionListType)
	{
	case 3: 
		pList = &m_senatorList;
		break;

	case 4:
		pList = &m_candidateList;
		break;
	}

	if (pList == nullptr)
		return;

	KingElectionList::iterator itr = pList->find(strUserID);
	if (bDeleteList)
	{
		if (itr != pList->end())
		{
			delete itr->second;
			pList->erase(itr);
		}
	}
	else
	{
	}
}

void CKingSystem::CheckSpecialEvent()
{
	uint8	bCurDay = g_localTime.tm_mday,
			bCurHour = g_localTime.tm_hour,
			bCurMinute = g_localTime.tm_min;

	int16 sEventExpiry;

	if (m_byExpEvent)
	{
		if (bCurDay == m_byExpEvent_Day)
			sEventExpiry = bCurMinute + 60 * (bCurHour - m_byExpEvent_Hour) - m_byExpEvent_Minute;
		else
			sEventExpiry = bCurMinute + 60 * (bCurHour - m_byExpEvent_Hour + 24) - m_byExpEvent_Minute;

		if (sEventExpiry > m_sExpEvent_Duration)
		{
			m_byExpEvent = 0;
			m_byExpEvent_Day = 0;
			m_byExpEvent_Hour = 0;
			m_byExpEvent_Minute = 0;
			m_sExpEvent_Duration = 0;

			g_pMain->SendFormattedResource(IDS_KING_EXP_BONUS_EVENT_STOP, m_byNation, false);
		}
	}

	if (m_byNoahEvent)
	{
		if (bCurDay == m_byNoahEvent_Day)
			sEventExpiry = bCurMinute + 60 * (bCurHour - m_byNoahEvent_Hour) - m_byNoahEvent_Minute;
		else
			sEventExpiry = bCurMinute + 60 * (bCurHour - m_byNoahEvent_Hour + 24) - m_byNoahEvent_Minute;

		if (sEventExpiry > m_sNoahEvent_Duration)
		{
			m_byNoahEvent = 0;
			m_byNoahEvent_Day = 0;
			m_byNoahEvent_Hour = 0;
			m_byNoahEvent_Minute = 0;
			m_sNoahEvent_Duration = 0;

			g_pMain->SendFormattedResource(IDS_KING_NOAH_BONUS_EVENT_STOP, m_byNation, false);
		}
	}
}


void CKingSystem::LoadRecommendList()
{
	Guard lock(m_lock);
	m_top10ClanSet.clear();
	for (int i = 1; i <= 1000; i++)
	{
		_KNIGHTS_RATING * pRating = g_pMain->m_KnightsRatingArray[m_byNation - 1].GetData(i);
		CKnights * pKnights = nullptr;

		if (pRating == nullptr
				|| (pKnights = g_pMain->GetClanPtr(pRating->sClanID)) == nullptr)
				continue;

		UpdateElectionList(3, false, pRating->sClanID, pKnights->m_strChief);

		CUser * pUser = g_pMain->GetUserPtr(pKnights->m_strChief, TYPE_CHARACTER);
		if (pUser != nullptr)
		{
			Packet result;
			std::string notice;

			g_pMain->GetServerResource(IDS_KING_RECOMMEND_REQUEST_MESSAGE, &notice, pKnights->m_strChief.c_str());
			g_pMain->GetServerResource(IDP_ANNOUNCEMENT, &notice, notice.c_str());

			ChatPacket::Construct(&result, WAR_SYSTEM_CHAT, &notice);
			pUser->Send(&result);
		}

		m_top10ClanSet.insert(pRating->sClanID);
	}
}


void CKingSystem::KingNotifyMessage(uint32 nResourceID, int byNation, ChatType chatType)
{
	std::string result;
	switch (nResourceID)
	{
//		 Resource ID (SERVER_RESOURCE)						// ID used internally (officially)
	case IDS_KING_RECOMMEND_TIME:							// 1 (none)
	case IDS_KING_RECOMMEND_FINISH_TIME:					// 2 (none)
	case IDS_KING_ELECTION_TIME:							// 3 (none)
	case IDS_KING_IMPEACHMENT_REQUEST_TIME:					// 4 (none)
	case IDS_KING_IMPEACHMENT_ELECTION_TIME:				// 5 (none)
	case IDS_KING_REIGN_TIME:								// 7 (none)
	case IDS_KING_KARUS_PRIZE_EVENT_MESSAGE:				// 11 (awarded %s %d coins)
	case IDS_KING_ELMO_PRIZE_EVENT_MESSAGE:					// 12 (awarded %s %d coins)
	case IDS_KING_KARUS_FUGITIVE_EVENT_MESSAGE_1:			// 13 (awarded %s %d coins -- probably inaccurate though, see below)
	case IDS_KING_ELMO_FUGITIVE_EVENT_MESSAGE_1:			// 14 (awarded %s %d coins -- probably inaccurate though, see below)
	case IDS_KING_FUGITIVE_EVENT_MESSAGE_2:					// 15 (%s killed %s and received %d coins as a reward)
	case IDS_KING_KARUS_WEATHER_FINE_EVENT:					// 16 (none)
	case IDS_KING_KARUS_WEATHER_RAIN_EVENT:					// 17 (none)
	case IDS_KING_KARUS_WEATHER_SNOW_EVENT:					// 18 (none)
	case IDS_KING_ELMO_WEATHER_FINE_EVENT:					// 19 (none)
	case IDS_KING_ELMO_WEATHER_RAIN_EVENT:					// 20 (none)
	case IDS_KING_ELMO_WEATHER_SNOW_EVENT:					// 21 (none)
	case IDS_KING_KARUS_NOAH_BONUS_EVENT:					// 22 (%d%% increased coin rate)
	case IDS_KING_KARUS_EXP_BONUS_EVENT:					// 23 (%d%% increased XP rate)
	case IDS_KING_ELMO_NOAH_BONUS_EVENT:					// 24 (%d%% increased coin rate)
	case IDS_KING_ELMO_EXP_BONUS_EVENT:						// 25 (%d%% increased XP rate)
	case IDS_KING_RECOMMEND_REQUEST_MESSAGE:				// 26 (%s can nominate a King)
	case IDS_KING_CANDIDACY_RECOMMEND_MESSAGE:				// 27 (%s has nominated %s as a King)
	case IDS_KING_PERIOD_OF_RECOMMEND_MESSAGE:				// 28 (none)
	case IDS_KING_PERIOD_OF_ELECTION_MESSAGE:				// 29 (none)
	case IDS_KING_ELECTION_RESULT_MESSAGE:					// 30 (%d%% of the vote was won by %s)
	case IDS_KING_EXP_BONUS_EVENT_STOP:						// 31 (none)
	case IDS_KING_NOAH_BONUS_EVENT_STOP:					// 32 (none)
	case IDS_KING_IMPEACHMENT_REQUEST_MESSAGE:				// 33 (none)
	case IDS_KING_IMPEACHMENT_PASS_MESSAGE:					// 34 (none)
	case IDS_KING_IMPEACHMENT_REJECT_MESSAGE:				// 35 (none)
	case IDS_KING_IMPEACHMENT_ELECTION_MESSAGE:				// 36 (none)
	case IDS_KING_IMPEACHMENT_ELECTION_YES_RESULT_MESSAGE:	// 37 (none)
	case IDS_KING_IMPEACHMENT_ELECTION_NO_RESULT_MESSAGE:	// 38 (none)
		break;
	}
}

void CKingSystem::PacketProcess(CUser * pUser, Packet & pkt)
{
	if (pUser == nullptr)
		return;

	CKingSystem * pKingSystem = g_pMain->m_KingSystemArray.GetData(pUser->GetNation());
	if (pKingSystem != nullptr)
		pKingSystem->KingPacketProcess(pUser, pkt);
}


void CKingSystem::KingPacketProcess(CUser * pUser, Packet & pkt)
{
	switch (pkt.read<uint8>())
	{
	case KING_ELECTION:
		ElectionSystem(pUser, pkt);
		break;

	case KING_IMPEACHMENT:
		ImpeachmentSystem(pUser, pkt);
		break;

	case KING_TAX:
		KingTaxSystem(pUser, pkt);
		break;

	case KING_EVENT:
		KingSpecialEvent(pUser, pkt);
		break;

	case KING_NATION_INTRO:
		break;
	}
}


void CKingSystem::ElectionSystem(CUser * pUser, Packet & pkt)
{
	switch (pkt.read<uint8>())
	{
	case KING_ELECTION_SCHEDULE:
		ElectionScheduleConfirmation(pUser, pkt);
		break;

	case KING_ELECTION_NOMINATE:
		CandidacyRecommend(pUser, pkt);
		break;

	case KING_ELECTION_NOTICE_BOARD:
		CandidacyNoticeBoard(pUser, pkt);
		break;

	case KING_ELECTION_POLL:
		ElectionPoll(pUser, pkt);
		break;

	case KING_ELECTION_RESIGN:
		CandidacyResign(pUser, pkt);
		break;
	}
}


void CKingSystem::ElectionScheduleConfirmation(CUser * pUser, Packet & pkt)
{
	Packet result(WIZ_KING, uint8(KING_ELECTION));
	result << uint8(KING_ELECTION_SCHEDULE);

	switch (m_byImType)
	{
	case 0:
		{
			uint8 byElectionMonth = g_localTime.tm_mon + 1;

			if (g_localTime.tm_mday > m_byDay)
			{
				++byElectionMonth;
				while (byElectionMonth > 12)
					byElectionMonth -= 12;
			}

			result	<< uint8(1)
				<< byElectionMonth 
				<< m_byDay << m_byHour << m_byMinute;
		} break;

	case 1:
		{
			result	<< uint8(3)
				<< m_byImMonth 
				<< m_byImDay << m_byImHour << m_byImMinute;
		} break;

	case 3:
		{
			uint8 byImpeachmentMonth = m_byImMonth;
			while (byImpeachmentMonth > 12)
				m_byImMonth -= 12;

			result	<< uint8(2)
				<< byImpeachmentMonth
				<< m_byImDay << m_byImHour << m_byImMinute;
		} break;
	}

	pUser->Send(&result);
}


void CKingSystem::CandidacyRecommend(CUser * pUser, Packet & pkt) 
{
	Packet result(WIZ_KING, uint8(KING_ELECTION));
	std::string strUserID;
	pkt.SByte();
	pkt >> strUserID;
	if (strUserID.empty() || strUserID.length() > MAX_ID_SIZE)
		return;

	result << uint8(KING_ELECTION_NOMINATE);

	if (m_byType != ELECTION_TYPE_NOMINATION)
	{
		result << int16(-2);
		pUser->Send(&result);
		return;
	}

	Guard lock(m_lock);
	LoadRecommendList();

	if (!pUser->isClanLeader()
			|| m_top10ClanSet.find(pUser->GetClanID()) == m_top10ClanSet.end()
			|| m_resignedCandidateList.find(pUser->m_strUserID) != m_resignedCandidateList.end())
	{
		result << int16(-3);
		pUser->Send(&result);
		return;
	}

	result << strUserID;
	g_pMain->AddDatabaseRequest(result, pUser);
}


void CKingSystem::InsertNominee(std::string & strNominee)
{
	Guard lock(m_lock);

	KingElectionList::iterator senatorItr = m_senatorList.find(strNominee);
	if (senatorItr == m_senatorList.end())
		return;

	KingElectionList::iterator candidateItr = m_candidateList.find(strNominee);
	if (candidateItr != m_candidateList.end())
		return;

	_KING_ELECTION_LIST * pEntry = new _KING_ELECTION_LIST;
	memcpy(pEntry, senatorItr->second, sizeof(_KING_ELECTION_LIST));

	m_candidateList.insert(make_pair(strNominee, pEntry));
}


void CKingSystem::CandidacyNoticeBoard(CUser * pUser, Packet & pkt)
{
	Packet result(WIZ_KING, uint8(KING_ELECTION));
	uint8 opcode = pkt.read<uint8>();
	bool bSuccess = false;

	result << uint8(KING_ELECTION_NOTICE_BOARD) << opcode;

	switch (opcode)
	{
	case KING_CANDIDACY_BOARD_WRITE:
		{
			if (m_byType != ELECTION_TYPE_NOMINATION 
				&& m_byType != ELECTION_TYPE_PRE_ELECTION
				&& m_byType != ELECTION_TYPE_ELECTION)
			{
				result << int16(-1);
				pUser->Send(&result);
				return;
			}

			std::string strNotice;
			pkt >> strNotice;

			if (strNotice.empty() || strNotice.length() > 480)
			{
				result << int16(-2);
				pUser->Send(&result);
				return;
			}

			KingCandidacyNoticeBoardMap::iterator itr = m_noticeBoardMap.find(pUser->m_strUserID);
			if (itr == m_noticeBoardMap.end())
			{
				result << int16(-3);
				pUser->Send(&result);
				return;
			}

			itr->second = strNotice;
			size_t wpos = result.wpos();

			result << int16(1);
			pUser->Send(&result);

			result.put(wpos, strNotice.c_str(), strNotice.length());

			result << strNotice;
			g_pMain->AddDatabaseRequest(result, pUser);
		} return;

	case KING_CANDIDACY_BOARD_READ:
		{ 
			if (m_byType != ELECTION_TYPE_NOMINATION 
				&& m_byType != ELECTION_TYPE_PRE_ELECTION
				&& m_byType != ELECTION_TYPE_ELECTION)
			{
				result << int16(-1);
				pUser->Send(&result);
				return;
			}

			pkt >> opcode;
			result << opcode;

			if (opcode == 1)
			{
				Guard lock(m_lock);
				result	<< int16(1)
					<< uint8(m_noticeBoardMap.size());

				result.SByte();
				foreach (itr, m_noticeBoardMap)
					result << itr->first;
			}
			else if (opcode == 2)
			{
				std::string strCandidate;
				pkt.SByte();
				pkt >> strCandidate;

				if (strCandidate.empty() || strCandidate.length() > MAX_ID_SIZE)
					return;

				KingCandidacyNoticeBoardMap::iterator itr = m_noticeBoardMap.find(strCandidate);
				if (itr == m_noticeBoardMap.end()
						|| itr->second.empty())
				{
					result	<< int16(-2);
				}
				else
				{
					result.DByte();
					result	<< int16(1)
						<< strCandidate << itr->second;
				}
			}

			pUser->Send(&result);
		} return;

	case 4:
		if (m_byType == ELECTION_TYPE_NOMINATION 
			|| m_byType == ELECTION_TYPE_PRE_ELECTION
			|| m_byType == ELECTION_TYPE_ELECTION)
		{
			if (1 == 2)
				break;

			bSuccess = true;
		}
		break;

	case 5:
		if (m_byType == ELECTION_TYPE_NOMINATION 
			|| m_byType == ELECTION_TYPE_PRE_ELECTION
			|| m_byType == ELECTION_TYPE_ELECTION)
			bSuccess = true;
		break;


	default: 
		return;
	}

	result << int16(bSuccess ? 1 : -1);
	if (opcode == 4)
		result << bSuccess;

	pUser->Send(&result);
}


void CKingSystem::ElectionPoll(CUser * pUser, Packet & pkt)
{
	Packet result(WIZ_KING, uint8(KING_ELECTION));
	uint8 opcode = pkt.read<uint8>();

	result << uint8(KING_ELECTION_POLL) << opcode;

	if (m_byType != ELECTION_TYPE_ELECTION)
	{
		result << int16(-1);
		pUser->Send(&result);
		return;
	}

	Guard lock(m_lock);
	switch (opcode)
	{
	case 1:
		{
			uint8 count = (uint8)m_candidateList.size();
			result << uint16(1) << count;
			result.SByte();
			foreach (itr, m_candidateList)
			{
				CKnights * pKnights = g_pMain->GetClanPtr(itr->second->sKnights);
				result << itr->first;
				if (pKnights != nullptr)
					result << pKnights->m_strName;
				else
					result << uint8(0);
			}
			pUser->Send(&result);
		} break;

	case 2:
		{
			std::string strCandidate;
			pkt.SByte();
			pkt >> strCandidate;
			if (strCandidate.empty() || strCandidate.length() > MAX_ID_SIZE)
				return;

			KingElectionList::iterator itr = m_candidateList.find(strCandidate);
			if (itr == m_candidateList.end())
			{
				result << int16(-2);
				pUser->Send(&result);
				return;
			}

			if (pUser->GetLevel() < 20)
			{
				result << int16(-4);
				pUser->Send(&result);
				return;
			}

			UpdateElectionList(4, false, itr->second->sKnights, strCandidate, pUser);	
		} break;
	}
}


void CKingSystem::CandidacyResign(CUser * pUser, Packet & pkt) 
{
	Packet result(WIZ_KING, uint8(KING_ELECTION));
	result << uint8(KING_ELECTION_RESIGN);

	if (m_byType != ELECTION_TYPE_NOMINATION)
	{
		result << int16(-2);
		pUser->Send(&result);
		return;
	}

	Guard lock(m_lock);
	KingElectionList::iterator itr = m_candidateList.find(pUser->m_strUserID);

	if (itr == m_candidateList.end())
	{
		result << int16(-3);
		pUser->Send(&result);
		return;
	}

	m_resignedCandidateList.insert(pUser->m_strUserID);
	m_candidateList.erase(itr);

	UpdateElectionList(4, true, itr->second->sKnights, pUser->m_strUserID, pUser);
}


void CKingSystem::ImpeachmentSystem(CUser * pUser, Packet & pkt)
{
	switch (pkt.read<uint8>())
	{
	case KING_IMPEACHMENT_REQUEST:
		ImpeachmentRequest(pUser, pkt);
		break;

	case KING_IMPEACHMENT_REQUEST_ELECT:
		ImpeachmentRequestElect(pUser, pkt);
		break;

	case KING_IMPEACHMENT_LIST:
		ImpeachmentList(pUser, pkt);
		break;

	case KING_IMPEACHMENT_ELECT:
		ImpeachmentElect(pUser, pkt);
		break;

	case KING_IMPEACHMENT_REQUEST_UI_OPEN:
		ImpeachmentRequestUiOpen(pUser, pkt);
		break;

	case KING_IMPEACHMENT_ELECTION_UI_OPEN:
		ImpeachmentElectionUiOpen(pUser, pkt);
		break;
	}
}

void CKingSystem::ImpeachmentRequest(CUser * pUser, Packet & pkt) 
{

}
void CKingSystem::ImpeachmentRequestElect(CUser * pUser, Packet & pkt) 
{

}
void CKingSystem::ImpeachmentList(CUser * pUser, Packet & pkt) 
{

}
void CKingSystem::ImpeachmentElect(CUser * pUser, Packet & pkt) 
{

}


void CKingSystem::ImpeachmentRequestUiOpen(CUser * pUser, Packet & pkt) 
{
	Packet result(WIZ_KING, uint8(KING_IMPEACHMENT));
	result	<< uint8(KING_IMPEACHMENT_REQUEST_UI_OPEN);

	if (m_byImType != 1)
		result << int16(-1);
	else if (pUser->m_bRank != 2)
		result << int16(-2);
	else
		result << int16(1);

	pUser->Send(&result);
}


void CKingSystem::ImpeachmentElectionUiOpen(CUser * pUser, Packet & pkt)
{
	Packet result(WIZ_KING, uint8(KING_IMPEACHMENT));

	result	<< uint8(KING_IMPEACHMENT_ELECTION_UI_OPEN)
		<< int16(m_byImType != 3 ? -1 : 1);

	pUser->Send(&result);
}


void CKingSystem::KingTaxSystem(CUser * pUser, Packet & pkt)
{
	CKingSystem *pKingSystem = g_pMain->m_KingSystemArray.GetData(m_byNation);
	Packet result(WIZ_KING, uint8(KING_TAX));
	uint8 bOpcode = pkt.read<uint8>();
	result << bOpcode;

	if (!pUser->isKing())
	{
		result << int16(-1);
		pUser->Send(&result);
		return;
	}

	switch (bOpcode)
	{
	case 2:
		{
			pUser->GoldGain(m_nTerritoryTax);
		
			HandleDatabaseRequest_Tax(m_nTerritoryTariff, pUser->GetNation(), m_nTerritoryTax);
			pKingSystem->m_nTerritoryTax -= m_nTerritoryTax;
		}
		break;
	case 3:
		{
			C3DMap * pMap = g_pMain->GetZoneByID(m_byNation);
			if (pMap == nullptr)
				return;

			result << int16(1) << pMap->GetTariff();
			pUser->Send(&result);
		}
		break;
	case 4:
		{
			C3DMap * pMap = g_pMain->GetZoneByID(m_byNation);
			uint8 byTerritoryTariff = pkt.read<uint8>();

			if (pMap == nullptr
				|| byTerritoryTariff > 10)
			{
				result << int16(-2);
				pUser->Send(&result);
				return;
			}

			pMap->SetTariff(byTerritoryTariff);

			result << int16(1) << byTerritoryTariff << m_byNation;
			g_pMain->Send_All(&result, nullptr, m_byNation);

			pKingSystem->m_nTerritoryTariff = byTerritoryTariff;

			g_pMain->AddDatabaseRequest(result, pUser);
		}
		break;
	case 7:
		{
			if (pUser->CheckExistItem(KING_SCEPTER))
			{
				result << int16(-1);
			}
			else if (pUser->FindSlotForItem(KING_SCEPTER) < 0)
			{
				result << int16(-2);
			}
			else
			{
				pUser->GiveItem(KING_SCEPTER);
				pUser->GiveItem(KING_SCEPTER);
				result << int16(1);
			}
			pUser->Send(&result);
		}
		break;
	}
}


void CKingSystem::KingSpecialEvent(CUser * pUser, Packet & pkt)
{
	Packet result(WIZ_KING, uint8(KING_EVENT));
	uint8 opcode = pkt.read<uint8>();
	result << opcode;

	if (!pUser->isKing())
	{
		result << int16(-1);
		pUser->Send(&result);
		return;
	}

	switch (opcode)
	{
	case KING_EVENT_NOAH:
		{
			Guard lock(m_lock);

			uint8 bAmount = pkt.read<uint8>();
			if (bAmount < 1 || bAmount > 3)
				return;

			uint32 nCost = 50000000 * bAmount;
			if (nCost > m_nNationalTreasury)
			{
				result << int16(-3);
				pUser->Send(&result);
				return;
			}

			m_nNationalTreasury -= nCost;

			m_byNoahEvent = bAmount;
			m_byNoahEvent_Day = g_localTime.tm_mday;
			m_byNoahEvent_Hour = g_localTime.tm_hour;
			m_byNoahEvent_Minute = g_localTime.tm_min;

			m_sNoahEvent_Duration = 30;

			g_pMain->SendFormattedResource(m_byNation == KARUS ? IDS_KING_KARUS_NOAH_BONUS_EVENT : IDS_KING_ELMO_NOAH_BONUS_EVENT,
				m_byNation, false, bAmount);

			result << m_byNation << bAmount << m_byNoahEvent_Day << m_byNoahEvent_Hour << m_byNoahEvent_Minute << m_sNoahEvent_Duration;
			g_pMain->AddDatabaseRequest(result);
		} break;

	case KING_EVENT_EXP:
		{
			Guard lock(m_lock);

			uint8 bAmount = pkt.read<uint8>();
			if (bAmount != 10 && bAmount != 30 && bAmount != 50)
				return;

			uint32 nCost = 30000000 * bAmount;
			if (nCost > m_nNationalTreasury)
			{
				result << int16(-3);
				pUser->Send(&result);
				return;
			}

			m_nNationalTreasury -= nCost;

			m_byExpEvent = bAmount;
			m_byExpEvent_Day = g_localTime.tm_mday;
			m_byExpEvent_Hour = g_localTime.tm_hour;
			m_byExpEvent_Minute = g_localTime.tm_min;

			m_sExpEvent_Duration = 30;

			g_pMain->SendFormattedResource(m_byNation == KARUS ? IDS_KING_KARUS_EXP_BONUS_EVENT : IDS_KING_ELMO_EXP_BONUS_EVENT,
				m_byNation, false, bAmount);

			result << m_byNation << bAmount << m_byExpEvent_Day << m_byExpEvent_Hour << m_byExpEvent_Minute << m_sExpEvent_Duration;
			g_pMain->AddDatabaseRequest(result);
		} break;

	case KING_EVENT_PRIZE:
		{
			Guard lock(m_lock);

			uint32 nCoins;
			std::string strUserID;
			pkt.SByte();
			pkt >> nCoins >> strUserID;

			if (nCoins == 0)
				return;

			CUser * pTUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
			if (pTUser == nullptr || strUserID.empty() || strUserID.length() > MAX_ID_SIZE)
			{
				result << int16(-2);
				pUser->Send(&result);
				return;
			}

			if (nCoins > m_nNationalTreasury)
			{
				result << int16(-4);
				pUser->Send(&result);
				return;
			}

			m_nNationalTreasury -= nCoins;
			pTUser->GoldGain(nCoins);

			g_pMain->SendFormattedResource(m_byNation == KARUS ? IDS_KING_KARUS_PRIZE_EVENT_MESSAGE : IDS_KING_ELMO_PRIZE_EVENT_MESSAGE,
				m_byNation, false, pTUser->m_strUserID.c_str(), nCoins);

			result << m_byNation << nCoins << strUserID;
			g_pMain->AddDatabaseRequest(result);

		} break;

	case KING_EVENT_FUGITIVE:
		break;

	case KING_EVENT_WEATHER:
		{
			Guard lock(m_lock);

			uint8 bType, bAmount;
			pkt >> bType >> bAmount;

			if (bType != 1)
				if (bAmount == 0 || bAmount > 100
					|| bType == 0 || bType > WEATHER_SNOW)
					return;

			if (m_nNationalTreasury < 100000)
			{
				result << int16(-3);
				pUser->Send(&result);
				return;
			}

			m_nNationalTreasury -= 100000;

			g_pMain->m_byKingWeatherEvent = 1;
			g_pMain->m_byKingWeatherEvent_Day = g_localTime.tm_mday;
			g_pMain->m_byKingWeatherEvent_Hour = g_localTime.tm_hour;
			g_pMain->m_byKingWeatherEvent_Minute = g_localTime.tm_min;

			g_pMain->m_byWeather = bType;
			g_pMain->m_sWeatherAmount = bAmount;

			g_pMain->UpdateWeather();

			uint32 nResourceID = 
				(m_byNation == KARUS 
				? IDS_KING_KARUS_WEATHER_FINE_EVENT + (bType-1) 
				: IDS_KING_ELMO_WEATHER_FINE_EVENT  + (bType-1));

			g_pMain->SendFormattedResource(nResourceID, m_byNation, false);
		} break;

	case KING_EVENT_NOTICE: 
		{
			std::string strMessage;
			pkt.SByte();
			pkt >> strMessage;
			if (strMessage.empty() || strMessage.length() > 256)
				return;

			result.SByte();
			result << uint8(1) << uint16(1) << strMessage;
			g_pMain->Send_All(&result, nullptr, m_byNation);
			DateTime time;
			g_pMain->WriteChatLogFile(string_format("[ KING - %d:%d:%d ] %s : %s ( Zone=%d, X=%d, Z=%d )\n",time.GetHour(),time.GetMinute(),time.GetSecond(),pUser->GetName().c_str(),strMessage.c_str(),pUser->GetZoneID(),uint16(pUser->GetX()),uint16(pUser->GetZ())));
		} break;
	}
}

void CKingSystem::ResetElectionLists()
{
	Guard lock(m_lock);

	foreach (itr, m_senatorList)
		delete itr->second;
	m_senatorList.clear();

	foreach (itr, m_candidateList)
		delete itr->second;
	m_candidateList.clear();
	m_resignedCandidateList.clear();
}

CKingSystem::~CKingSystem()
{
	ResetElectionLists();
}