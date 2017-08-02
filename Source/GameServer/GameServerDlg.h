#pragma once

#ifdef GAMESERVER

#include "resource.h"
#include "LuaEngine.h"

#include "Define.h"
#include "ChatHandler.h"

class C3DMap;
class CUser;

#include "LoadServerData.h"

#include "User.h"
#include "AISocket.h"
#include "../shared/ClientSocketMgr.h"

typedef std::map<std::string, CUser *>  NameMap;
typedef  std::map<uint16, uint16>          ForgettenTempleMonsterList;

class CGameServerDlg
{
public:	
	CGameServerDlg();
	bool Startup();

	bool LoadAchieveCom();
	bool LoadAchieveMain();
	bool LoadAchieveMon();
	bool LoadAchieveNormal();
	bool LoadAchieveTitle();
	bool LoadAchieveWar();

	void GetTimeFromIni();
	void GetMineItem();
	void GetFishItem();
	void GetEventTime();

	bool LoadItemTable();
	bool LoadSetItemTable();
	bool LoadItemDuper();
	bool LoadIlegalItems();
	bool LoadItemExchangeTable();
	bool LoadItemUpgradeTable();
	bool LoadItemOpTable();
	bool LoadExpiration();
	bool LoadServerResourceTable();
	bool LoadQuestHelperTable();
	bool LoadQuestMonsterTable();
	bool LoadMagicTable();
	bool LoadMagicType1();
	bool LoadMagicType2();
	bool LoadMagicType3();
	bool LoadMagicType4();
	bool LoadMagicType5();
	bool LoadMagicType6();
	bool LoadMagicType7();
	bool LoadMagicType8();
	bool LoadMagicType9();
	bool LoadRentalList();
	bool LoadCoefficientTable();
	bool LoadLevelUpTable();
	bool LoadAllKnights(bool bIsslient = false);
	bool LoadAllKnightsUserData(bool bIsslient = false);
	bool LoadKnightsAllianceTable(bool bIsslient = false);
	bool LoadKnightsSiegeWarsTable();
	bool LoadUserRankings();
	void CleanupUserRankings();
	bool LoadKnightsCapeTable();
	bool LoadKnightsRankTable(bool bWarTime = false, bool bIsslient = false);
	bool LoadStartPositionTable();
	bool LoadStartPositionRandomTable();
	bool LoadBattleTable();
	bool LoadKingSystem();
	bool LoadMonsterSummonListTable();
	bool LoadMonsterSummonListZoneTable();
	bool LoadMonsterRespawnListTable();
	bool LoadMonsterRespawnListInformationTable();
	bool LoadPremiumItemTable();
	bool LoadPremiumItemExpTable();
	bool LoadUserDailyOpTable();
	bool LoadEventTriggerTable();
	bool LoadMonsterChallengeTable();
	bool LoadEventTimesTable();
	bool LoadMonsterChallengeSummonListTable();
	bool LoadUserItemTable();
	bool LoadObjectPosTable();

	bool MapFileLoad();
	bool LoadNoticeData();
	bool LoadNoticeUpData();
	void AIServerConnect();

	static uint32 THREADCALL Timer_CheckGameEvents(void * lpParam);
	static uint32 THREADCALL Timer_BifrostTime(void * lpParam);
	static uint32 THREADCALL Timer_UpdateGameTime(void * lpParam);
	static uint32 THREADCALL Timer_UpdateSessions(void * lpParam);
	static uint32 THREADCALL Timer_UpdateConcurrent(void * lpParam);

	void ReqUpdateConcurrent();

