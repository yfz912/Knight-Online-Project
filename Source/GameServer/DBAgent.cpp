#include "stdafx.h"
#include "../shared/database/OdbcConnection.h"
#include "KnightsManager.h"
#include "DBAgent.h"
#include "../shared/DateTime.h"

CDBAgent g_DBAgent;

using std::string;
using std::unique_ptr;

CDBAgent::CDBAgent()
{
	m_GameDB = new OdbcConnection();
	m_AccountDB = new OdbcConnection();
}

CDBAgent::~CDBAgent()
{
	delete m_GameDB;
	delete m_AccountDB;
}
bool CDBAgent::Startup(bool bMarsEnabled, 
					   tstring & strAccountDSN, tstring & strAccountUID, tstring & strAccountPWD,
					   tstring & strGameDSN, tstring & strGameUID, tstring & strGamePWD)
{
	if (!Connect(bMarsEnabled,
		strAccountDSN, strAccountUID, strAccountPWD,
		strGameDSN, strGameUID, strGamePWD))
	{
		// we should probably be a little more specific (i.e. *which* database server)
		printf(_T("ERROR: Failed to connect to the database server."));
		return false;
	}

	DatabaseThread::Startup();

	return true;
}

bool CDBAgent::Connect(bool bMarsEnabled, 
					   tstring & strAccountDSN, tstring & strAccountUID, tstring & strAccountPWD,
					   tstring & strGameDSN, tstring & strGameUID, tstring & strGamePWD)
{
	if (!m_AccountDB->Connect(strAccountDSN, strAccountUID, strAccountPWD, bMarsEnabled))
	{
		ReportSQLError(m_AccountDB->GetError());
		return false;
	}

	if (!m_GameDB->Connect(strGameDSN, strGameUID, strGamePWD, bMarsEnabled))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	return true;
}

void CDBAgent::ReportSQLError(OdbcError *pError)
{
	if (pError == nullptr)
		return;

	DateTime time;

	// This is *very* temporary.
	string errorMessage = string_format(_T("[ ODBC Error - %d.%d.%d %d:%d:%d ] ] Source: %s Error: %s Description: %s\n"),
		time.GetDay(),time.GetMonth(),time.GetYear(),time.GetHour(),time.GetMinute(),time.GetSecond(),
		pError->Source.c_str(), pError->ExtendedErrorMessage.c_str(), pError->ErrorMessage.c_str());

	Guard lock(m_lock);
	FILE *fp = fopen("./Logs/Errors.log", "a");
	if (fp != nullptr)
	{
		fwrite(errorMessage.c_str(), errorMessage.length(), 1, fp);
		fclose(fp);
	}

	TRACE("Database error: %s\n", errorMessage.c_str());
	delete pError;
}

int8 CDBAgent::AccountLogin(string & strAccountID, string & strPasswd)
{
	int8 bRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strPasswd.c_str(), strPasswd.length());

	if (!dbCommand->Execute(_T("{? = CALL GAME_LOGIN(?, ?)}")))
		ReportSQLError(m_GameDB->GetError());

	return bRet;
}

uint8 CDBAgent::NationSelect(string & strAccountID, uint8 bNation)
{
	uint8 bRet = 0;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());

	if (!dbCommand->Execute(string_format(_T("{? = CALL NATION_SELECT(?, %d)}"), bNation)))
		ReportSQLError(m_GameDB->GetError());

	return (bRet > 0 ? bNation : 0);
}

bool CDBAgent::GetAllCharID(string & strAccountID, string & strCharID1, string & strCharID2, string & strCharID3, string & strCharID4)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());

	if (!dbCommand->Execute(_T("SELECT strCharID1, strCharID2, strCharID3, strCharID4 FROM ACCOUNT_CHAR WHERE strAccountID = ?")))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	if (!dbCommand->hasData())
		return false;

	dbCommand->FetchString(1, strCharID1);
	dbCommand->FetchString(2, strCharID2);
	dbCommand->FetchString(3, strCharID3);
	dbCommand->FetchString(4, strCharID4);

	return true;
}

bool CDBAgent::SetAllCharID(string & strAccountID, string & strCharID1, string & strCharID2, string & strCharID3, string & strCharID4)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	string ID1, ID2,ID3, ID4;

	if (strCharID1 == "")
		ID1 = "Vazio";
	else
		ID1 = strCharID1;
	if (strCharID2 == "")
		ID2 = "Vazio";
	else
		ID2 = strCharID2;
	if (strCharID3 == "")
		ID3 = "Vazio";
	else
		ID3 = strCharID3;
	if (strCharID4 == "")
		ID4 = "Vazio";
	else
		ID4 = strCharID4;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, ID1.c_str(), ID1.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, ID2.c_str(), ID2.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, ID3.c_str(), ID3.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, ID4.c_str(), ID4.length());

	if (!dbCommand->Execute(_T("{CALL UPDATE_ALL_CHAR_ID("
		"?, ?, ?, ?, ?)}")))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	return true;
}

void CDBAgent::LoadCharInfo(string & strCharID, ByteBuffer & result)
{
	uint32 nHair = 0;
	uint16 sClass = 0;
	uint8 bRace = 0, bLevel = 0, bFace = 0, bZone = 0; 
	char strItem[INVENTORY_TOTAL * 8];
	char strItemEx[INVENTORY_TOTAL * 8];
	ByteBuffer itemData;

	// ensure it's all 0'd out initially.
	memset(strItem, 0x00, sizeof(strItem));
	memset(strItemEx, 0x00, sizeof(strItemEx));

	if (!strCharID.empty())
	{
		unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
		if (dbCommand.get() == nullptr)
			return;

		dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());

		if (!dbCommand->Execute(_T("SELECT Race, Class, HairRGB, [Level], Face, Zone, strItem FROM USERDATA WHERE strUserID = ?")))
			ReportSQLError(m_GameDB->GetError());

		if (dbCommand->hasData())
		{
			dbCommand->FetchByte(1, bRace);
			dbCommand->FetchUInt16(2, sClass);
			dbCommand->FetchUInt32(3, nHair);
			dbCommand->FetchByte(4, bLevel);
			dbCommand->FetchByte(5, bFace);
			dbCommand->FetchByte(6, bZone);
			dbCommand->FetchBinary(7, strItem, sizeof(strItem));
			dbCommand->FetchBinary(8, strItemEx, sizeof(strItemEx));
		}
	}

	itemData.append(strItem, sizeof(strItem));

	result	<< strCharID << bRace << sClass << bLevel << bFace << nHair << bZone;
	for (int i = 0; i < SLOT_MAX; i++) 
	{
		uint32 nItemID;
		uint16 sDurability, sCount;
		itemData >> nItemID >> sDurability >> sCount;
		if (i == HEAD || i == BREAST || i == SHOULDER || i == LEG || i == GLOVE || i == FOOT || i == RIGHTHAND || i == LEFTHAND)
			result << nItemID << sDurability;
	}
}

int8 CDBAgent::CreateNewChar(string & strAccountID, int index, string & strCharID, uint8 bRace, uint16 sClass, uint32 nHair, uint8 bFace, uint8 bStr, uint8 bSta, uint8 bDex, uint8 bInt, uint8 bCha)
{
	int8 bRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;
	
	ByteBuffer AchieveBuffer;

	for (int i = 1; i < ACHIEVE_TOTAL; i++)
		AchieveBuffer << uint16(i) << uint8(0) << uint16(0) << uint16(0);

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)AchieveBuffer.contents(), AchieveBuffer.size(), SQL_BINARY);

	if (!dbCommand->Execute(string_format(_T("{? = CALL CREATE_NEW_CHAR(?, %d, ?, %d, %d, %d, %d, %d, %d, %d, %d, %d, ?)}"), 
		index, bRace, sClass, nHair, bFace, bStr, bSta, bDex, bInt, bCha)))
		ReportSQLError(m_GameDB->GetError());

	return bRet;
}

int8 CDBAgent::ChangeHair(std::string & strAccountID, std::string & strCharID, uint8 bOpcode, uint8 bFace, uint32 nHair)
{
	int8 bRet = 1; // failed
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());

	if (!dbCommand->Execute(string_format(_T("{? = CALL CHANGE_HAIR(?, ?, %d, %d, %d)}"), 
		bOpcode, bFace, nHair)))
		ReportSQLError(m_GameDB->GetError());

	return bRet;
}

int8 CDBAgent::DeleteChar(string & strAccountID, int index, string & strCharID, string & strSocNo)
{
	int8 bRet = -2; // generic error
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strSocNo.c_str(), strSocNo.length());

	if (!dbCommand->Execute(string_format(_T("{? = CALL DELETE_CHAR(?, %d, ?, ?)}"), index)))
		ReportSQLError(m_GameDB->GetError());

	return bRet;
}

void CDBAgent::LoadRentalData(string & strAccountID, string & strCharID, UserRentalMap & rentalData)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	if (!dbCommand->Execute(_T("{CALL LOAD_RENTAL_DATA(?)}")))
	{
		ReportSQLError(m_GameDB->GetError());
		return;
	}

	if (!dbCommand->hasData())
		return;

	do
	{
		_USER_RENTAL_ITEM *pItem = new _USER_RENTAL_ITEM();
		_RENTAL_ITEM *pRentalItem = nullptr;

		dbCommand->FetchString(1, pItem->strUserID);
		if (STRCASECMP(pItem->strUserID.c_str(), strCharID.c_str()) != 0)
		{
			delete pItem;
			continue;
		}

		dbCommand->FetchByte(2, pItem->byRentalType);
		dbCommand->FetchByte(3, pItem->byRegType);
		dbCommand->FetchUInt32(4, pItem->nRentalIndex);
		dbCommand->FetchUInt32(5, pItem->nItemID);
		dbCommand->FetchUInt16(6, pItem->sDurability);
		dbCommand->FetchUInt64(7, pItem->nSerialNum);
		dbCommand->FetchUInt32(8, pItem->nRentalMoney);
		dbCommand->FetchUInt16(9, pItem->sRentalTime);
		dbCommand->FetchInt16(10, pItem->sMinutesRemaining);
		dbCommand->FetchString(11, pItem->szTimeRental, sizeof(pItem->szTimeRental));

		pRentalItem = g_pMain->m_RentalItemArray.GetData(pItem->nRentalIndex);
		if (pRentalItem == nullptr
			|| rentalData.find(pItem->nSerialNum) != rentalData.end())
			delete pItem;
		else
			rentalData.insert(std::make_pair(pItem->nSerialNum, pItem));

	} while (dbCommand->MoveNext());
}

void CDBAgent::LoadItemSealData(string & strAccountID, string & strCharID, UserItemSealMap & itemSealData)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	if (!dbCommand->Execute(_T("SELECT nItemSerial, nItemID, bSealType FROM SEALED_ITEMS WHERE strAccountID = ?")))
	{
		ReportSQLError(m_GameDB->GetError());
		return;
	}

	if (!dbCommand->hasData())
		return;

	do
	{
		_USER_SEAL_ITEM *pItem = new _USER_SEAL_ITEM;

		dbCommand->FetchUInt64(1, pItem->nSerialNum);
		dbCommand->FetchUInt32(2, pItem->nItemID);
		dbCommand->FetchByte(3, pItem->bSealType);

		if (pItem == nullptr)
			delete pItem;
		else
			itemSealData.insert(std::make_pair(pItem->nSerialNum, pItem));

	} while (dbCommand->MoveNext());
}