	void SendFlyingSantaOrAngel();
	void BattleZoneCurrentUsers();
	void GetCaptainUserPtr();
	void Send_CommandChat(Packet *pkt, int nation, CUser* pExceptUser = nullptr);
	void SendItemZoneUsers(uint8 ZoneID, uint32 nItemID, uint16 sCount = 1, uint32 Time = 0);
	void KickOutZoneUsers(uint8 ZoneID, uint8 TargetZoneID = 0, uint8 bNation = 0);
	void SendItemEventRoom(uint16 nEventRoom,uint32 nItemID, uint16 sCount = 1);
	uint64 GenerateItemSerial();
	int KickOutAllUsers();
	void CheckAliveUser();
	int GetKnightsGrade(uint32 nPoints);
	void WritePacketLog();
	uint16 GetKnightsAllMembers(uint16 sClanID, Packet & result, uint16 & pktSize, bool bClanLeader);
	void GetUserRank(CUser *pUser);
	void Announcement(uint16 type, int nation=0, int chat_type=8, CUser* pExceptUser = nullptr, CNpc *pExpectNpc = nullptr);
	void NoahKnights(Packet * pkt);
	void SnowBattleZoneCurrentUsers();
	void SnowBanishLosers();
	void SnowBattleZoneClose();
	void SnowBattleZoneOpenTimer();
	void ResetBattleZone();
	void BanishLosers();
	void BattleZoneVictoryCheck();
	void BattleZoneOpenTimer();
	void BattleZoneOpen(int nType, uint8 bZone = 0);
	void CastleSiegeWarZoneOpen(int nType, uint8 bZone = 0);
	void LunarGoldShells();
    void DeleteLunarGoldShells();
	void BattleZoneClose();
	void BattleZoneResult(uint8 nation, CUser* pUser = nullptr);
	void BattleWinnerResult(BattleWinnerTypes winnertype);
	void AliveUserCheck();
	void TerminationFinish();
	void Send_PartyMember(int party, Packet *result);
	void Send_KnightsMember(int index, Packet *pkt);
	void Send_KnightsAlliance(uint16 sAllianceID, Packet *pkt);
	void SetGameTime();
	void ResetPlayerRankings(uint8 ZoneID = 0);
	void UpdateWeather();
	void UpdateGameTime();
	void ResetLoyaltyMonthly();
	void SendAllUserInfo();
	void DeleteAllNpcList(int flag = 0);
	CNpc*  FindNpcInZone(uint16 sPid, uint8 byZone);
	CNpc* UpdateNpc();
	void ForgettenTempleEventTimer();
	void CastleSiegeWarOpenTimer();
	uint8 GetMonsterChallengeTime();
	time_t	m_lastBlessTime;
	time_t	m_lastBorderTime;
	time_t	m_lastCrystalKilled;
	time_t	m_CastleAnnounceTime;
	uint8 GetEventZoneTime();
	void TempleEventTimer();
	void TempleEventStart();
	void JuraidTempleEventStart();
	void TempleEventTeleportUsers();
	uint8 TempleEventGetRoomUsers(uint16 nEventRoom = 0);
	void TempleEventSummon();
	void TempleEventSummonChaosCubes();
	void TempleEventFinish(uint16 m_sEventRoom = 0, uint8 m_bNation = 0);
	void TempleEventGetActiveEventTime(CUser *pUser);
	void TempleEventSendActiveEventTime(CUser *pUser);
	void TempleEventKickOutUser(CUser *pUser);
	void TempleEventReset();
	void AddEventUser(CUser * pUser);
	void RemoveEventUser(CUser * pUser);
	void UpdateEventUser(CUser * pUser, uint16 nEventRoom = 0);
	void SetEventUser(CUser *pUser);
	std::string GetBattleAndNationMonumentName(int16 TrapNumber = -1, uint8 ZoneID = 0);
	void CheckNationMonumentRewards();
	void BorderMonumentBosses();

	void Yaz(char* yazi,WORD color);
	void color_c(char* buff,WORD color);
	void SendConsoleFAIL();
	void SendConsoleOK();

	void ReloadKnightAndUserRanks();
	void SetPlayerRankingRewards(uint16 ZoneID);

	bool CastleSiegeWarAttack(CUser *pUser, CUser *pTargetUser);
	void UpdateSiege(int16 m_sCastleIndex, int16 m_sMasterKnights, int16 m_bySiegeType, int16 m_byWarDay, int16 m_byWarTime, int16 m_byWarMinute);
	void UpdateSiegeTax(uint8 Zone, int16 ZoneTarrif);

	bool IsDuplicateItem(uint32 nItemID, uint64 nItemSerial);
	void AddUserItem(uint32 nItemID, uint64 nItemSerial);

	void AddDatabaseRequest(Packet & pkt, CUser *pUser = nullptr);
	// TerminitionTime

	void TerminitionTime(uint8 sNewZone,uint16 Time);

	// Get info for NPCs in regions around user (WIZ_REQ_NPCIN)
	void NpcInOutForMe(CUser* pSendUser);

	// Get info for NPCs in region
	void GetRegionNpcIn(C3DMap* pMap, uint16 region_x, uint16 region_z, Packet & pkt, uint16 & t_count, uint16 nEventRoom, CUser* pSendUser);

	// Get list of NPC IDs in region
	void GetRegionNpcList(C3DMap* pMap, uint16 region_x, uint16 region_z, Packet & pkt, uint16 & t_count, uint16 nEventRoom = 0);

	// Get list of NPCs for regions around user (WIZ_NPC_REGION)
	void RegionNpcInfoForMe(CUser* pSendUser);	

	// Get raw list of all units in regions surrounding pOwner.
	void GetUnitListFromSurroundingRegions(Unit * pOwner, std::vector<uint16> * pList);

	// Get info for users in regions around user (WIZ_REQ_USERIN)
	void UserInOutForMe(CUser* pSendUser);

	// Get info for users in region
	void GetRegionUserIn(C3DMap* pMap, uint16 region_x, uint16 region_z, Packet & pkt, uint16 & t_count, uint16 nEventRoom = 0);

	// Get list of user IDs in region
	void GetRegionUserList(C3DMap* pMap, uint16 region_x, uint16 region_z, Packet & pkt, uint16 & t_count, uint16 nEventRoom = 0);

	// Get list of users for regions around user (WIZ_REGIONCHANGE)
	void RegionUserInOutForMe(CUser* pSendUser);

	// Get info for merchants in regions around user
	void MerchantUserInOutForMe(CUser* pSendUser);

	// Get war status
	INLINE bool isWarOpen() { return m_byBattleOpen != NO_BATTLE;} 

	// Get list of merchants in region
	void GetRegionMerchantUserIn(C3DMap* pMap, uint16 region_x, uint16 region_z, Packet & pkt, uint16 & t_count, uint16 nEventRoom = 0);

	void SendHelpDescription(CUser *pUser, std::string sHelpMessage);

	INLINE bool isPermanentMessageSet() { return m_bPermanentChatMode; }
	void SetPermanentMessage(const char * format, ...);

	void HandleConsoleCommand(const char * msg);

	template <ChatType chatType>
	INLINE void SendChat(const char * msg, uint8 byNation = Nation::ALL, bool bFormatNotice = false)
	{
		Packet result;
		std::string buffer;

		if (bFormatNotice)
			GetServerResource(IDP_ANNOUNCEMENT, &buffer, msg);
		else
			buffer = msg;

		ChatPacket::Construct(&result, (uint8) chatType, &buffer);
		Send_All(&result, nullptr, byNation);
	}

	template <ChatType chatType>
	INLINE void SendChatToZone(const char * msg, uint8 ZoneID, uint8 byNation = Nation::ALL, bool bFormatNotice = false)
	{
		Packet result;
		std::string buffer;

		if (bFormatNotice)
			GetServerResource(IDP_ANNOUNCEMENT, &buffer, msg);
		else
			buffer = msg;

		ChatPacket::Construct(&result, (uint8) chatType, &buffer);
		Send_Zone(&result, ZoneID, nullptr, byNation);
	}

	template <ChatType chatType>
	INLINE void SendFormattedChat(const char * msg, uint8 byNation = Nation::ALL, bool bFormatNotice = false, va_list args = nullptr)
	{
		char buffer[512];
		vsnprintf(buffer, sizeof(buffer), msg, args);
		SendChat<chatType>(buffer, byNation, bFormatNotice);
		va_end(args);
	}

	template <ChatType chatType>
	void SendFormattedChat(const char * msg, uint8 byNation = Nation::ALL, bool bFormatNotice = false, ...)
	{
		va_list ap;
		va_start(ap, byNation);
		SendFormattedChat<chatType>(msg, byNation, bFormatNotice, ap);
		va_end(ap);
	}

	/* The following are simply wrappers for more readable SendChat() calls */

	INLINE void SendNotice(const char *msg, uint8 byNation = Nation::ALL) 
	{
		SendChat<PUBLIC_CHAT>(msg, byNation, true);
	}

	template <ChatType chatType>
	INLINE void SendNotice(const char *msg, uint8 ZoneID, uint8 byNation = Nation::ALL, bool bFormatNotice = false)
	{
		SendChatToZone<chatType>(msg, ZoneID, byNation, bFormatNotice);
	}

	void SendFormattedNotice(const char *msg, uint8 byNation = Nation::ALL, ...)
	{
		va_list ap;
		va_start(ap, byNation);
		SendFormattedChat<PUBLIC_CHAT>(msg, byNation, true, ap);
		va_end(ap);
	}

	INLINE void SendAnnouncement(const char *msg, uint8 byNation = Nation::ALL)
	{
		SendChat<WAR_SYSTEM_CHAT>(msg, byNation, true);
	}