bool CDBAgent::LoadUserAchieve(CUser *pUser)
{
	if (pUser == nullptr)
		return false;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->m_strUserID.c_str(), pUser->m_strUserID.length());

	if (!dbCommand->Execute(_T("SELECT "
		"CoverTitle, SkillTitle, AchieveTime, MonKillCount, UserKillCount, UserDeathCount, "
		"aPoints, aRecently1, aRecently2, aRecently3, strAchieve "
		"FROM USER_ACHIEVE WHERE strUserID = ?")))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	char strAchieve[ACHIEVE_TOTAL * 7] = {0};

	int i = 1;
	dbCommand->FetchUInt16(i++, pUser->iCoverTitle);
	dbCommand->FetchUInt16(i++, pUser->iSkillTitle);
	dbCommand->FetchUInt32(i++, pUser->m_AchieveTimeIn);
	dbCommand->FetchUInt32(i++, pUser->MonDefeatCount);
	dbCommand->FetchUInt32(i++, pUser->UserDefeatCount);
	dbCommand->FetchUInt32(i++, pUser->UserDeathCount);
	dbCommand->FetchUInt32(i++, pUser->aPoints);
	dbCommand->FetchUInt16(i++, pUser->iRecently1);
	dbCommand->FetchUInt16(i++, pUser->iRecently2);
	dbCommand->FetchUInt16(i++, pUser->iRecently3);
	dbCommand->FetchBinary(i++, strAchieve, sizeof(strAchieve));

	ByteBuffer AchieveBuffer;

	AchieveBuffer.append(strAchieve, sizeof(strAchieve));

	memset(pUser->m_sAchieveDataArray, 0x00, sizeof(pUser->m_sAchieveDataArray));

	for (int i = 1; i < ACHIEVE_TOTAL; i++)
	{
		uint16	dAchieveID, dSlot1, dSlot2;
		uint8	dstats;

		AchieveBuffer >> dAchieveID >> dstats
			>> dSlot1 >> dSlot2;

		_ACHIEVE_MAIN * pAchieveMain = g_pMain->m_AchieveMainArray.GetData(dAchieveID);

		if (pAchieveMain)
			if (pAchieveMain->mType == 4 && dstats == 3)
				dstats = 0;

		_ACHIEVE_DATA * pAchieve = pUser->GetAchieve(i);

		pAchieve->dAchieveID	= dAchieveID;			
		pAchieve->dstats		= dstats;
		pAchieve->dSlot1		= dSlot1;
		pAchieve->dSlot2		= dSlot2;
	}
			
	return true;
}

bool CDBAgent::LoadUserData(string & strAccountID, string & strCharID, CUser *pUser)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	if (pUser == nullptr 
		|| pUser->m_bLogout
		|| !pUser->GetName().empty()
		|| strCharID.length() > MAX_ID_SIZE
		/*|| pUser->m_dwTime != 0*/)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());

	if (!dbCommand->Execute(_T("{CALL LOAD_USER_DATA(?, ?)}")))
		ReportSQLError(m_GameDB->GetError());

	if (!dbCommand->hasData())
		return false;

	char strItem[INVENTORY_TOTAL * 8] = {0}, strItemEx[INVENTORY_TOTAL * 8] = {0}, strSerial[INVENTORY_TOTAL * 8] = {0}, strQuest[QUEST_ARRAY_SIZE] = {0}, strQuestCount[QUEST_TOTAL * 2] = {0}, 
		strRebStats[5] = {0};

	uint16 sQuestCount = 0;

	int field = 1;
	dbCommand->FetchByte(field++, pUser->m_bNation);
	dbCommand->FetchByte(field++, pUser->m_bRace);
	dbCommand->FetchUInt16(field++, pUser->m_sClass);
	dbCommand->FetchUInt32(field++, pUser->m_nHair);
	dbCommand->FetchByte(field++, pUser->m_bRank);
	dbCommand->FetchByte(field++, pUser->m_bTitle);
	dbCommand->FetchByte(field++, pUser->m_bLevel);
	dbCommand->FetchByte(field++, pUser->m_reblvl);
	dbCommand->FetchInt64(field++, pUser->m_iExp);
	dbCommand->FetchUInt32(field++, pUser->m_iLoyalty);
	dbCommand->FetchByte(field++, pUser->m_bFace);
	dbCommand->FetchByte(field++, pUser->m_bCity);
	dbCommand->FetchInt16(field++, pUser->m_bKnights);
	dbCommand->FetchByte(field++, pUser->m_bFame);
	dbCommand->FetchInt16(field++, pUser->m_sHp);
	dbCommand->FetchInt16(field++, pUser->m_sMp);
	dbCommand->FetchInt16(field++, pUser->m_sSp);
	dbCommand->FetchByte(field++, pUser->m_bStats[STAT_STR]);
	dbCommand->FetchByte(field++, pUser->m_bStats[STAT_STA]);
	dbCommand->FetchByte(field++, pUser->m_bStats[STAT_DEX]);
	dbCommand->FetchByte(field++, pUser->m_bStats[STAT_INT]);
	dbCommand->FetchByte(field++, pUser->m_bStats[STAT_CHA]);
	dbCommand->FetchByte(field++, pUser->m_bAuthority);
	dbCommand->FetchInt16(field++, pUser->m_sPoints);
	dbCommand->FetchUInt32(field++, pUser->m_iGold);
	dbCommand->FetchByte(field++, pUser->m_bZone);
	dbCommand->FetchInt16(field++, pUser->m_sBind);
	pUser->m_curx = (float)(dbCommand->FetchInt32(field++) / 100.0f);
	pUser->m_curz = (float)(dbCommand->FetchInt32(field++) / 100.0f);
	pUser->m_cury = (float)(dbCommand->FetchInt32(field++) / 100.0f);
	pUser->m_oldx = pUser->m_curx;
	pUser->m_oldy = pUser->m_cury;
	pUser->m_oldz = pUser->m_curz;
	pUser->m_dwTime = dbCommand->FetchUInt32(field++) + 1;
	dbCommand->FetchString(field++, (char *)pUser->m_bstrSkill, sizeof(pUser->m_bstrSkill));
	dbCommand->FetchBinary(field++, strItem, sizeof(strItem));
	dbCommand->FetchBinary(field++, strItemEx, sizeof(strItemEx));
	dbCommand->FetchBinary(field++, strSerial, sizeof(strSerial));
	dbCommand->FetchUInt16(field++, sQuestCount);
	dbCommand->FetchBinary(field++, strQuest, sizeof(strQuest));
	dbCommand->FetchBinary(field++, strQuestCount, sizeof(strQuestCount));
	dbCommand->FetchBinary(field++, strRebStats, sizeof(strRebStats));
	dbCommand->FetchUInt32(field++, pUser->m_iMannerPoint);
	dbCommand->FetchUInt32(field++, pUser->m_iLoyaltyMonthly);
	dbCommand->FetchString(field++, pUser->m_strMemo);
	dbCommand->FetchUInt16(field++, pUser->m_GenieTime);
	dbCommand->FetchString(field++, (char *)pUser->m_GenieOptions, sizeof(pUser->m_GenieOptions));

	pUser->m_strUserID = strCharID;
	pUser->m_lastSaveTime = UNIXTIME;
	pUser->m_lastBonusTime = UNIXTIME;
	pUser->m_TimeOnline = UNIXTIME;

	// Convert the old quest storage format to the new one.
	pUser->m_questMap.clear();
	if (sQuestCount > QUEST_LIMIT)
		sQuestCount = QUEST_LIMIT;

	for (int i = 0, index = 0; i < sQuestCount; i++, index += 3)
	{
		uint16	sQuestID	= *(uint16 *)(strQuest + index);
		uint8	bQuestState	= *(uint8  *)(strQuest + index + 2);
		pUser->m_questMap.insert(std::make_pair(sQuestID, bQuestState));
	}

	// Start the Seed quest if it doesn't already exist.
	if (pUser->CheckExistEvent(STARTER_SEED_QUEST, 0))
		pUser->SaveEvent(STARTER_SEED_QUEST, 1);

	ByteBuffer itemBuffer, serialBuffer, itemExBuffer, RebStatsBuffer, QuestBuffer;
	itemBuffer.append(strItem, sizeof(strItem));
	itemExBuffer.append(strItemEx, sizeof(strItemEx));
	serialBuffer.append(strSerial, sizeof(strSerial));
	RebStatsBuffer.append(strRebStats, sizeof(strRebStats));
	QuestBuffer.append(strQuestCount, sizeof(strQuestCount));

	memset(pUser->m_sItemArray, 0x00, sizeof(pUser->m_sItemArray));

	UserRentalMap rentalData;

	// Until this statement is cleaned up, 
	// no other statements can be processed.
	delete dbCommand.release();

	LoadRentalData(strAccountID, strCharID, rentalData);
	LoadItemSealData(strAccountID, strCharID, pUser->m_sealedItemMap);

	for(int i = 0; i < QUEST_TOTAL; i++)
	{
		uint16 nQuestID;
		
		QuestBuffer >> nQuestID;

		_QUEST_DATA * uQuest = pUser->GetQuestID(i);

		uQuest->dQuestID = nQuestID;
	}

	uint8 RebStr, RebSta, RebDex, RebInt, RebCha;

	RebStatsBuffer >> RebStr >>  RebSta
		>> RebDex >> RebInt >> RebCha;

	pUser->SetRebStatBuff(STAT_STR, RebStr);
	pUser->SetRebStatBuff(STAT_STA, RebSta);
	pUser->SetRebStatBuff(STAT_DEX, RebDex);
	pUser->SetRebStatBuff(STAT_INT, RebInt);
	pUser->SetRebStatBuff(STAT_CHA, RebCha);

	for (int i = 0; i < INVENTORY_TOTAL; i++)
	{ 
		uint64 nSerialNum;
		uint32 nItemID;
		int16 sDurability, sCount, RentTime;
		uint32 expirationtime;

		itemBuffer >> nItemID >> sDurability >> sCount;
		itemExBuffer >> expirationtime >> RentTime;
		serialBuffer >> nSerialNum;

		_ITEM_TABLE *pTable = g_pMain->GetItemPtr(nItemID);
		if (pTable == nullptr || sCount <= 0)
			continue;

		if (!pTable->m_bCountable && sCount > 1)
			sCount = 1;
		else if (sCount > ITEMCOUNT_MAX)
			sCount = ITEMCOUNT_MAX;

		if (nSerialNum == 0)
			nSerialNum = g_pMain->GenerateItemSerial();

		_ITEM_DATA *pItem = pUser->GetItem(i);
		pItem->nNum = nItemID;
		pItem->sDuration = pTable->isAccessory() ? pTable->m_sDuration : sDurability;
		pItem->sCount = sCount;
		pItem->nSerialNum = nSerialNum;
		pItem->nExpirationTime = expirationtime;

		// If the serial was found in the rental data, mark as rented.
		UserRentalMap::iterator itr = rentalData.find(nSerialNum);
		if (itr != rentalData.end())
		{
			pItem->bFlag = ITEM_FLAG_RENTED;
			pItem->sRemainingRentalTime = itr->second->sMinutesRemaining;
		}

		UserItemSealMap::iterator sealitr = pUser->m_sealedItemMap.find(nSerialNum);
		if (sealitr != pUser->m_sealedItemMap.end())
		{
			if (sealitr->second->bSealType == 1)
				pItem->bFlag = ITEM_FLAG_SEALED;
			else if (sealitr->second->bSealType == 3)
				pItem->bFlag = ITEM_FLAG_BOUND;
		}

		g_pMain->AddUserItem(nItemID, nSerialNum);

		if (g_pMain->IsDuplicateItem(nItemID,nSerialNum))
			pItem->bFlag = ITEM_FLAG_DUPLICATE;

		if (pTable->m_Bound == 1)
		{
			if (pItem->bFlag == ITEM_FLAG_NONE)
				pItem->bFlag = ITEM_FLAG_NOT_BOUND;
		}
	}

	// Clean up the rental data
	foreach (itr, rentalData)
		delete itr->second;
	rentalData.clear();

	// Starter items. This needs fixing eventually.
	if (pUser->GetLevel() == 1 && pUser->m_iExp == 0) // going back to their initial bugginess
	{
		uint32 nItemID = 0;
		uint16 sDurability = 0;

		switch (pUser->m_sClass)
		{
		case 101:
			nItemID = 120010000;
			sDurability = 5000;
			break;
		case 102:
			nItemID = 110010000;
			sDurability = 4000;
			break;
		case 103:
			nItemID = 180010000;
			sDurability = 5000;
			break;
		case 104:
			nItemID = 190010000;
			sDurability = 10000;
			break;
		case 201:
			nItemID = 120050000;
			sDurability = 5000;
			break;
		case 202:
			nItemID = 110050000;
			sDurability = 4000;
			break;
		case 203:
			nItemID = 180050000;
			sDurability = 5000;
			break;
		case 204:
			nItemID = 190050000;
			sDurability = 10000;
			break;
		}

		if (nItemID && !pUser->CheckExistItem(nItemID, 1))
		{
			int slot = pUser->GetEmptySlot();
			if (slot < 0)
				return true;

			_ITEM_DATA * pItem = pUser->GetItem(slot);
			pItem->nNum = nItemID;
			pItem->sDuration = sDurability;
			pItem->sCount = 1;
			pItem->nSerialNum = g_pMain->GenerateItemSerial();
		}
	}

	return true;
}

bool CDBAgent::LoadWarehouseData(string & strAccountID, CUser *pUser)
{
	char strItem[WAREHOUSE_MAX * 8], strItemEx[WAREHOUSE_MAX * 8], strSerial[WAREHOUSE_MAX * 8];

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	if (pUser == nullptr 
		|| pUser->m_bLogout)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());

	if (!dbCommand->Execute(_T("SELECT nMoney, WarehouseData, strSerial, WarehouseDataEx FROM WAREHOUSE WHERE strAccountID = ?")))
		ReportSQLError(m_GameDB->GetError());

	if (!dbCommand->hasData())
		return false;

	memset(strItem, 0x00, sizeof(strItem));
	memset(strSerial, 0x00, sizeof(strSerial));
	memset(strItemEx, 0x00, sizeof(strItemEx));

	dbCommand->FetchUInt32(1, pUser->m_iBank);
	dbCommand->FetchBinary(2, strItem, sizeof(strItem));
	dbCommand->FetchBinary(3, strSerial, sizeof(strSerial));
	dbCommand->FetchBinary(4, strItemEx, sizeof(strItemEx));

	ByteBuffer itemBuffer, serialBuffer, itemExBuffer;
	itemBuffer.append(strItem, sizeof(strItem));
	itemExBuffer.append(strItemEx, sizeof(strItemEx));
	serialBuffer.append(strSerial, sizeof(strSerial));

	memset(pUser->m_sWarehouseArray, 0x00, sizeof(pUser->m_sWarehouseArray));

	for (int i = 0; i < WAREHOUSE_MAX; i++) 
	{
		uint64 nSerialNum;
		uint32 nItemID, nItemEx;
		int16 sDurability, sCount;

		itemBuffer >> nItemID >> sDurability >> sCount;
		serialBuffer >> nSerialNum;
		itemExBuffer >> nItemEx;

		_ITEM_TABLE *pTable = g_pMain->GetItemPtr(nItemID);
		if (pTable == nullptr || sCount <= 0)
			continue;

		if (!pTable->m_bCountable && sCount > 1)
			sCount = 1;
		else if (sCount > ITEMCOUNT_MAX)
			sCount = ITEMCOUNT_MAX;

		pUser->m_sWarehouseArray[i].nNum = nItemID;
		pUser->m_sWarehouseArray[i].sDuration = sDurability;
		pUser->m_sWarehouseArray[i].sCount = sCount;
		pUser->m_sWarehouseArray[i].nSerialNum = nSerialNum;
		pUser->m_sWarehouseArray[i].nExpirationTime = nItemEx;

		UserItemSealMap::iterator sealitr = pUser->m_sealedItemMap.find(nSerialNum);
		if (sealitr != pUser->m_sealedItemMap.end())
		{
			if (sealitr->second->bSealType == 1)
				pUser->m_sWarehouseArray[i].bFlag = ITEM_FLAG_SEALED;
			else if (sealitr->second->bSealType == 3)
				pUser->m_sWarehouseArray[i].bFlag = ITEM_FLAG_BOUND;
		}

		g_pMain->AddUserItem(nItemID, nSerialNum);

		if (g_pMain->IsDuplicateItem(nItemID,nSerialNum))
			pUser->m_sWarehouseArray[i].bFlag = ITEM_FLAG_DUPLICATE;

		if (pTable->m_Bound == 1)
		{
			if (pUser->m_sWarehouseArray[i].bFlag == ITEM_FLAG_NONE)
				pUser->m_sWarehouseArray[i].bFlag = ITEM_FLAG_NOT_BOUND;
		}
	}

	return true;
}

bool CDBAgent::LoadWarehouseDataVip(string & strAccountID, CUser *pUser)
{
	char VipItem[VIP_HAVE_MAX * 8], VipItemEx[VIP_HAVE_MAX * 4], VipSerial[VIP_HAVE_MAX * 8];

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	if (pUser == nullptr 
		|| pUser->m_bLogout)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());

	if (!dbCommand->Execute(_T("SELECT VipPass, VipData, VipSerial, ViDataEx, vExpiration FROM WAREHOUSE_VIP WHERE strAccountID = ?")))
		ReportSQLError(m_GameDB->GetError());

	if (!dbCommand->hasData())
		return false;

	memset(VipItem, 0x00, sizeof(VipItem));
	memset(VipItemEx, 0x00, sizeof(VipItemEx));
	memset(VipSerial, 0x00, sizeof(VipSerial));

	dbCommand->FetchUInt16(1, pUser->m_VipPass);
	dbCommand->FetchBinary(2, VipItem, sizeof(VipItem));
	dbCommand->FetchBinary(3, VipSerial, sizeof(VipSerial));
	dbCommand->FetchBinary(4, VipItemEx, sizeof(VipItemEx));
	dbCommand->FetchUInt32(5, pUser->m_VipKeyTime);

	ByteBuffer VitemBuffer, VserialBuffer, VitemExBuffer;
	VitemBuffer.append(VipItem, sizeof(VipItem));
	VserialBuffer.append(VipItemEx, sizeof(VipItemEx));
	VitemExBuffer.append(VipSerial, sizeof(VipSerial));

	memset(pUser->m_sVIPhouseArray, 0x00, sizeof(pUser->m_sVIPhouseArray));

	for (int i = 0; i < VIP_HAVE_MAX; i++) 
	{
		uint64 nSerialNum;
		uint32 nItemID, nItemEx;
		int16 sDurability, sCount;

		VitemBuffer >> nItemID >> sDurability >> sCount;
		VserialBuffer >> nSerialNum;
		VitemExBuffer >> nItemEx;

		_ITEM_TABLE *pTable = g_pMain->GetItemPtr(nItemID);
		if (pTable == nullptr || sCount <= 0)
			continue;

		if (!pTable->m_bCountable && sCount > 1)
			sCount = 1;
		else if (sCount > ITEMCOUNT_MAX)
			sCount = ITEMCOUNT_MAX;

		pUser->m_sVIPhouseArray[i].nNum = nItemID;
		pUser->m_sVIPhouseArray[i].sDuration = sDurability;
		pUser->m_sVIPhouseArray[i].sCount = sCount;
		pUser->m_sVIPhouseArray[i].nSerialNum = nSerialNum;
		pUser->m_sVIPhouseArray[i].nExpirationTime = nItemEx;

		UserItemSealMap::iterator sealitr = pUser->m_sealedItemMap.find(nSerialNum);
		if (sealitr != pUser->m_sealedItemMap.end())
		{
			if (sealitr->second->bSealType == 1)
				pUser->m_sVIPhouseArray[i].bFlag = ITEM_FLAG_SEALED;
			else if (sealitr->second->bSealType == 3)
				pUser->m_sVIPhouseArray[i].bFlag = ITEM_FLAG_BOUND;
		}

		g_pMain->AddUserItem(nItemID, nSerialNum);

		if (g_pMain->IsDuplicateItem(nItemID,nSerialNum))
			pUser->m_sVIPhouseArray[i].bFlag = ITEM_FLAG_DUPLICATE;

		if (pTable->m_Bound == 1)
		{
			if (pUser->m_sVIPhouseArray[i].bFlag == ITEM_FLAG_NONE)
				pUser->m_sVIPhouseArray[i].bFlag = ITEM_FLAG_NOT_BOUND;
		}
	}

	return true;
}

void CDBAgent::ExpirationItem(uint64 nItemSerial, uint32 Times, CUser *pUser ) 
{

}

bool CDBAgent::LoadPremiumServiceUser(string & strAccountID, CUser *pUser)
{
	if (pUser == nullptr)
		return false;

	unique_ptr<OdbcCommand> dbCommand(m_AccountDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	char strPremiums[PREMIUM_TOTAL * 5] = {0};

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());

	if (!dbCommand->Execute(_T("{CALL LOAD_PREMIUM_SERVICE_USER(?)}")))
		ReportSQLError(m_AccountDB->GetError());

	if (!dbCommand->hasData())
		return false;

	memset(strPremiums, 0x00, sizeof(strPremiums));

	dbCommand->FetchByte(1, pUser->m_bPremiumInUse);
	dbCommand->FetchBinary(2, strPremiums, sizeof(strPremiums));

	ByteBuffer PremiumBuffer;
	PremiumBuffer.append(strPremiums, sizeof(strPremiums));

	memset(pUser->m_sPremiumArray, 0x00, sizeof(pUser->m_sPremiumArray));

	for(int p = 0; p < PREMIUM_TOTAL; p++)
	{
		uint8 rType;
		uint32 rTime;

		PremiumBuffer >> rType >> rTime;

		_PREMIUM_DATA * uPrem = pUser->GetPremiumPtr(p);
		if(rType ==0 || rTime == 0)
			continue;

		uPrem->pType = rType;
		uPrem->pTime = rTime;

		pUser->m_bPremiumCount++;
	}

	// this is hardcoded because we don't really care about the other mode
	if (pUser->m_bPremiumInUse != 0)
		pUser->m_bAccountStatus = 0; // normal premium with expiry time

	return true;
}

bool CDBAgent::LoadSavedMagic(CUser *pUser)
{
	if (pUser == nullptr)
		return false;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->m_strUserID.c_str(), pUser->m_strUserID.length());
	if (!dbCommand->Execute(_T("SELECT "
		"nSkill1, nDuring1, nSkill2, nDuring2, nSkill3, nDuring3, nSkill4, nDuring4, nSkill5, nDuring5, "
		"nSkill6, nDuring6, nSkill7, nDuring7, nSkill8, nDuring8, nSkill9, nDuring9, nSkill10, nDuring10 "
		"FROM USER_SAVED_MAGIC WHERE strCharID = ?")))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	Guard lock(pUser->m_savedMagicLock);
	pUser->m_savedMagicMap.clear();
	if (!dbCommand->hasData())
		return true;

	for (int i = 1; i <= 20; i += 2)
	{
		uint32	nSkillID;
		uint16	nExpiry;
		dbCommand->FetchUInt32(i, nSkillID);
		dbCommand->FetchUInt16(i + 1, nExpiry);

		if (nSkillID != 0)
			pUser->m_savedMagicMap[nSkillID] = (nExpiry + UNIXTIME);
	}

	return true;
}