	void SendFormattedAnnouncement(const char *msg, uint8 byNation = Nation::ALL, ...)
	{
		va_list ap;
		va_start(ap, byNation);
		SendFormattedChat<WAR_SYSTEM_CHAT>(msg, byNation, true, ap);
		va_end(ap);
	}

	void SendFormattedResource(uint32 nResourceID, uint8 byNation = Nation::ALL, bool bIsNotice = true, ...);

	void Send_Region(Packet *pkt, C3DMap *pMap, int x, int z, CUser* pExceptUser = nullptr, uint16 nEventRoom = 0);
	void Send_UnitRegion(Packet *pkt, C3DMap *pMap, int x, int z, CUser* pExceptUser = nullptr, uint16 nEventRoom = 0);
	void Send_OldRegions(Packet *pkt, int old_x, int old_z, C3DMap *pMap, int x, int z, CUser* pExceptUser = nullptr, uint16 nEventRoom = 0);
	void Send_NewRegions(Packet *pkt, int new_x, int new_z, C3DMap *pMap, int x, int z, CUser* pExceptUser = nullptr, uint16 nEventRoom = 0);

	void Send_NearRegion(Packet *pkt, C3DMap *pMap, int region_x, int region_z, float curx, float curz, CUser* pExceptUser=nullptr, uint16 nEventRoom = 0);
	void Send_FilterUnitRegion(Packet *pkt, C3DMap *pMap, int x, int z, float ref_x, float ref_z, CUser* pExceptUser=nullptr, uint16 nEventRoom = 0);

	void Send_Zone_Matched_Class(Packet *pkt, uint8 bZoneID, CUser* pExceptUser, uint8 nation, uint8 seekingPartyOptions, uint16 nEventRoom = 0);
	void Send_Zone(Packet *pkt, uint8 bZoneID, CUser* pExceptUser = nullptr, uint8 nation = 0, uint16 nEventRoom = 0, float fRange = 0.0f);

	void Send_All(Packet *pkt, CUser* pExceptUser = nullptr, uint8 nation = 0, uint8 ZoneID = 0, bool isSendEventUsers = false, uint16 nEventRoom = 0);
	void Send_AIServer(Packet *pkt);

	void GetServerResource(int nResourceID, std::string * result, ...);
	_START_POSITION *GetStartPosition(int nZoneID);

	int64 GetExpByLevel(int nLevel);
	C3DMap * GetZoneByID(int zoneID);

	CUser * GetUserPtr(std::string findName, NameType type);
	CUser * GetUserPtr(uint16 sUserId);
	CNpc  * GetNpcPtr(uint16 sNpcId);

	Unit * GetUnitPtr(uint16 id);

	// Spawns an event NPC/monster
	void SpawnEventNpc(uint16 sSid, bool bIsMonster, uint8 byZone, float fX, float fY, float fZ, uint16 sCount = 1, uint16 sRadius = 0, uint16 sDuration = 0, uint8 nation = 0, int16 socketID = -1, uint16 nEventRoom = 0);

	// Kill a Npc/Monster
	void KillNpc(uint16 sNid);

	// Change NPC/Monster properties for Respawn
	void NpcUpdate(uint16 sSid, bool bIsMonster, uint8 byGroup = 0, uint16 sPid = 0);

	// Adds the account name & session to a hashmap (on login)
	void AddAccountName(CUser *pSession);

	// Adds the character name & session to a hashmap (when in-game)
	void AddCharacterName(CUser *pSession);

	// Removes an existing character name/session from the hashmap, replaces the character's name 
	// and reinserts the session with the new name into the hashmap.
	void ReplaceCharacterName(CUser *pSession, std::string & strNewUserID);

	// Removes the account name & character names from the hashmaps (on logout)
	void RemoveSessionNames(CUser *pSession);

	// Send to Zone NPC Effect
	void ShowNpcEffect(uint16 sNpcID, uint32 nEffectID, uint8 ZoneID);

	_PARTY_GROUP * GetPartyPtr(uint16 sPartyID);
	CKnights * GetClanPtr(uint16 sClanID);
	_KNIGHTS_ALLIANCE * GetAlliancePtr(uint16 sAllianceID);
	_ITEM_TABLE * GetItemPtr(uint32 nItemID);
	_KNIGHTS_SIEGE_WARFARE * GetSiegeMasterKnightsPtr(uint16 sMasterKnights);

	_PARTY_GROUP * CreateParty(CUser *pLeader);
	void DeleteParty(uint16 sIndex);

	_EVENT_STATUS pTempleEvent;

	~CGameServerDlg();