bool CDBAgent::UpdateSavedMagic(CUser *pUser)
{
	if (pUser == nullptr)
		return false;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	Guard lock(pUser->m_savedMagicLock);
	uint32 nSkillID[10] = {0};
	uint16 tExpiryTime[10] = {0};
	uint32 i = 0;
	foreach (itr, pUser->m_savedMagicMap)
	{
		nSkillID[i]		= itr->first;
		if (itr->first != 0)
			tExpiryTime[i]	= uint16(itr->second - UNIXTIME);

		if (++i == 10)
			break;
	}

	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->m_strUserID.c_str(), pUser->m_strUserID.length());
	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_SAVED_MAGIC(?, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)}"), 
		nSkillID[0], tExpiryTime[0], nSkillID[1], tExpiryTime[1], nSkillID[2], tExpiryTime[2], nSkillID[3], tExpiryTime[3], nSkillID[4], tExpiryTime[4],
		nSkillID[5], tExpiryTime[5], nSkillID[6], tExpiryTime[6], nSkillID[7], tExpiryTime[7], nSkillID[8], tExpiryTime[8], nSkillID[9], tExpiryTime[9])))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	return true;
}

bool CDBAgent::SetLogInInfo(string & strAccountID, string & strCharID, string & strServerIP, short sServerNo, string & strClientIP, uint8 bInit)
{
	uint8 result = 0;
	unique_ptr<OdbcCommand> dbCommand(m_AccountDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &result);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strServerIP.c_str(), strServerIP.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strClientIP.c_str(), strClientIP.length());

	if (!dbCommand->Execute(string_format(_T("{? = CALL SET_LOGIN_INFO(?, ?, %d, ?, ?, %d)}"), sServerNo, bInit)))
		ReportSQLError(m_AccountDB->GetError());

	return (bool)(result == 0 ? false : true);
}

bool CDBAgent::LoadWebItemMall(std::vector<_ITEM_DATA> & itemList, CUser *pUser)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->m_strUserID.c_str(), pUser->m_strUserID.length());

	if (!dbCommand->Execute(_T("{CALL LOAD_WEB_ITEMMALL(?)}")))
		ReportSQLError(m_AccountDB->GetError());

	if (dbCommand->hasData())
	{
		do
		{
			_ITEM_DATA item;
			dbCommand->FetchUInt32(2, item.nNum); // 1 is the account name, which we don't need to use unless we're logging	
			dbCommand->FetchUInt16(3, item.sCount);
			dbCommand->FetchUInt32(5, item.nExpirationTime);
			itemList.push_back(item);
		} while (dbCommand->MoveNext());
	}

	return true;
}

bool CDBAgent::LoadSkillShortcut(Packet & result, CUser *pUser)
{
	if (pUser == nullptr)
		return false;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	uint16 sCount;
	char strSkillData[260];

	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->GetName().c_str(), pUser->GetName().length());
	if (!dbCommand->Execute(_T("SELECT nCount, strSkillData FROM USERDATA_SKILLSHORTCUT WHERE strCharID = ?")))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	if (!dbCommand->hasData())
		return false;

	dbCommand->FetchUInt16(1, sCount);
	dbCommand->FetchString(2, strSkillData, sizeof(strSkillData));

	result << sCount;
	for (uint32 i = 0; i < sCount; i++)
		result << *(uint32 *)(strSkillData + (i * sizeof(uint32)));

	return true;
}

void CDBAgent::SaveSkillShortcut(uint16 sCount, char *buff, CUser *pUser)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->GetName().c_str(), pUser->GetName().length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, buff, 260);

	if (!dbCommand->Execute(string_format(_T("{CALL SKILLSHORTCUT_SAVE(?, %d, ?)}"), sCount)))
		ReportSQLError(m_GameDB->GetError());
}

bool CDBAgent::SavePremiumServiceUser(CUser *pUser)
{
	
	if (pUser == nullptr)
		return false;

	if (pUser->m_bPremiumInUse == 0)
		return false;

	unique_ptr<OdbcCommand> dbCommand(m_AccountDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	ByteBuffer PremiumBuffer;

	uint8 pCount = 0;

	for(int p = 0; p < PREMIUM_TOTAL; p++)
	{
		_PREMIUM_DATA * uPrem = pUser->GetPremiumPtr(p);

		if (uPrem->pTime <= 0)
			continue;

		PremiumBuffer << uPrem->pType << uPrem->pTime;
		pCount++;
	}

	for(int i = pCount; i < PREMIUM_TOTAL; i++)
	{
		PremiumBuffer << uint8(0) << uint32(0);
		pCount++;
	}


	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->GetAccountName().c_str(), pUser->GetAccountName().length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)PremiumBuffer.contents(), PremiumBuffer.size(), SQL_BINARY);

	if (!dbCommand->Execute(string_format(_T("{CALL SAVE_PREMIUM_SERVICE_USER(?, %d, ?)}"), 
		pUser->m_bPremiumInUse)))
		ReportSQLError(m_GameDB->GetError());

	return true;
}

uint8 CDBAgent::SealItem(string strSealPasswd, uint64 nItemSerial, uint32 nItemID, uint8 bSealType, CUser *pUser)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return 3;

	uint8 bRet = 1;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->GetAccountName().c_str(), pUser->GetAccountName().length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->GetName().c_str(), pUser->GetName().length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strSealPasswd.c_str(), strSealPasswd.length());

	if (!dbCommand->Execute(string_format(_T("{? = CALL USER_ITEM_SEAL(?, ?, ?, " I64FMTD ", %d, %d)}"), nItemSerial, nItemID, bSealType)))
		ReportSQLError(m_GameDB->GetError());

	return bRet;
}

void CDBAgent::RequestFriendList(std::vector<string> & friendList, CUser *pUser)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->GetName().c_str(), pUser->GetName().length());
	if (!dbCommand->Execute(_T("SELECT * FROM FRIEND_LIST WHERE strUserID = ?")))
		ReportSQLError(m_GameDB->GetError());

	if (!dbCommand->hasData())
		return;

	string strCharID;
	for (int i = 2; i <= 25; i++)
	{
		if (dbCommand->FetchString(i, strCharID)
			&& strCharID.length())
			friendList.push_back(strCharID);
	}
}

FriendAddResult CDBAgent::AddFriend(short sid, short tid)
{
	CUser *pSrcUser = g_pMain->GetUserPtr(sid), *pTargetUser = g_pMain->GetUserPtr(tid);
	if (pSrcUser == nullptr 
		|| pTargetUser == nullptr)
		return FRIEND_ADD_ERROR;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return FRIEND_ADD_ERROR;

	int16 sRet = (int16)FRIEND_ADD_ERROR;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &sRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, pSrcUser->GetName().c_str(), pSrcUser->GetName().length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, pTargetUser->GetName().c_str(), pTargetUser->GetName().length());

	if (!dbCommand->Execute(_T("{? = CALL INSERT_FRIEND_LIST(?, ?)}")))
		ReportSQLError(m_GameDB->GetError());

	return (FriendAddResult)sRet;
}

FriendRemoveResult CDBAgent::RemoveFriend(string & strCharID, CUser *pUser)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return FRIEND_REMOVE_ERROR;

	int16 sRet = (int16)FRIEND_REMOVE_ERROR;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &sRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->m_strUserID.c_str(), pUser->m_strUserID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());

	if (!dbCommand->Execute(_T("{? = CALL DELETE_FRIEND_LIST(?, ?)}")))
		ReportSQLError(m_GameDB->GetError());

	return (FriendRemoveResult)sRet;
}

bool CDBAgent::UpdateUserAchieve(string & strCharID, UserUpdateType type, CUser *pUser)
{
	if (strCharID != pUser->GetName())
		return false;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	if (type == UPDATE_PACKET_SAVE)
		pUser->m_dwTime++;
	else if (type == UPDATE_LOGOUT || type == UPDATE_ALL_SAVE)
		pUser->m_dwTime = 0;

	ByteBuffer AchieveBuffer;

	for (int i = 1; i < ACHIEVE_TOTAL; i++)
	{
		_ACHIEVE_DATA * pAchieve = &pUser->m_sAchieveDataArray[i];
		AchieveBuffer << pAchieve->dAchieveID << pAchieve->dstats 
			<< pAchieve->dSlot1 << pAchieve->dSlot2;
	}

	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)AchieveBuffer.contents(), AchieveBuffer.size(), SQL_BINARY);

	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_USER_ACHIEVE("
		"?, " // strCharID 
		"%d, %d, %d, %d, "			// CoverTitle, SkillTitle, AchieveTime, MonKillCount 
		"%d, %d, %d, %d, "			// UserKillCount, UserDeathCount, Points, Recently1
		"%d, %d, ?)}"),					// Recently2, Recently3, strAchieve
		pUser->iCoverTitle, pUser->iSkillTitle, pUser->m_AchieveTimeOut, 
		pUser->MonDefeatCount, pUser->UserDefeatCount, pUser->UserDeathCount,
		pUser->aPoints, pUser->iRecently1, pUser->iRecently2,
		pUser->iRecently3)))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	return true;
}

bool CDBAgent::UpdateUser(string & strCharID, UserUpdateType type, CUser *pUser)
{
	if (strCharID != pUser->GetName())
		return false;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	if (type == UPDATE_PACKET_SAVE)
		pUser->m_dwTime++;
	else if (type == UPDATE_LOGOUT || type == UPDATE_ALL_SAVE)
		pUser->m_dwTime = 0;

	char strQuest[QUEST_ARRAY_SIZE];
	memset(strQuest, 0, sizeof(strQuest));
	int index = 0;
	foreach (itr, pUser->m_questMap)
	{
		*(uint16 *)(strQuest + index) = itr->first;
		*(uint8  *)(strQuest + index + 2) = itr->second;
		index += 3;
	}

	ByteBuffer itemBuffer, serialBuffer, itemExBuffer, RebStatsBuffer, QuestBuffer;

	for(int i = 0; i < QUEST_TOTAL; i++)
	{
		_QUEST_DATA * uQuest =pUser->GetQuestID(i);

		QuestBuffer << uQuest->dQuestID;
	}

	for (int i = 0; i < INVENTORY_TOTAL; i++)
	{
		_ITEM_DATA *pItem = &pUser->m_sItemArray[i];
		itemBuffer << pItem->nNum << pItem->sDuration << pItem->sCount;
		itemExBuffer<< pItem->nExpirationTime << pItem->sRemainingRentalTime;
		serialBuffer << pItem->nSerialNum;
	}

	RebStatsBuffer << pUser->GetRebStatBuff(STAT_STR) << pUser->GetRebStatBuff(STAT_STA)
		<< pUser->GetRebStatBuff(STAT_DEX) << pUser->GetRebStatBuff(STAT_INT) << pUser->GetRebStatBuff(STAT_CHA);

	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)pUser->m_bstrSkill, sizeof(pUser->m_bstrSkill));
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)itemBuffer.contents(), itemBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)itemExBuffer.contents(), itemExBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)serialBuffer.contents(), serialBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)strQuest, sizeof(strQuest), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)QuestBuffer.contents(), QuestBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)RebStatsBuffer.contents(), RebStatsBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->m_strMemo.c_str(), pUser->m_strMemo.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)pUser->m_GenieOptions, sizeof(pUser->m_GenieOptions));

	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_USER_DATA("
		"?, " // strCharID 
		"%d, %d, %d, %d, %d, "		// nation, race, class, hair, rank
		"%d, %d, %d, " I64FMTD ", %d, %d, "		// title, level, rebLevel, exp, loyalty, face
		"%d, %d, %d, "				// city, knights, fame
		"%d, %d, %d, "				// hp, mp, sp
		"%d, %d, %d, %d, %d, "		// str, sta, dex, int, cha
		"%d, %d, %d, %d, %d, "		// authority, free points, gold, zone, bind
		"%d, %d, %d, %d, %d, "		// x, z, y, dwTime, sQuestCount
		"?, ?, ?, ?, ?, ?, ?, "				// strSkill, strItem, strItemEx, strSerial, strQuest, strQuestCount, strRebStats
		"%d, %d, "				// manner points, monthly NP
		"?, %d, ?)}"),			// ClanMemo, Genie Time , Genie Options	
		pUser->m_bNation, pUser->m_bRace, pUser->m_sClass, pUser->m_nHair, pUser->m_bRank, 
		pUser->m_bTitle, pUser->m_bLevel, pUser->m_reblvl, pUser->m_iExp /* temp hack, database needs to support it */, pUser->m_iLoyalty, pUser->m_bFace, 
		pUser->m_bCity,	pUser->m_bKnights, pUser->m_bFame, 
		pUser->m_sHp, pUser->m_sMp, pUser->m_sSp, 
		pUser->m_bStats[STAT_STR], pUser->m_bStats[STAT_STA], pUser->m_bStats[STAT_DEX], pUser->m_bStats[STAT_INT], pUser->m_bStats[STAT_CHA], 
		pUser->m_bAuthority, pUser->m_sPoints, pUser->m_iGold, pUser->m_bZone, pUser->m_sBind, 
		(int)(pUser->m_curx*100), (int)(pUser->m_curz*100), (int)(pUser->m_cury*100), pUser->m_dwTime, pUser->m_questMap.size(), 
		pUser->m_iMannerPoint, pUser->m_iLoyaltyMonthly, pUser->m_GenieTime)))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	pUser->m_lastSaveTime = UNIXTIME;
	pUser->m_lastBonusTime = UNIXTIME;
	return true;
}