	char	m_ppNotice[20][128];
	char	m_peNotice[20][128];
	std::string	m_AIServerIP;
	uint32    m_AIServerPort;

	NpcArray							m_arNpcArray;
	ZoneArray							m_ZoneArray;
	ItemtableArray						m_ItemtableArray;
	SetItemArray						m_SetItemArray;
	MagictableArray						m_MagictableArray;
	Magictype1Array						m_Magictype1Array;
	Magictype2Array						m_Magictype2Array;
	Magictype3Array						m_Magictype3Array;
	Magictype4Array						m_Magictype4Array;
	Magictype5Array						m_Magictype5Array;
	Magictype6Array						m_Magictype6Array;
	Magictype7Array						m_Magictype7Array;
	Magictype8Array						m_Magictype8Array;
	Magictype9Array						m_Magictype9Array;
	CoefficientArray					m_CoefficientArray;
	LevelUpArray						m_LevelUpArray;
	PartyArray							m_PartyArray;
	KnightsArray						m_KnightsArray;
	KnightsRatingArray					m_KnightsRatingArray[2]; // one for both nations
	KnightsAllianceArray				m_KnightsAllianceArray;
	KnightsSiegeWarfareArray			m_KnightsSiegeWarfareArray;
	KnightsCapeArray					m_KnightsCapeArray;
	UserNameRankMap						m_UserPersonalRankMap;
	UserNameRankMap						m_UserKnightsRankMap;
	UserRankMap							m_playerRankings[2]; // one for both nations
	std::recursive_mutex				m_userRankingsLock;
	StartPositionArray					m_StartPositionArray;
	ServerResourceArray					m_ServerResourceArray;
	QuestHelperArray					m_QuestHelperArray;
	QuestNpcList						m_QuestNpcList;
	QuestMonsterArray					m_QuestMonsterArray;
	RentalItemArray						m_RentalItemArray;
	ItemExchangeArray					m_ItemExchangeArray;
	ItemUpgradeArray					m_ItemUpgradeArray;
	ItemOpArray							m_ItemOpArray;
	ItemDupersArray						m_ItemDupersArray;
	IlegalItemsArray					m_IlegalItemsArray;
	AchieveComArray						m_AchieveComArray;
	AchieveMainArray					m_AchieveMainArray;
	AchieveMonArray						m_AchieveMonArray;
	AchieveNormalArray					m_AchieveNormalArray;
	AchieveTitleArray					m_AchieveTitleArray;
	AchieveWarArray						m_AchieveWarArray;
	ExpirationArray						m_ExpirationArray;
	KingSystemArray						m_KingSystemArray;
	EventTriggerArray					m_EventTriggerArray;
	MonsterChallengeArray				m_MonsterChallengeArray;
	MonsterChallengeSummonListArray		m_MonsterChallengeSummonListArray;
	EventTimesArray						m_EventTimesArray;
	MonsterSummonListArray				m_MonsterSummonList;
	MonsterSummonListZoneArray			m_MonsterSummonListZoneArray;
	MonsterRespawnListArray				m_MonsterRespawnListArray;
	MonsterRespawnListInformationArray	m_MonsterRespawnListInformationArray;
	MineListArray						m_MineListArray;
	PremiumItemArray					m_PremiumItemArray;
	PremiumItemExpArray					m_PremiumItemExpArray;
	UserRankingArray					m_UserRankingArray[2];
	UserDailyOpMap						m_UserDailyOpMap;
	TempleEventUserArray				m_TempleEventUserArray;
	NationMonumentInformationArray		m_NationMonumentInformationArray;
	StartPositionRandomArray			m_StartPositionRandomArray;
	UserItemArray						m_UserItemArray;
	ObjectEventArray					m_ObjectEventArray;
	ChatRoomArray						m_ChatRoomArray;
	SpecialItemArray					m_SpecialItemArray;

	Atomic<uint16>				m_sPartyIndex;
	short	m_sZoneCount;							// AI Server 재접속시 사용

	bool	m_bFirstServerFlag;		// 서버가 처음시작한 후 게임서버가 붙은 경우에는 1, 붙지 않은 경우 0
	bool	m_bServerCheckFlag;
	bool	m_bPointCheckFlag;		// AI서버와 재접전에 NPC포인터 참조막기 (true:포인터 참조, false:포인터 참조 못함)
	short   m_sErrorSocketCount;  // 이상소켓 감시용