bool CDBAgent::UpdateWarehouseData(string & strAccountID, UserUpdateType type, CUser *pUser)
{
	if (strAccountID.length() == 0)
		return false;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	if (type == UPDATE_LOGOUT || type == UPDATE_ALL_SAVE)
		pUser->m_dwTime = 0;

	// This *should* be padded like the database field is (unnecessarily), but I want to see how MSSQL responds.
	ByteBuffer itemBuffer, serialBuffer, itemExBuffer;
	for (int i = 0; i < WAREHOUSE_MAX; i++)
	{
		_ITEM_DATA *pItem = &pUser->m_sWarehouseArray[i];
		itemBuffer << pItem->nNum << pItem->sDuration << pItem->sCount;
		serialBuffer << pItem->nSerialNum;
		itemExBuffer << pItem->nExpirationTime;
	}

	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)itemBuffer.contents(), itemBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)serialBuffer.contents(), serialBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)itemExBuffer.contents(), itemExBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());

	if (!dbCommand->Execute(string_format(_T("UPDATE WAREHOUSE SET nMoney=%d, dwTime=%d, WarehouseData=?, strSerial=?, WarehouseDataEx=? WHERE strAccountID=?"), 
		pUser->m_iBank, pUser->m_dwTime)))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	return true;
}

bool CDBAgent::UpdateWarehouseDataVip(string & strAccountID, UserUpdateType type, CUser *pUser)
{
	if (strAccountID.length() == 0)
		return false;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	if (type == UPDATE_LOGOUT || type == UPDATE_ALL_SAVE)
		pUser->m_dwTime = 0;

	// This *should* be padded like the database field is (unnecessarily), but I want to see how MSSQL responds.
	ByteBuffer VitemBuffer, VserialBuffer, iVtemExBuffer;

	for (int i = 0; i < VIP_HAVE_MAX; i++)
	{
		_ITEM_DATA *pItem = &pUser->m_sVIPhouseArray[i];
		VitemBuffer << pItem->nNum << pItem->sDuration << pItem->sCount;
		VserialBuffer << pItem->nSerialNum;
		iVtemExBuffer << pItem->nExpirationTime;
	}

	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)VitemBuffer.contents(), VitemBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)VserialBuffer.contents(), VserialBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)iVtemExBuffer.contents(), iVtemExBuffer.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());

	if (!dbCommand->Execute(string_format(_T("UPDATE WAREHOUSE_VIP SET VipPass=%d, VipData=?, VipSerial=?, ViDataEx=?, vExpiration=%d WHERE strAccountID=?"),
		pUser->m_VipPass, pUser->m_VipKeyTime)))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	return true;
}

int8 CDBAgent::CreateAlliance(uint8 byType, uint16 shAlliancIndex, uint16 shKnightsIndex, uint8  byEmptyIndex, uint8 bySiegeFlag)
{
	int8 bRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;
	

	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_KNIGHTS_ALLIANCE(%d, %d, %d, %d, %d)}"), byType, shAlliancIndex, shKnightsIndex, byEmptyIndex,bySiegeFlag)))
	ReportSQLError(m_GameDB->GetError());

	return bRet;
}

int8 CDBAgent::InsertAlliance(uint8 byType, uint16 shAlliancIndex, uint16 shKnightsIndex, uint8  byEmptyIndex, uint8 bySiegeFlag)
{
	int8 bRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;
	

	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_KNIGHTS_ALLIANCE(%d, %d, %d, %d, %d)}"), byType, shAlliancIndex, shKnightsIndex, byEmptyIndex,bySiegeFlag)))
	ReportSQLError(m_GameDB->GetError());

	return bRet;
}

int8 CDBAgent::RemoveAlliance(uint8 byType, uint16 shAlliancIndex, uint16 shKnightsIndex, uint8  byEmptyIndex, uint8 bySiegeFlag)
{
	int8 bRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;
	

	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_KNIGHTS_ALLIANCE(%d, %d, %d, %d, %d)}"), byType, shAlliancIndex, shKnightsIndex, byEmptyIndex,bySiegeFlag)))
	ReportSQLError(m_GameDB->GetError());

	return bRet;
}

int8 CDBAgent::DestoryAlliance(uint8 byType, uint16 shAlliancIndex, uint16 shKnightsIndex, uint8  byEmptyIndex, uint8 bySiegeFlag)
{
	int8 bRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;
	

	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_KNIGHTS_ALLIANCE(%d, %d, %d, %d, %d)}"), byType, shAlliancIndex, shKnightsIndex, byEmptyIndex,bySiegeFlag)))
	ReportSQLError(m_GameDB->GetError());

	return bRet;
}

int8 CDBAgent::CreateKnights(uint16 sClanID, uint8 bNation, string & strKnightsName, string & strChief, uint8 bFlag)
{
	int8 bRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strKnightsName.c_str(), strKnightsName.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strChief.c_str(), strChief.length());

	if (!dbCommand->Execute(string_format(_T("{? = CALL CREATE_KNIGHTS(%d, %d, %d, ?, ?)}"), sClanID, bNation, bFlag)))
		ReportSQLError(m_GameDB->GetError());

	return bRet;
}

int CDBAgent::UpdateKnights(uint8 bType, string & strCharID, uint16 sClanID, uint8 bDomination)
{
	int16 sRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return sRet;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &sRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());

	if (!dbCommand->Execute(string_format(_T("{? = CALL UPDATE_KNIGHTS(%d, ?, %d, %d)}"), bType + 0x10, sClanID, bDomination)))
		ReportSQLError(m_GameDB->GetError());

	if (bType == KNIGHTS_VICECHIEF && sRet == 0)
	{
		CKnights * pKnights = g_pMain->GetClanPtr(sClanID);
		if (pKnights != nullptr)
		{
			if (pKnights->m_strViceChief_1 == "")
				pKnights->m_strViceChief_1 = strCharID;
			else if (pKnights->m_strViceChief_2 == "")
				pKnights->m_strViceChief_2 = strCharID;
			else if (pKnights->m_strViceChief_3 == "")
				pKnights->m_strViceChief_3 = strCharID;
		}
	}

	return sRet;
}

int CDBAgent::DeleteKnights(uint16 sClanID)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());

	int16 sRet = -1;
	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &sRet);
	if (!dbCommand->Execute(string_format(_T("{? = CALL DELETE_KNIGHTS (%d)}"), sClanID)))
		ReportSQLError(m_GameDB->GetError());

	return sRet;
}

uint16 CDBAgent::LoadKnightsAllMembers(uint16 sClanID, Packet & result)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return 0;

	if (!dbCommand->Execute(string_format(_T("SELECT strUserID, Fame, [Level], Class FROM USERDATA WHERE Knights = %d"), sClanID)))
		ReportSQLError(m_GameDB->GetError());

	if (!dbCommand->hasData())
		return 0;

	uint16 count = 0;
	do
	{
		string strCharID; uint16 sClass; uint8 bFame, bLevel;
		dbCommand->FetchString(1, strCharID);
		dbCommand->FetchByte(2, bFame);
		dbCommand->FetchByte(3, bLevel);
		dbCommand->FetchUInt16(4, sClass);

		result << strCharID << bFame << bLevel << sClass 
			// check if user's logged in (i.e. grab logged in state)
			<< uint8(g_pMain->GetUserPtr(strCharID, TYPE_CHARACTER) == nullptr ? 0 : 1);
		count++;
	} while (dbCommand->MoveNext());

	return count;
}

bool CDBAgent::LoadKnightsInfo(uint16 sClanID, uint8 & bNation, std::string & strKnightsName, uint16 & sMembers, uint32 & nPoints, uint8 & bRank)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	if (!dbCommand->Execute(string_format(_T("SELECT Nation, IDName, Members, Points, Ranking FROM KNIGHTS WHERE IDNum=%d" ), sClanID)))
		ReportSQLError(m_GameDB->GetError());

	if (!dbCommand->hasData())
		return false;

	dbCommand->FetchByte(1, bNation);
	dbCommand->FetchString(2, strKnightsName);
	dbCommand->FetchUInt16(3, sMembers);
	dbCommand->FetchUInt32(4, nPoints);
	dbCommand->FetchByte(5, bRank);

	return true;
}

void CDBAgent::LoadKnightsAllList()
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	const tstring szSQL = _T("SELECT IDNum, Points, Ranking FROM KNIGHTS WHERE Points != 0 ORDER BY Points DESC"); 

	if (dbCommand.get() == nullptr)
		return;

	if (!dbCommand->Execute(szSQL))
		ReportSQLError(m_GameDB->GetError());

	if (!dbCommand->hasData())
		return;

	Packet result(WIZ_KNIGHTS_PROCESS);
	uint8 bCount = 0;
	int offset;

	do
	{
		if (bCount == 0)
		{
			result.clear();
			offset = result.wpos();
			result << uint8(0);
		}

		uint32 nPoints; uint16 sClanID; uint8 bRanking;
		dbCommand->FetchUInt16(1, sClanID);
		dbCommand->FetchUInt32(2, nPoints);
		dbCommand->FetchByte(3, bRanking);

		result << sClanID << nPoints << bRanking;

		// only send 100 clans at a time (no shared memory limit, yay!)
		if (++bCount >= 100)
		{
			// overwrite the count
			result.put(offset, bCount);

			CKnightsManager::RecvKnightsAllList(result);
			bCount = 0;
		}
	} while (dbCommand->MoveNext());

	// didn't quite make it in the last batch (if any)? send the remainder.
	if (bCount < 100)
	{
		result.put(offset, bCount);
		CKnightsManager::RecvKnightsAllList(result);
	}
}

bool CDBAgent::UpdateClanSymbol(uint16 sClanID, uint16 sSymbolSize, char *clanSymbol)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, clanSymbol, MAX_KNIGHTS_MARK, SQL_BINARY);
	if (!dbCommand->Execute(string_format(_T("UPDATE KNIGHTS SET Mark=?, sMarkVersion += 1, sMarkLen=%d WHERE IDNum=%d"), sSymbolSize, sClanID)))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	return true;
}