	uint16 m_sYear, m_sMonth, m_sDate, m_sHour, m_sMin, m_sSec;
	uint8 m_byWeather;
	uint16 m_sWeatherAmount;
	int m_nCastleCapture;
	uint8 m_ReloadKnightAndUserRanksMinute , m_DevakillSecond;

	uint8   m_byBattleOpen, m_byOldBattleOpen;
	uint8  m_byBattleZone, m_byBattleZoneType, m_bVictory, m_byOldVictory, m_bResultDelayVictory, m_bKarusFlag, m_bElmoradFlag, m_bMiddleStatueNation;
	int32	m_byBattleOpenedTime;
	int32	m_byBattleTime;
	int32	m_byBattleRemainingTime;
	int32	m_sBattleTimeDelay;
	int32  m_sBattleResultDelay;

	bool nFirst;

	int32	m_byBattleSiegeWarStartTime;
	uint8	m_SiegeWarNoticeTime;
	std::string	m_SiegeWarWinKnightsNotice;
	bool	m_byBattleSiegeWarOpen;
	bool	m_byBattleSiegeWarMomument;
	bool	m_byBattleSiegeWarTeleport;
	bool	m_byBattleSiegeWarTown;
	bool	AlreadySendAchieve;
	uint8	m_sKilledKarusNpc, m_sKilledElmoNpc;
	uint8	m_sKarusMonuments, m_sElmoMonuments;
	uint8	m_sKarusBdw, m_sElmoBdw;
	uint16  m_sKarusMonumentPoint, m_sElmoMonumentPoint;
	bool    m_byKarusOpenFlag, m_byElmoradOpenFlag, m_byBanishFlag, m_byBattleSave, m_bResultDelay, m_bySnowBanishFlag;
	short   m_sDiscount;
	short	m_sKarusDead, m_sElmoradDead, m_sBanishDelay, m_sKarusCount, m_sElmoradCount;
	std::string m_sBattleZoneOpenDays;
	std::string m_sEventZoneOpenDays1;
	std::string m_sEventZoneOpenDays2;
	std::string m_sEventZoneOpenDays3;
	uint8	m_nBattleZoneOpenHourStart[WAR_TIME_COUNT], m_nBattlezoneOpenWarZone[WAR_ZONE_COUNT];

	std::string m_strKarusCaptain, m_strElmoradCaptain;

	uint8   m_nBorderDefenseWarTime[BORDER_DEFENSE_WAR_EVENT_COUNT], m_nChaosTime[CHAOS_EVENT_COUNT], m_nJuraidTime[JURAD_MOUNTAIN_EVENT_COUNT], m_nUtcTime[UTC_EVENT_COUNT];
	uint8	m_nPVPMonumentNation[MAX_ZONE_ID];
	uint8	m_nEventMonumentNation[MAX_ZONE_ID];

	uint32  m_GameServerPort;
	int32	m_nGameMasterRHitDamage;
	int32	m_nGameMasterRHitDamageUser;
	int32	m_nBonusTimeInterval, m_nBonusTimeGold, m_nBonusPVPWarItem;
	uint16	m_CountofTickets;
	uint8	m_nPlayerRankingResetTime;
	int		m_upgrade1 , m_upgrade2;
	std::string  m_sPlayerRankingsRewardZones;
	uint32  m_nPlayerRankingKnightCashReward;
	uint32  m_nPlayerRankingLoyaltyReward,m_Grade1,m_Grade2,m_Grade3,m_Grade4;

	uint8 m_MerchantStatus;
    uint8 m_TradeStatus;

	//mining mattock
	uint32 m_Drop1,m_Drop2,m_Drop3,m_Drop4,m_Drop5,m_Drop6,m_Drop7,m_Drop8,m_Drop9,m_Drop10,m_Drop11,m_Drop12,m_Drop13,m_Drop14,m_Drop15,m_rainworm;
	//mining gold mattock
	uint32 m_gDrop1,m_gDrop2,m_gDrop3,m_gDrop4,m_gDrop5,m_gDrop6,m_gDrop7,m_gDrop8,m_gDrop9,m_gDrop10,m_gDrop11,m_gDrop12,m_gDrop13,m_gDrop14,m_gDrop15,m_grainworm;
	//fishing rode
	uint32 f_Drop1,f_Drop2,f_Drop3,f_Drop4,f_Drop5,f_Drop6,f_Drop7,f_Drop8,f_Drop9,f_Drop10,f_Drop11,f_Drop12;
	//fishing gold rode
	uint32 f_gDrop1,f_gDrop2,f_gDrop3,f_gDrop4,f_gDrop5,f_gDrop6,f_gDrop7,f_gDrop8,f_gDrop9,f_gDrop10,f_gDrop11,f_gDrop12;