/**
* @brief	Handles the clan NP donations database request.
* 			It is essentially the client packet's real handler
* 			as the packet is simply forwarded here.
*
* @param	pUser	The user.
* @param	pkt  	The packet.
*/
void CKnightsManager::ReqDonateNP(CUser *pUser, Packet & pkt)
{
	if (pUser == nullptr || !pUser->isInClan())
		return;

	pUser->aKnightContrib = 0;
	uint32 amountNP;
	pkt >> amountNP;

	// Ensure the user has enough NP to donate to the clan.
	if (amountNP > pUser->GetLoyalty()
		// Users must have at least MIN_NP_TO_DONATE to donate.
			|| (pUser->GetLoyalty() - amountNP) < MIN_NP_TO_DONATE)
			return;

	// Ensure the clan exists
	CKnights * pKnights = g_pMain->GetClanPtr(pUser->GetClanID());
	if (pKnights == nullptr)
		return;

	// Take player's donated NP. Don't affect monthly NP. 
	if (g_DBAgent.DonateClanPoints(pUser, amountNP))
	{
		// Update the user's donated NP
		AddUserDonatedNP(pUser->GetClanID(), pUser->m_strUserID, amountNP);

		// Add to the clan point fund
		pKnights->m_nClanPointFund += amountNP;

		// Take the NP from the user and update the client.
		pUser->m_iLoyalty -= amountNP;
		pUser->SendLoyaltyChange(0);
		pUser->aKnightContrib = amountNP;
		pUser->AchieveMainCount(0, 0, 0, 5);		// Valid Knight Contribut Count
	}
}

/**
* @brief	Donates (clanPoints) clan points to the specified user's clan.
* 			Also increases the user's total NP donated.
*
* @param	pUser	  	The donor user.
* @param	amountNP  	The number of national points being donated by the user.
*
* @return	true if it succeeds, false if it fails.
*/
bool CDBAgent::DonateClanPoints(CUser * pUser,  uint32 amountNP)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->m_strUserID.c_str(), pUser->m_strUserID.length());
	if (!dbCommand->Execute(string_format(_T("{CALL DONATE_CLAN_POINTS(?, %d, %d)}"), pUser->GetClanID(), amountNP)))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	return true;
}

/**
* @brief	Handles the database request to refund the specified
* 			logged out character's donated NP.
* 			
* 			NOTE: Logged in players don't need to be handled as their NP is
* 			refunded in-game.
*
* @param	pkt	The packet.
*/
void CKnightsManager::ReqRefundNP(Packet & pkt)
{
	string strUserID;
	uint32 nRefundNP;
	pkt >> strUserID >> nRefundNP;
	g_DBAgent.RefundNP(strUserID, nRefundNP);
}

/**
* @brief	Handles the database request to update the
* 			specified clan's clan point fund.
*
* @param	pkt	The packet.
*/
void CKnightsManager::ReqUpdateNP(Packet & pkt)
{
	uint16 sClanID;
	uint32 nClanPointFund;
	pkt >> sClanID >> nClanPointFund;
	g_DBAgent.UpdateClanFund(sClanID, nClanPointFund);
}

/**
* @brief	Refunds the specified amount of NP to a logged out character.
*
* @param	strUserID	Character's name.
* @param	nRefundNP	The amount of NP to refund.
*/
void CDBAgent::RefundNP(string & strUserID, uint32 nRefundNP)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strUserID.c_str(), strUserID.length());
	if (!dbCommand->Execute(string_format(_T("UPDATE USERDATA SET Loyalty += %d WHERE strUserID = ?"), nRefundNP)))
		ReportSQLError(m_GameDB->GetError());
}

/**
* @brief	Change authority is logged out character.
*
* @param	strUserID	Character's name.
* @param	nAuthority	New user authority.
*/
void CDBAgent::UpdateUserAuthority(string & strUserID, uint16 nAuthority)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strUserID.c_str(), strUserID.length());
	if (!dbCommand->Execute(string_format(_T("UPDATE USERDATA SET Authority = %d WHERE strUserID = ?"), nAuthority)))
		ReportSQLError(m_GameDB->GetError());
}

/**
* @brief	Updates the clan fund.
*
* @param	sClanID		  	Identifier for the clan.
* @param	nClanPointFund	The current clan point fund.
*/
void CDBAgent::UpdateClanFund(uint16 sClanID, uint32 nClanPointFund)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	if (!dbCommand->Execute(string_format(_T("UPDATE KNIGHTS SET ClanPointFund = %d WHERE IDNum = %d"), nClanPointFund, sClanID)))
		ReportSQLError(m_GameDB->GetError());
}

/**
* @brief	Updates the clan notice.
*
* @param	sClanID		 	Identifier for the clan.
* @param	strClanNotice	The clan notice.
*/
void CDBAgent::UpdateClanNotice(uint16 sClanID, std::string & strClanNotice)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strClanNotice.c_str(), strClanNotice.length());
	if (!dbCommand->Execute(string_format(_T("UPDATE KNIGHTS SET strClanNotice = ? WHERE IDNum = %d"), sClanID)))
		ReportSQLError(m_GameDB->GetError());
}

NameChangeOpcode CDBAgent::UpdateCharacterName(std::string & strAccountID, std::string & strUserID, std::string & strNewUserID)
{
	 unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	 if (dbCommand.get() == nullptr)
	  return NameChangeInvalidName;

	 int16 sRet = 1;

	 dbCommand->AddParameter(SQL_PARAM_OUTPUT, &sRet);
	 dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	 dbCommand->AddParameter(SQL_PARAM_INPUT, strUserID.c_str(), strUserID.length());
	 dbCommand->AddParameter(SQL_PARAM_INPUT, strNewUserID.c_str(), strNewUserID.length());

	 if (!dbCommand->Execute(string_format(_T("{? = CALL CHANGE_NEW_ID(%d, ?, ?, ?, 1)}"), g_pMain->m_nServerNo)))
	  ReportSQLError(m_GameDB->GetError());

	 return NameChangeOpcode(sRet);
}

/**
* @brief	Handles clan cape database updates.
*
* @param	sClanID	Identifier for the clan.
* @param	sCapeID	Identifier for the cape.
* @param	r 	Red colour component.
* @param	g 	Green colour component.
* @param	b 	Blue colour component.
*
* @return	true if it succeeds, false if it fails.
*/
void CDBAgent::UpdateCape(uint16 sClanID, uint16 sCapeID, uint8 r, uint8 g, uint8 b)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	if (!dbCommand->Execute(string_format(_T("UPDATE KNIGHTS SET sCape=%d, bCapeR=%d, bCapeG=%d, bCapeB=%d WHERE IDNum=%d"), 
		sCapeID, r, g, b, sClanID)))
		ReportSQLError(m_GameDB->GetError());
}

/**
* @brief	Updates the clan grade.
*
* @param	sClanID	Identifier for the clan.
* @param	byFlag 	The clan type (training, promoted, etc).
* @param	sCapeID	Identifier for the cape.
*/
void CDBAgent::UpdateClanGrade(uint16 sClanID, uint8 byFlag, uint16 sCapeID)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	if (!dbCommand->Execute(string_format(_T("UPDATE KNIGHTS SET sCape=%d, Flag=%d WHERE IDNum=%d"), 
		sCapeID, byFlag, sClanID)))
		ReportSQLError(m_GameDB->GetError());
}

void CDBAgent::UpdateBattleEvent(string & strCharID, uint8 bNation)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	if (!dbCommand->Execute(string_format(_T("UPDATE BATTLE SET byNation=%d, strUserName=? WHERE sIndex=%d"), bNation, g_pMain->m_nServerNo)))
		ReportSQLError(m_GameDB->GetError());
}

void CDBAgent::AccountLogout(string & strAccountID)
{
	unique_ptr<OdbcCommand> dbCommand(m_AccountDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	if (!dbCommand->Execute(_T("{CALL ACCOUNT_LOGOUT(?)}")))
		ReportSQLError(m_AccountDB->GetError());
}

void CDBAgent::UpdateConCurrentUserCount(int nServerNo, int nZoneNo, int nCount)
{
	unique_ptr<OdbcCommand> dbCommand(m_AccountDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	if (!dbCommand->Execute(string_format(_T("UPDATE CONCURRENT SET zone%d_count = %d WHERE serverid = %d"), nZoneNo, nCount, nServerNo)))
		ReportSQLError(m_AccountDB->GetError());
}

// This is what everything says it should do, 
// but the client doesn't seem to care if it's over 1
uint8 CDBAgent::GetUnreadLetterCount(string & strCharID)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return 0;

	uint8 bCount = 0;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bCount);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	if (!dbCommand->Execute(_T("{? = CALL MAIL_BOX_CHECK_COUNT(?)}")))
	{
		ReportSQLError(m_GameDB->GetError());
		return 0;
	}

	return bCount;
}

bool CDBAgent::GetLetterList(string & strCharID, Packet & result, bool bNewLettersOnly /* = true*/)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	int8 bCount = 0;
	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bCount);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	if (!dbCommand->Execute(string_format(_T("{? = CALL MAIL_BOX_REQUEST_LIST(?, %d)}"), bNewLettersOnly)))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	result << uint8(1);
	int offset = result.wpos();
	result << bCount; // placeholder for count

	if (!dbCommand->hasData())
		return true;

	result.SByte();
	do
	{
		string strSubject, strSender;
		uint32 nLetterID, nItemID, nCoins, nDate;
		uint16 sCount, sDaysRemaining;
		uint8 bStatus, bType;

		dbCommand->FetchUInt32(1, nLetterID);
		dbCommand->FetchByte(2, bStatus);
		dbCommand->FetchByte(3, bType);
		dbCommand->FetchString(4, strSubject);
		dbCommand->FetchString(5, strSender);
		dbCommand->FetchByte(6, bType);
		dbCommand->FetchUInt32(7, nItemID);
		dbCommand->FetchUInt16(8, sCount);
		dbCommand->FetchUInt32(9, nCoins);
		dbCommand->FetchUInt32(10, nDate);
		dbCommand->FetchUInt16(11, sDaysRemaining); 

		result	<< nLetterID // letter ID
			<< bStatus  // letter status, doesn't seem to affect anything
			<< strSubject << strSender
			<< bType;	

		if (bType == 2)
			result	<< nItemID << sCount << nCoins;

		result	<< nDate // date (yy*10000 + mm*100 + dd)
			<< sDaysRemaining;

	} while (dbCommand->MoveNext());

	result.put(offset, bCount); // set count now that the result set's been read

	return true;
}

int8 CDBAgent::SendLetter(string & strSenderID, string & strRecipientID, string & strSubject, string & strMessage, uint8 bType, _ITEM_DATA * pItem, int32 nCoins)
{
	uint64 nSerialNum = 0;
	uint32 nItemID = 0;
	uint16 sCount = 0, sDurability = 0;
	int8 bRet = 0;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return 0;

	// This is a little bit redundant, but best to be sure.
	if (bType == 2 
		&& pItem != nullptr)
	{
		nItemID = pItem->nNum;
		sCount = pItem->sCount;
		sDurability = pItem->sDuration;
		nSerialNum = pItem->nSerialNum;
	}

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strSenderID.c_str(), strSenderID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strRecipientID.c_str(), strRecipientID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strSubject.c_str(), strSubject.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strMessage.c_str(), strMessage.length());

	// MSSQL uses signed types.
	if (!dbCommand->Execute(string_format(_T("{? = CALL MAIL_BOX_SEND(?, ?, ?, ?, %d, %d, %d, %d, " I64FMTD ", %d)}"), 
		bType, nItemID, sCount, sDurability, nSerialNum, nCoins)))
	{
		ReportSQLError(m_GameDB->GetError());
		return 0;
	}

	return bRet;
}

bool CDBAgent::ReadLetter(string & strCharID, uint32 nLetterID, string & strMessage)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	if (!dbCommand->Execute(string_format(_T("{CALL MAIL_BOX_READ(?, %d)}"), nLetterID)))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	if (!dbCommand->hasData())
		return false;

	dbCommand->FetchString(1, strMessage);
	return true;
}

int8 CDBAgent::GetItemFromLetter(string & strCharID, uint32 nLetterID, uint32 & nItemID, uint16 & sCount, uint16 & sDurability, uint32 & nCoins, uint64 & nSerialNum)
{
	int8 bRet = -1; // error
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	if (!dbCommand->Execute(string_format(_T("{? = CALL MAIL_BOX_GET_ITEM(?, %d)}"), nLetterID)))
		ReportSQLError(m_GameDB->GetError());

	if (dbCommand->hasData())
	{
		dbCommand->FetchUInt32(1, nItemID);
		dbCommand->FetchUInt16(2, sCount);
		dbCommand->FetchUInt16(3, sDurability);
		dbCommand->FetchUInt32(4, nCoins);
		dbCommand->FetchUInt64(5, nSerialNum);
	}

	return bRet=1;
}

//Added by Obede (fix letter delete when error)
int8 CDBAgent::UpdateItemFromLetter(string & strCharID, uint32 nLetterID, uint32 & nItemID, uint16 & sCount, uint16 & sDurability, uint32 & nCoins, uint64 & nSerialNum)
{
	int8 bRet = -1; // error
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return bRet;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	if (!dbCommand->Execute(string_format(_T("{? = CALL MAIL_BOX_UPDATE_ITEM_RECEIVED(?, %d)}"), nLetterID)))
		ReportSQLError(m_GameDB->GetError());

	if (dbCommand->hasData())
	{
		dbCommand->FetchUInt32(1, nItemID);
		dbCommand->FetchUInt16(2, sCount);
		dbCommand->FetchUInt16(3, sDurability);
		dbCommand->FetchUInt32(4, nCoins);
		dbCommand->FetchUInt64(5, nSerialNum);
	}

	return bRet=1;
}

void CDBAgent::DeleteLetter(string & strCharID, uint32 nLetterID)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	// NOTE: The official implementation passes all 5 letter IDs.
	if (!dbCommand->Execute(string_format(_T("UPDATE MAIL_BOX SET bDeleted = 1 WHERE nLetterID = %d AND strRecipientID = ?"), nLetterID)))
		ReportSQLError(m_GameDB->GetError());
}

/**
* @brief	Updates the election status.
*
* @param	byType  	Election status.
* @param	byNation	Electoral nation.
*/
void CDBAgent::UpdateElectionStatus(uint8 byType, uint8 byNation)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	if (!dbCommand->Execute(string_format(_T("{CALL KING_UPDATE_ELECTION_STATUS(%d, %d)}"), byType, byNation)))
		ReportSQLError(m_GameDB->GetError());
}

/**
* @brief	Updates the election list.
*
* @param	byDBType  	Procedure-specific database action.
* 						If 1, insert. If 2, delete.
* @param	byType	  	Flag to specify what the user's in the election list for (election, impeachment, and thereof).
* @param	byNation  	Electoral nation.
* @param	sKnights  	The nominee's clan ID.
* @param	nAmount		Vote count.
* @param	strNominee	The nominee's name.
*/
void CDBAgent::UpdateElectionList(uint8 byDBType, uint8 byType, uint8 byNation, uint16 sKnights, uint32 nAmount, string & strNominee, CUser * pUser)
{
	int16 sRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr || pUser == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &sRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->m_strAccountID.c_str(), pUser->m_strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->GetName().c_str(), pUser->GetName().length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strNominee.c_str(), strNominee.length());

	if (!dbCommand->Execute(string_format(_T("{? = CALL KING_ELECTION_PROC(?, ?, %d, ?, %d)}"), pUser->GetNation(), sRet)))
		ReportSQLError(m_GameDB->GetError());

	Packet result(WIZ_KING, uint8(1));
	result << byType << uint8(2) << sRet;
	pUser->Send(&result);
}

int16 CDBAgent::UpdateElectionProc(CUser *pUser)
{
	int16 sRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr || pUser == nullptr)
		return sRet;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &sRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->m_strAccountID.c_str(), pUser->m_strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->GetName().c_str(), pUser->GetName().length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, pUser->GetName().c_str(), pUser->GetName().length());

	if (!dbCommand->Execute(string_format(_T("{? = CALL KING_ELECTION_PROC(?, ?, %d, ?, 0)}"),pUser->GetNation())))
		ReportSQLError(m_GameDB->GetError());

	return sRet;
}

void CDBAgent::SendUDP_ElectionStatus(uint8 m_byType)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;
	
	if (!dbCommand->Execute(string_format(_T("UPDATE KING_SYSTEM SET byType = %d"), m_byType)))
	ReportSQLError(m_GameDB->GetError());
}


/**
* @brief	Nominates/recommends strNominee as King.
*
* @param	strNominator	The nominator.
* @param	strNominee  	The nominee.
* @param	byNation		Their nation.
*
* @return	.
*/
int16 CDBAgent::UpdateCandidacyRecommend(std::string & strNominator, std::string & strNominee, uint8 byNation)
{
	int16 sRet = -1;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return sRet;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &sRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strNominee.c_str(), strNominee.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strNominator.c_str(), strNominator.length());

	if (!dbCommand->Execute(string_format(_T("{? = CALL KING_CANDIDACY_RECOMMEND(?, ?, %d, 0)}"), byNation)))
		ReportSQLError(m_GameDB->GetError());

	return sRet;
}

/**
* @brief	Updates the candidacy notice board.
*
* @param	strCharID	Candidate's name.
* @param	byNation 	Candidate's nation.
* @param	strNotice	The notice.
*/
void CDBAgent::UpdateCandidacyNoticeBoard(string & strCharID, uint8 byNation, string & strNotice)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	// Field is 1024 bytes in the database.
	uint8 strBinaryNotice[1024] = {0};
	uint16 sNoticeLen = strNotice.length();

	// This shouldn't happen, but... in the horribly unlikely event it does... we're ready.
	if (sNoticeLen > sizeof(strBinaryNotice))
		sNoticeLen = sizeof(strBinaryNotice);

	memcpy(strBinaryNotice, strNotice.c_str(), sNoticeLen);

	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strBinaryNotice, sizeof(strBinaryNotice));

	if (!dbCommand->Execute(string_format(_T("{CALL KING_CANDIDACY_NOTICE_BOARD_PROC(?, %d, %d, ?)}"), 
		sNoticeLen, byNation)))
		ReportSQLError(m_GameDB->GetError());
}

void CDBAgent::UpdateNoahOrExpEvent(uint8 byType, uint8 byNation, uint8 byAmount, uint8 byDay, uint8 byHour, uint8 byMinute, uint16 sDuration)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	if (!dbCommand->Execute(string_format(_T("{CALL KING_UPDATE_NOAH_OR_EXP_EVENT(%d, %d, %d, %d, %d, %d, %d)}"), 
		byType, byNation, byAmount, byDay, byHour, byMinute, sDuration)))
		ReportSQLError(m_GameDB->GetError());
}

void CDBAgent::InsertPrizeEvent(uint8 byType, uint8 byNation, uint32 nCoins, std::string & strCharID)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	if (!dbCommand->Execute(string_format(_T("{CALL KING_INSERT_PRIZE_EVENT(%d, %d, %d, ?)}"), 
		byType, byNation, nCoins)))
		ReportSQLError(m_GameDB->GetError());
}

void CDBAgent::InsertTaxEvent(uint8 KingNationTax, uint8 Nation, uint32 TerritoryTax)
{	
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	if (TerritoryTax > 0)
	{
		if (!dbCommand->Execute(string_format(_T("UPDATE KING_SYSTEM SET nTerritoryTax -= %d WHERE byNation = %d"), TerritoryTax, Nation)))
		ReportSQLError(m_GameDB->GetError());
	}
	else
	{
		if (!dbCommand->Execute(string_format(_T("UPDATE KING_SYSTEM SET byTerritoryTariff = %d WHERE byNation = %d"), KingNationTax, Nation)))
		ReportSQLError(m_GameDB->GetError());
	}
}

void CDBAgent::InsertTaxUpEvent(uint8 Nation, uint32 TerritoryTax)
{	
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;
	if (Nation == ZONE_ELMORAD || Nation == ZONE_ELMORAD2 || Nation == ZONE_ELMORAD3
		|| Nation == ZONE_KARUS || Nation == ZONE_KARUS2 || Nation == ZONE_KARUS3)
	{
		if (!dbCommand->Execute(string_format(_T("UPDATE KING_SYSTEM SET nTerritoryTax += %d WHERE byNation = %d"), TerritoryTax, Nation)))
		ReportSQLError(m_GameDB->GetError());

		if (!dbCommand->Execute(string_format(_T("UPDATE KING_SYSTEM SET nNationalTreasury += %d WHERE byNation = %d"), TerritoryTax, Nation)))
		ReportSQLError(m_GameDB->GetError());
	}
	else if (Nation == ZONE_MORADON || Nation == ZONE_MORADON2
		|| Nation == ZONE_MORADON3 || Nation == ZONE_MORADON4
		|| Nation == ZONE_MORADON5)
	{
		if (!dbCommand->Execute(string_format(_T("UPDATE KNIGHTS_SIEGE_WARFARE SET nMoradonTax += %d WHERE sCastleIndex = 1"), TerritoryTax)))
		ReportSQLError(m_GameDB->GetError());
	}
	else if (Nation == ZONE_DELOS)
	{
		if (!dbCommand->Execute(string_format(_T("UPDATE KNIGHTS_SIEGE_WARFARE SET nDellosTax += %d WHERE sCastleIndex = 1"), TerritoryTax)))
		ReportSQLError(m_GameDB->GetError());
	}
}

/**
* @brief	Resets the monthly NP total accumulated in the last month.
*/
void CDBAgent::ResetLoyaltyMonthly()
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	if (!dbCommand->Execute(_T("{CALL RESET_LOYALTY_MONTHLY}")))
		ReportSQLError(m_GameDB->GetError());
}

/**
* @brief	Clears the remaining users who were connected to this server
from the logged in user list that may still be there as the 
result of an improper shutdown.
*/
void CDBAgent::ClearRemainUsers()
{
	_ZONE_SERVERINFO * pInfo = g_pMain->m_ServerArray.GetData(g_pMain->m_nServerNo);
	if (pInfo == nullptr)
		return;

	unique_ptr<OdbcCommand> dbCommand(m_AccountDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, pInfo->strServerIP.c_str(), pInfo->strServerIP.length());
	if (!dbCommand->Execute(_T("{CALL CLEAR_REMAIN_USERS(?)}")))
		ReportSQLError(m_AccountDB->GetError());
}

void CDBAgent::InsertUserDailyOp(_USER_DAILY_OP * pUserDailyOp)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, pUserDailyOp->strUserId.c_str(), pUserDailyOp->strUserId.length());
	if (!dbCommand->Execute(string_format(_T("{CALL INSERT_USER_DAILY_OP(?, %d, %d, %d, %d, %d, %d, %d, %d)}"), 
		pUserDailyOp->ChaosMapTime, pUserDailyOp->UserRankRewardTime, pUserDailyOp->PersonalRankRewardTime, pUserDailyOp->KingWingTime)))
		ReportSQLError(m_GameDB->GetError());	
}