	uint16	m_nTempleEventRemainSeconds;

	uint8	m_bMaxRegenePoint;

	bool	m_bPermanentChatMode;
	std::string	m_strPermanentChat;

	uint8	m_bSantaOrAngel;
	uint8	m_sRankResetHour;

	// National Points Settings
	int m_Loyalty_Ardream_Source;
	int m_Loyalty_Ardream_Target;
	int m_Loyalty_Ronark_Land_Base_Source;
	int m_Loyalty_Ronark_Land_Base_Target;
	int m_Loyalty_Ronark_Land_Source;
	int m_Loyalty_Ronark_Land_Target;
	int m_Loyalty_Other_Zone_Source;
	int m_Loyalty_Other_Zone_Target;
	int m_Loyalty_Mini_Pvp_Source;
	int m_Loyalty_Mini_Pvp_Target;

	// Bifrost
	uint8   m_nBifrostTime[BIFROST_EVENT_COUNT];

	uint8 m_BifrostVictory;
	uint8 m_sBifrostVictoryAll;
	uint16 m_sBifrostRemainingTime;
	uint16 m_sBifrostTime;
	bool m_sBifrostWarStart;
	uint8 m_sBifrostVictoryNoticeAll;
	uint16 m_xBifrostRemainingTime;
	uint16 m_xJoinOtherNationBifrostTime;
	uint16 m_xBifrostTime;
	uint16 m_xBifrostMonumentAttackTime;
	bool m_bAttackBifrostMonument;

	void SendEventRemainingTime(bool bSendAll = false, CUser *pUser = nullptr, uint8 ZoneID = 0);

	bool m_IsMagicTableInUpdateProcess;
	bool m_IsPlayerRankingUpdateProcess;
	bool m_IsItemOPUpdateProcess;
	bool m_IsDupeUpdateProcess;
	bool m_IlegalItemsUpdateProcess;
	bool m_SiegeUpdateProcess;
	
	uint16 LeechKig;
	uint16 BoneDragon;
	uint16 Minotaur;
	uint16 Apostle;
	uint16 DoomSoldier;
	uint16 TrollWarrior;

	uint16 e_LeechKig;
	uint16 e_BoneDragon;
	uint16 e_Minotaur;
	uint16 e_Apostle;
	uint16 e_DoomSoldier;
	uint16 e_TrollWarrior;
	uint16 JuraidAnnounce;

	// Forgetten Temple
	std::vector<uint16>        m_nForgettenTempleUsers;
	bool              m_bForgettenTempleIsActive;
	int8              m_nForgettenTempleStartHour;
	int8              m_nForgettenTempleLevelMin;
	int8              m_nForgettenTempleLevelMax;
	int32              m_nForgettenTempleStartTime;
	uint8              m_nForgettenTempleChallengeTime;
	bool              m_bForgettenTempleSummonMonsters;
	uint8              m_nForgettenTempleCurrentStage;
	uint8              m_nForgettenTempleLastStage;
	ForgettenTempleMonsterList    m_ForgettenTempleMonsterList;
	uint32              m_nForgettenTempleLastSummonTime;
	bool              m_nForgettenTempleBanishFlag;
	uint8              m_nForgettenTempleBanishTime;

	// Event Zones
	std::vector<uint16>        m_nEventZoneUsers;
	bool              m_bEventZoneIsActive;
	int8              m_nEventZoneStartHour;
	int8              m_nEventZoneLevelMin;
	int8              m_nEventZoneLevelMax;
	int32              m_nEventZoneStartTime;
	uint8              m_nEventZoneTime;
	bool              m_nEventZoneBanishFlag;
	uint8              m_nEventZoneBanishTime;

	// zone server info
	int					m_nServerNo, m_nServerGroupNo;
	int					m_nServerGroup;	// server의 번호(0:서버군이 없다, 1:서버1군, 2:서버2군)
	ServerArray			m_ServerArray;
	ServerArray			m_ServerGroupArray;

	NameMap		m_accountNameMap,
		m_characterNameMap;

	std::recursive_mutex	m_accountNameLock,
		m_characterNameLock,
		m_questNpcLock;

	// Controlled weather events set by Kings
	uint8 m_byKingWeatherEvent;
	uint8 m_byKingWeatherEvent_Day;
	uint8 m_byKingWeatherEvent_Hour;
	uint8 m_byKingWeatherEvent_Minute;

	// XP/coin/NP events
	uint8 m_byExpEventAmount, m_byCoinEventAmount, m_byNPEventAmount ;

	INLINE CLuaEngine * GetLuaEngine() { return &m_luaEngine; }

	KOSocketMgr<CUser> m_socketMgr;
	ClientSocketMgr<CAISocket> m_aiSocketMgr;

	FILE *m_fpTradeUser;
	FILE *m_fpDeathUser;
	FILE *m_fpDeathNpc;
	FILE *m_fpChat;
	FILE *m_fpShop;
	FILE *m_fpGM;
	FILE *m_upgradelog;
	FILE *m_fpCheat;
	
	void WriteTradeUserLogFile(std::string & logMessage);
	void WriteDeathUserLogFile(std::string & logMessage);
	void WriteDeathNpcLogFile(std::string & logMessage);
	void WriteChatLogFile(std::string & logMessage);
	void WriteShopLogFile(std::string & logMessage);
	void WriteGMLogFile(std::string & logMessage);
	void WriteUpgradeLogFile(std::string & logMessage);
	void WriteCheatLogFile(std::string & logMessage);

private:
	CLuaEngine	m_luaEngine;

	std::string m_strGameDSN, m_strAccountDSN;
	std::string m_strGameUID, m_strAccountUID;
	std::string m_strGamePWD, m_strAccountPWD;
	bool m_bMarsEnabled;

	bool ProcessServerCommand(std::string & command);

public:
	void InitServerCommands();
	void CleanupServerCommands();

	static ServerCommandTable s_commandTable;

	COMMAND_HANDLER(HandleNoticeCommand);
	COMMAND_HANDLER(HandleBdwOpenCommand);
	COMMAND_HANDLER(HandleNoticeallCommand);
	COMMAND_HANDLER(HandleKillUserCommand);
	COMMAND_HANDLER(HandleWar1OpenCommand);
	COMMAND_HANDLER(HandleWar2OpenCommand);
	COMMAND_HANDLER(HandleWar3OpenCommand);
	COMMAND_HANDLER(HandleWar4OpenCommand);
	COMMAND_HANDLER(HandleWar5OpenCommand);
	COMMAND_HANDLER(HandleWar6OpenCommand);
	COMMAND_HANDLER(HandleSnowWarOpenCommand);
	COMMAND_HANDLER(HandleSiegeWarOpenCommand);
	COMMAND_HANDLER(HandleWarCloseCommand);
	COMMAND_HANDLER(HandleDiscountCommand);
	COMMAND_HANDLER(HandleGlobalDiscountCommand);
	COMMAND_HANDLER(HandleDiscountOffCommand);
	COMMAND_HANDLER(HandleCaptainCommand);
	COMMAND_HANDLER(HandleSantaCommand);
	COMMAND_HANDLER(HandleSantaOffCommand);
	COMMAND_HANDLER(HandleAngelCommand);
	COMMAND_HANDLER(HandlePermanentChatCommand);
	COMMAND_HANDLER(HandlePermanentChatOffCommand);
	COMMAND_HANDLER(HandleReloadNoticeCommand);
	COMMAND_HANDLER(HandleReloadTablesCommand);
	COMMAND_HANDLER(HandleReloadMagicsCommand);
	COMMAND_HANDLER(HandleReloadItemOPCommand);
	COMMAND_HANDLER(HandleReloadDupeCommand);
	COMMAND_HANDLER(HandleReloadIlegalItemsCommand);
	COMMAND_HANDLER(HandleReloadSiegeCommand);
	COMMAND_HANDLER(HandleReloadQuestCommand);
	COMMAND_HANDLER(HandleReloadRanksCommand);
	COMMAND_HANDLER(HandleNPAddCommand);
	COMMAND_HANDLER(HandleExpAddCommand);
	COMMAND_HANDLER(HandleGiveItemCommand);
	COMMAND_HANDLER(HandleMoneyAddCommand);
	COMMAND_HANDLER(HandleTeleportAllCommand);
	COMMAND_HANDLER(HandleCountCommand);
	COMMAND_HANDLER(HandlePermitConnectCommand);
	COMMAND_HANDLER(HandleWarResultCommand);
	COMMAND_HANDLER(HandleMonSummonCommand);
	COMMAND_HANDLER(HandleSnowWarCloseCommand);
	COMMAND_HANDLER(HandleGiveAchieveCommand);
	COMMAND_HANDLER(HandleResetAchieveCommand);
};

extern CGameServerDlg * g_pMain;
#endif