void CDBAgent::UpdateUserDailyOp(std::string strUserId, uint8 type, int32 sUnixTime)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strUserId.c_str(), strUserId.length());
	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_USER_DAILY_OP(?, %d, %d)}"), type, sUnixTime)))
		ReportSQLError(m_GameDB->GetError());	
}

void CDBAgent::UpdateRanks()
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	if (!dbCommand->Execute(_T("{CALL UPDATE_RANKS}")))
		ReportSQLError(m_GameDB->GetError());
}

bool CDBAgent::GetAllCharInfo(string & strCharID, uint16 & nNum, _NATION_DATA* &m_NationTransfer)
{
	string dCharName;
	uint8 dRace;
	uint8 dNation;
	uint16 dClass;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());

	if (!dbCommand->Execute(_T("SELECT strUserID, Race, Nation, Class FROM USERDATA WHERE strUserID = ?")))
		ReportSQLError(m_GameDB->GetError());


	if (dbCommand->hasData())
	{
		dbCommand->FetchString(1, dCharName);
		dbCommand->FetchByte(2, dRace);
		dbCommand->FetchByte(3, dNation);
		dbCommand->FetchUInt16(4, dClass);
	}
	else // si no tiene data, si STRUserID1 o StrUserID2 ,... es NULL
		return false;

	_NATION_DATA*  m_Transfer = new _NATION_DATA;

	m_Transfer->nNum = nNum;
	m_Transfer->bCharName = dCharName;
	m_Transfer->bRace = dRace;
	m_Transfer->bNation = dNation;
	m_Transfer->sClass = dClass;

	m_NationTransfer = m_Transfer;

	nNum++;
	return true;
}


int8 CDBAgent::NationTransferValidate(std::string strCharID)
{
	int8 error = 3;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;
	
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &error);

	if (!dbCommand->Execute(_T("{CALL NATION_TRANS_VALID(?, ?)}")))
		ReportSQLError(m_GameDB->GetError());

	return error;
}

int8 CDBAgent::NationTransferSave(string strAccountID, string kCharID, uint8 kNewRace, uint8 kNation, uint16 kClass, CUser * pUser)
{
	int Px = 81800;
	int	Pz = 43500;
	int	Py = 469;
	uint32 pHair = 0;
	uint8 pFace = 0;

	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, kCharID.c_str(), kCharID.length());

	if (!dbCommand->Execute(string_format(_T("{CALL NATION_TRANS_SAVE("
		"?, ?, "				// AccountID, UserID
		"%d, %d, %d, "			// NewRace, NewNation, NewClass
		"%d, %d, "				// Hair, Face
		"%d, %d, %d)}"),		// PX, PZ, PY			
		kNewRace, kNation, kClass, pHair, pFace, Px, Pz, Py)))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	return true;
}

int8 CDBAgent::NationTransfer(std::string strAccountID, std::string strCharID)
{
	int8 bRet = 3;
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_OUTPUT, &bRet);
	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());

	if (!dbCommand->Execute(_T("{? = CALL ACCOUNT_NATION_TRANSFER(?, ?)}")))
		ReportSQLError(m_GameDB->GetError());

	return bRet;
}

/**
* @brief	Change knight cash is account.
*
* @param	strAccountID	Character's Account name.
* @param	KnightCash		Added knight cash amount
*/
void CDBAgent::UpdateAccountKnightCash(string & strAccountID, uint32 KnightCash)
{
	unique_ptr<OdbcCommand> dbCommand(m_AccountDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strAccountID.c_str(), strAccountID.length());
	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_KNIGHT_CASH (?, %d)}"), KnightCash)))
		ReportSQLError(m_AccountDB->GetError());	
}

bool CDBAgent::GetClanUserData(uint16 sClanID, _KNIGHTS_USER* p)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, p->strUserName.c_str(), p->strUserName.length());
	if (!dbCommand->Execute(string_format(_T("SELECT Fame, [Level], Class, strMemo FROM USERDATA WHERE Knights = %d AND strUserID = ?"), sClanID)))
		ReportSQLError(m_GameDB->GetError());

	if (!dbCommand->hasData())
		return false;

	do
	{
		dbCommand->FetchByte(1,p->m_sFame);
		 dbCommand->FetchByte(2,p->m_bLevel);
		 dbCommand->FetchUInt16(3, p->m_sClass);
		 dbCommand->FetchString(4, p->strUserMemo);

	} while (dbCommand->MoveNext());

	return true;
}

void CDBAgent::UpdateSiege(int16 m_sCastleIndex, int16 m_sMasterKnights, int16 m_bySiegeType, int16 m_byWarDay, int16 m_byWarTime, int16 m_byWarMinute)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_SIEGE (%d, %d, %d, %d, %d, %d)}"), m_sCastleIndex, m_sMasterKnights, m_bySiegeType, m_byWarDay, m_byWarTime, m_byWarMinute)))
		ReportSQLError(m_AccountDB->GetError());	
}

void CDBAgent::UpdateSiegeTax(uint8 Zone, int16 ZoneTarrif)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;
	if (Zone == ZONE_DELOS)
	{
	if (!dbCommand->Execute(string_format(_T("UPDATE KNIGHTS_SIEGE_WARFARE SET sMoradonTariff = %d"), ZoneTarrif)))
		ReportSQLError(m_GameDB->GetError());
	}
	else if (Zone == ZONE_MORADON || Zone == ZONE_MORADON2
		|| Zone == ZONE_MORADON3 || Zone == ZONE_MORADON4
		|| Zone == ZONE_MORADON5)
	{
	if (!dbCommand->Execute(string_format(_T("UPDATE KNIGHTS_SIEGE_WARFARE SET sDellosTariff = %d"), ZoneTarrif)))
		ReportSQLError(m_GameDB->GetError());
	}
	else if (Zone == 0)
	{
	if (!dbCommand->Execute(string_format(_T("UPDATE KNIGHTS_SIEGE_WARFARE SET nDungeonCharge = 0, nMoradonTax = 0, nDellosTax = 0"))))
		ReportSQLError(m_GameDB->GetError());
	}
}

bool CDBAgent::LoadSealInfo(string & CharID, uint8 & blevel, uint16 & bExp, uint8 & bRace, uint16 & bJob, uint8 & STR, uint8 & STA, uint8 & DEX, uint8 & INT, uint8 & CHA, uint32 & nGold, ByteBuffer & SkillArray, ByteBuffer & bstrItem)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, CharID.c_str(), CharID.length());

	if (!dbCommand->Execute(_T("{CALL LOAD_SEAL_USER(?)}")))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	if (!dbCommand->hasData())
		return false;

	char stritem[INVENTORY_COSP * 9] = { 0 }, strSkill[10] = {0};

	uint64 OrigExp = 0;
	bExp = 5000;

	int u = 1;
	dbCommand->FetchByte(u++, blevel);
	dbCommand->FetchUInt64(u++, OrigExp);
	dbCommand->FetchByte(u++, bRace);
	dbCommand->FetchUInt16(u++, bJob);
	dbCommand->FetchByte(u++, STR);
	dbCommand->FetchByte(u++, STA);
	dbCommand->FetchByte(u++, DEX);
	dbCommand->FetchByte(u++, INT);
	dbCommand->FetchByte(u++, CHA);
	dbCommand->FetchUInt32(u++, nGold);
	dbCommand->FetchBinary(u++, strSkill, sizeof(strSkill));
	dbCommand->FetchBinary(u++, stritem, sizeof(stritem));

	SkillArray.append(strSkill, sizeof(strSkill));
	bstrItem.append(stritem, sizeof(stritem));

	return true;
}

bool CDBAgent::CharacterSealSave(string strCharID, uint64 bSerial, uint32 SealSerial, uint8 bRaceSatis, uint16 sClass, uint8 bLevel, uint16 pExp, uint8 & STR, uint8 & STA, uint8 & DEX, uint8 & INT, uint8 & CHA, uint32 & nGold, ByteBuffer & bstrSkill, ByteBuffer & bstrItem)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	ByteBuffer rSerial;
	rSerial << bSerial;

	dbCommand->AddParameter(SQL_PARAM_INPUT, strCharID.c_str(), strCharID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)rSerial.contents(), rSerial.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)bstrSkill.contents(), bstrSkill.size(), SQL_BINARY);
	dbCommand->AddParameter(SQL_PARAM_INPUT, (char *)bstrItem.contents(), bstrItem.size(), SQL_BINARY);

	if (!dbCommand->Execute(string_format(_T("{CALL INSERT_USER_SEALED(?, ?, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, ?, ?)}"), 
		SealSerial, bRaceSatis, sClass, bLevel, pExp, STR, STA, DEX, INT, CHA, nGold)))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	_SPECIAL_ITEM * pData = new _SPECIAL_ITEM;

	pData->SealSerial = SealSerial;
	pData->sCharID = strCharID;
	pData->iSerial = bSerial;
	pData->bRaceSatis = bRaceSatis;
	pData->sClass = sClass;
	pData->bLevel = bLevel;
	pData->sExpPercent = pExp;
	pData->Stat_STR = STR;
	pData->Stat_STA = STA;
	pData->Stat_DEX = DEX;
	pData->Stat_INT = INT;
	pData->Stat_CHA = CHA;
	pData->sGold = nGold;

	pData->Skill_Points[0] = bstrSkill[0] + bstrSkill[1] + bstrSkill[2] + bstrSkill[3] + bstrSkill[4];
	pData->Skill_Points[1] = bstrSkill[5];
	pData->Skill_Points[2] = bstrSkill[6];
	pData->Skill_Points[3] = bstrSkill[7];
	pData->Skill_Points[4] = bstrSkill[8];

	for (int i = 0; i < INVENTORY_COSP; i++)
	{
		uint32 rNum;
		uint16 nDuration, nCount;

		bstrItem >> rNum >> nDuration >> nCount;

		_ITEM_TABLE *pTable = g_pMain->GetItemPtr(rNum);
		if (pTable == nullptr || nCount <= 0)
			continue;

		if (!pTable->m_bCountable && nCount > 1)
			nCount = 1;
		else if (nCount > ITEMCOUNT_MAX)
			nCount = ITEMCOUNT_MAX;

		pData->Item_Num[i] = rNum;
		pData->Item_Duration[i] = nDuration;
		pData->Item_Count[i] = nCount;
		pData->Item_Flag[i] = ITEM_FLAG_CHAR_SEAL;
	}

	g_pMain->m_SpecialItemArray.PutData(pData->SealSerial, pData);

	return true;
}

bool CDBAgent::CharacterSealDelete(string CharID)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return false;

	dbCommand->AddParameter(SQL_PARAM_INPUT, CharID.c_str(), CharID.length());

	if (!dbCommand->Execute(_T("DELETE FROM SPECIAL_ITEM WHERE strUserID = ?")))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	return true;
}

void CDBAgent::UpdateAccountChar(string AccountID, string strChardID, uint8 bRent/* = 0*/)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	dbCommand->AddParameter(SQL_PARAM_INPUT, AccountID.c_str(), AccountID.length());
	dbCommand->AddParameter(SQL_PARAM_INPUT, strChardID.c_str(), strChardID.length());

	if (!dbCommand->Execute(string_format(_T("{CALL UPDATE_ACCOUNT_CHAR(?, ?, %d)}"), bRent)))
		ReportSQLError(m_GameDB->GetError());
}

void CDBAgent::LoadSealPasswd(std::string AccountID, std::string & strPasswd)
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());
	if (dbCommand.get() == nullptr)
		return;

	char strPass[8] = {0};

	dbCommand->AddParameter(SQL_PARAM_INPUT, AccountID.c_str(), AccountID.length());

	if (!dbCommand->Execute(_T("{CALL LOAD_SEAL_PASSWD(?)}")))
		ReportSQLError(m_GameDB->GetError());

	dbCommand->FetchString(1, strPasswd);
}