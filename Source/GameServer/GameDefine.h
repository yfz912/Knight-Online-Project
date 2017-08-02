#pragma once

// Classes
#define KARUWARRIOR		101  // Beginner Karus Warrior
#define KARUROGUE		102  // Beginner Karus Rogue
#define KARUWIZARD		103  // Beginner Karus Magician
#define KARUPRIEST		104  // Beginner Karus Priest
#define BERSERKER		105  // Skilled (after first job change) Karus Warrior
#define GUARDIAN		106  // Mastered Karus Warrior
#define HUNTER			107  // Skilled (after first job change) Karus Rogue
#define PENETRATOR		108  // Mastered Karus Rogue
#define SORSERER		109  // Skilled (after first job change) Karus Magician
#define NECROMANCER		110  // Mastered Karus Magician
#define SHAMAN			111  // Skilled (after first job change) Karus Priest
#define DARKPRIEST		112  // Mastered Karus Priest
#define KARUKURIAN		113 // Beginner Karus Kurian
#define KURIANN			114 // Skilled (after first job change) Karus Kurian
#define KURIANM			115 // Mastered Karus Kurian

#define ELMORWARRRIOR	201  // Beginner El Morad Warrior
#define ELMOROGUE		202  // Beginner El Morad Rogue
#define ELMOWIZARD		203  // Beginner El Morad Magician
#define ELMOPRIEST      204  // Beginner El Morad Priest
#define BLADE			205  // Skilled (after first job change) El Morad Warrior
#define PROTECTOR		206  // Mastered El Morad Warrior
#define RANGER			207  // Skilled (after first job change) El Morad Rogue
#define ASSASSIN		208  // Mastered El Morad Rogue
#define MAGE			209  // Skilled (after first job change) El Morad Magician
#define ENCHANTER		210  // Mastered El Morad Magician
#define CLERIC			211  // Skilled (after first job change) El Morad Priest
#define DRUID			212  // Mastered El Morad Priest
#define ELMOPORTU		213     // Beginner El Morad Portu
#define PORTUN			214     // Skilled (after first job change) El Morad Portu
#define PORTUM			215     // Mastered El Morad Portu


// Races
#define KARUS_BIG		1  // Arch Tuarek (Karus Warriors - only!)
#define KARUS_MIDDLE    2  // Tuarek (Karus Rogues & Priests)
#define KARUS_SMALL		3  // Wrinkle Tuarek (Karus Magicians)
#define KARUS_WOMAN		4  // Puri Tuarek (Karus Priests)
#define KARUS_KURIAN	6   // Kurian (Karus Warriors - only!)
#define BABARIAN		11  // Barbarian (El Morad Warriors - only!)
#define ELMORAD_MAN		12  // El Morad Male (El Morad - ALL CLASSES)
#define ELMORAD_WOMAN	13  // El Morad Female (El Morad - ALL CLASSES)
#define ELMORAD_PORTU	14  // Portu (El Morad Warriors - only!)

// Ÿ�ݺ� ����� //
#define GREAT_SUCCESS			0X01		// �뼺��
#define SUCCESS					0X02		// ����
#define NORMAL					0X03		// ����
#define	FAIL					0X04		// ���� 

/*SucessRate by Obede
#define MAX_RESSIT 255
#define BUFF_TYPE_SLOW 40
#define BUFF_TYPE_STUNN 47*/

enum UserInfoOpCode
{
	UserInfo = 1, 
	UserInfoNick = 2,
	Location = 3,
	UserInfoShow = 4
};

enum ExpSealOpcode
{
     On = 1,
	 Off  = 2
};

enum AchieveOpCode
{
	AchieveError			= 0,
	AchieveSuccess			= 1,
	AchieveGetItem			= 2,
	AchieveInfo				= 3,
	AchieveSumary			= 4,
	AchieveChallengeDone	= 5,
	AchieveChallengeStart	= 6,
	AchieveChallengeCancel	= 7,
	AchieveChallengeCount	= 9,
	AchieveCover			= 16,
	AchieveSkill			= 17,
	AchieveCoverReset		= 18,
	AchieveSkillReset		= 19
};

enum NationTransferOpCode
{
	NationWarStatus			= 1,
	NationOpenBox			= 2,
	NationSuccessTransfer	= 3
};

enum GenderChangeOpCode
{
	GenderFail			= 0,
	GenderSuccess		= 1,
	GenderNoItem		= 2
};

enum UserInfoType
{
	UserInfonew			= 0x01, // Userinfo 1
	Userinfonew2		= 0x02, // Userinfo2
	StatusChat			= 0x03, // Status of Chat type
	RemoveChat			= 0x04, // Remove Region Chat
	Unknow5				= 0x05
};

enum ItemMovementType
{
	ITEM_INVEN_SLOT			= 1,
	ITEM_SLOT_INVEN			= 2,
	ITEM_INVEN_INVEN		= 3,
	ITEM_SLOT_SLOT			= 4,
	ITEM_INVEN_ZONE			= 5,
	ITEM_ZONE_INVEN			= 6,
	ITEM_INVEN_TO_COSP		= 7,  // Inventory -> Cospre bag
	ITEM_COSP_TO_INVEN		= 8,  // Cospre bag -> Inventory
	ITEM_INVEN_TO_MBAG		= 9,  // Inventory -> Magic bag
	ITEM_MBAG_TO_INVEN		= 10, // Magic bag -> Inventory
	ITEM_MBAG_TO_MBAG		= 11  // Magic bag -> Magic bag
};

enum ItemSlotType
{
	ItemSlot1HEitherHand		= 0,
	ItemSlot1HRightHand			= 1,
	ItemSlot1HLeftHand			= 2,
	ItemSlot2HRightHand			= 3,
	ItemSlot2HLeftHand			= 4,
	ItemSlotPauldron			= 5,
	ItemSlotPads				= 6,
	ItemSlotHelmet				= 7,
	ItemSlotGloves				= 8,
	ItemSlotBoots				= 9,
	ItemSlotEarring				= 10,
	ItemSlotNecklace			= 11,
	ItemSlotRing				= 12,
	ItemSlotShoulder			= 13,
	ItemSlotBelt				= 14,
	ItemSlotPet					= 20,
	ItemSlotBag					= 25,
	ItemSlotCospreGloves		= 100,
	ItemSlotCosprePauldron		= 105,
	ItemSlotCospreHelmet		= 107,
	ItemSlotCospreWings			= 110,
	ItemSlotCospreFairy			= 111
};

// Item Weapon Type Define
#define WEAPON_DAGGER			1
#define WEAPON_SWORD			2
#define WEAPON_2H_SWORD			22 // Kind field as-is
#define WEAPON_AXE				3
#define WEAPON_2H_AXE			32 // Kind field as-is
#define WEAPON_MACE				4
#define WEAPON_2H_MACE			42 // Kind field as-is
#define WEAPON_SPEAR			5
#define WEAPON_2H_SPEAR			52 // Kind field as-is
#define WEAPON_SHIELD			6
#define WEAPON_BOW				7
#define WEAPON_LONGBOW			8
#define WEAPON_LAUNCHER			10
#define WEAPON_STAFF			11
#define WEAPON_ARROW			12	// ��ų ���
#define WEAPON_JAVELIN			13	// ��ų ���
#define WEAPON_JAMADAR			14	// Jamadar 20xx
#define WEAPON_MACE2			18
#define WEAPON_WORRIOR_AC		21	// ��ų ���
#define WEAPON_LOG_AC			22	// ��ų ���
#define WEAPON_WIZARD_AC		23	// ��ų ���
#define WEAPON_PRIEST_AC		24	// ��ų ���
#define WEAPON_PICKAXE			61	// Unlike the others, this is just the Kind field as-is (not / 10).
#define WEAPON_FISHING			63	// Unlike the others, this is just the Kind field as-is (not / 10).

#define ACCESSORY_EARRING    91
#define ACCESSORY_NECKLACE    92
#define ACCESSORY_RING      93
#define ACCESSORY_BELT      94

#define ITEM_KIND_COSPRE		252

////////////////////////////////////////////////////////////
// User Status //
#define USER_STANDING			0X01		// �� �ִ�.
#define USER_SITDOWN			0X02		// �ɾ� �ִ�.
#define USER_DEAD				0x03		// ��Ŷ�
#define USER_BLINKING			0x04		// ��� ��Ƴ���!!!

////////////////////////////////////////////////////////////
// Durability Type
#define ATTACK				0x01
#define DEFENCE				0x02
#define REPAIR_ALL			0x03
#define ACID_ALL			0x04
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Knights Authority Type
/*
#define CHIEF				0x06
#define VICECHIEF			0x05*/
#define OFFICER				0x04
#define KNIGHT				0x03
//#define TRAINEE				0x02
#define PUNISH				0x01	

#define CHIEF				0x01	// ����
#define VICECHIEF			0x02	// �δ���
#define TRAINEE				0x05	// ���
#define COMMAND_CAPTAIN		100		// ���ֱ���
////////////////////////////////////////////////////////////

#define CLAN_COIN_REQUIREMENT	500000
#define CLAN_LEVEL_REQUIREMENT	20

#define ITEM_GOLD			900000000	// �� ������ ��ȣ...
#define ITEM_NO_TRADE		900000001	// Cannot be traded, sold or stored.

////////////////////////////////////////////////////////////
// EVENT MISCELLANOUS DATA DEFINE
#define ZONE_TRAP_INTERVAL	   2		// Interval is one second (in seconds) right now.
#define ZONE_TRAP_DAMAGE	   500		// HP Damage is 10 for now :)

////////////////////////////////////////////////////////////

#define RIVALRY_DURATION		(300)	// 5 minutes
#define RIVALRY_NP_BONUS		(150)	// 150 additional NP on kill
#define MINIRIVALRY_NP_BONUS	(50)	// 150 additional NP on kill

#define MAX_ANGER_GAUGE			(5)		// Maximum of 5 deaths in a PVP zone to fill your gauge.

#define PVP_MONUMENT_NP_BONUS	(5)	// 5 additional NP on kill
#define EVENT_MONUMENT_NP_BONUS	(10)	// 10 additional NP on kill

////////////////////////////////////////////////////////////
// SKILL POINT DEFINE
#define ORDER_SKILL			0x01
#define MANNER_SKILL		0X02
#define LANGUAGE_SKILL		0x03
#define BATTLE_SKILL		0x04
#define PRO_SKILL1			0x05
#define PRO_SKILL2			0x06
#define PRO_SKILL3			0x07
#define PRO_SKILL4			0x08

enum SkillPointCategory
{
	SkillPointFree		= 0,
	SkillPointCat1		= 5,
	SkillPointCat2		= 6,
	SkillPointCat3		= 7,
	SkillPointMaster	= 8
};

/////////////////////////////////////////////////////////////
// ITEM TYPE DEFINE
#define ITEM_TYPE_FIRE				0x01
#define ITEM_TYPE_COLD				0x02
#define ITEM_TYPE_LIGHTNING			0x03
#define ITEM_TYPE_POISON			0x04
#define ITEM_TYPE_HP_DRAIN			0x05
#define ITEM_TYPE_MP_DAMAGE			0x06
#define ITEM_TYPE_MP_DRAIN			0x07
#define ITEM_TYPE_MIRROR_DAMAGE		0x08

/////////////////////////////////////////////////////////////
// JOB GROUP TYPES
#define GROUP_WARRIOR				1
#define GROUP_ROGUE					2
#define GROUP_MAGE					3
#define GROUP_CLERIC				4
#define GROUP_ATTACK_WARRIOR		5
#define GROUP_DEFENSE_WARRIOR		6
#define GROUP_ARCHERER				7
#define GROUP_ASSASSIN				8
#define GROUP_ATTACK_MAGE			9
#define GROUP_PET_MAGE				10
#define GROUP_HEAL_CLERIC			11
#define GROUP_CURSE_CLERIC			12
#define GROUP_KURIAN_PORTU			13
#define GROUP_KURIAN_PORTU_WARRIOR	14
#define GROUP_KURIAN_PORTU_MASTER	15

//////////////////////////////////////////////////////////////
// USER ABNORMAL STATUS TYPES
enum AbnormalType
{
	ABNORMAL_INVISIBLE		= 0,	// Hides character completely (for GM visibility only).
	ABNORMAL_NORMAL			= 1,	// Shows character. This is the default for players.
	ABNORMAL_GIANT			= 2,	// Enlarges character.
	ABNORMAL_DWARF			= 3,	// Shrinks character.
	ABNORMAL_BLINKING		= 4,	// Forces character to start blinking.
	ABNORMAL_GIANT_TARGET	= 6		// Enlarges character and shows "Hit!" effect.
};

//////////////////////////////////////////////////////////////
// Object Type
#define NORMAL_OBJECT		0
#define SPECIAL_OBJECT		1

//////////////////////////////////////////////////////////////
// REGENE TYPES
#define REGENE_NORMAL		0
#define REGENE_MAGIC		1
#define REGENE_ZONECHANGE	2

struct _SPECIAL_ITEM
{
 uint32   SealSerial;
 std::string  sCharID;
 uint64   iSerial;
 uint8   bRaceSatis;
 uint16   sClass;
 uint8   bLevel;
 uint16   sExpPercent;

 // for Char Seal      ---JOKER97
 uint8   Stat_STR;
 uint8   Stat_STA;
 uint8   Stat_DEX;
 uint8   Stat_INT;
 uint8   Stat_CHA;
 uint32   sGold;
 uint8   Skill_Points[5];
 uint32   Item_Num[INVENTORY_COSP];
 uint16   Item_Duration[INVENTORY_COSP];
 uint16   Item_Count[INVENTORY_COSP];
 uint8   Item_Flag[INVENTORY_COSP];
};

struct _ACHIEVE_COM
{
	uint16	cAchieveID;
	uint8	cType;
	uint32	cQuest1;
	uint32	cQuest2;
};

struct _ACHIEVE_MAIN
{
	uint16	mMainID;
	uint8	mKind;
	uint16	mAchieveID;
	uint16	mPoints;
	uint32	mItemID;
	uint32	mItemCount;
	uint8	mZoneNum;
	uint8	mKilledType;
	uint8	mType;
	uint16	mTime;
	uint8	mSize;		// type of mainID, if is quest type or Killcount Type
	uint8	Category;
};

#define ACHIEVE_MOB_GROUPS		2
#define ACHIEVE_MOBS_PER_GROUP	4
struct _ACHIEVE_MON
{
	uint16	oMainID;
	uint8	oType;		// 1 = have Monster in Group1 || 0 = not have
	uint8	oType2;		// 1 = have Monster in Group2 || 0 = not have
	uint16	oSsid[ACHIEVE_MOB_GROUPS][ACHIEVE_MOBS_PER_GROUP]; 
	uint16	oCount[ACHIEVE_MOB_GROUPS];

	_ACHIEVE_MON()
	{
		memset(&oSsid, 0, sizeof(oSsid));
		memset(&oCount, 0, sizeof(oCount));
	}
};

struct _ACHIEVE_NORMAL
{
	uint16	nAchieveID;
	uint8	nType;
	uint32	nTypeCount;
};

struct _ACHIEVE_TITLE
{
	uint16	cAchieveID;
	uint16	cMainID;
	uint8	cStrB;
	uint8	cStaB;
	uint8	cDexB;
	uint8	cIntB;
	uint8	cChaB;
	uint16	cAttack;
	uint16	cAC;
	uint8	cNPContribu;
	uint8	cExpPct;
	uint16	cSSwordAC;
	uint16	cJamadarAC;
	uint16	cSwordAC;
	uint16	cBlowAC;
	uint16	cAxeAC;
	uint16	cSpearAC;
	uint16	cArrowAC;
	uint16	cFlameB;
	uint16	cIceB;
	uint16	cLightB;
	uint16	cFireR;
	uint16	cIceR;
	uint16	cLightR;
	uint16	cMagicR;
	uint16	cCurseR;
	uint16	cPoisonR;
};

struct _ACHIEVE_WAR
{
	uint16	wMainID;
	uint8	wType;
	uint8	Unknow;
	uint32	wKillCount;
	uint8	Unknow2;
};

struct _CLASS_COEFFICIENT
{
	uint16	sClassNum;
	float	ShortSword;
	float	Sword;
	float	Axe;
	float	Club;
	float	Spear;
	float	Pole;
	float	Staff;
	float	Bow;
	float	HP;
	float	MP;
	float	SP;
	float	AC;
	float	Hitrate;
	float	Evasionrate;
};

// Dropped loot/chest.
#define LOOT_ITEMS	6
struct _LOOT_ITEM
{
	uint32 nItemID;
	uint16 sCount;

	_LOOT_ITEM(uint32 nItemID, uint16 sCount)
	{
		this->nItemID = nItemID;
		this->sCount = sCount;
	}
};

struct _LOOT_BUNDLE
{
	uint32 nBundleID;
	std::vector<_LOOT_ITEM> Items;
	float x, z, y;
	time_t tDropTime;
};

struct _ITEM_EXPIRATION
{
	uint32 nItemID;
	uint8  nExpirationDay;
};

struct	_EXCHANGE_ITEM
{
	uint32	nItemID;
	uint32	nCount;
	uint16	sDurability;
	uint8	bSrcPos;
	uint8	bDstPos;
	uint64	nSerialNum;
};

enum ItemRace
{
	RACE_TRADEABLE_IN_48HR	= 19, // These items can't be traded until 48 hours from the time of creation
	RACE_UNTRADEABLE		= 20  // Cannot be traded or sold.
};

enum SellType
{
	SellTypeNormal		= 0, // sell price is 1/4 of the purchase price
	SellTypeFullPrice	= 1, // sell price is the same as the purchase price
	SellTypeNoRepairs	= 2  // sell price is 1/4 of the purchase price, item cannot be repaired.
};

struct _ITEM_TABLE
{
	uint32	m_iNum;
	std::string	m_sName;
	uint8	m_bKind;
	uint8	m_bSlot;
	uint8	m_bRace;
	uint8	m_bClass;
	uint16	m_sDamage;
	uint16	m_sDelay;
	uint16	m_sRange;
	uint16	m_sWeight;
	uint16	m_sDuration;
	uint32	m_iBuyPrice;
	uint32	m_iSellPrice;
	int16	m_sAc;
	uint8	m_bCountable;
	uint32	m_iEffect1;
	uint32	m_iEffect2;
	uint8	m_bReqLevel;
	uint8	m_bReqLevelMax;
	uint8	m_bReqRank;
	uint8	m_bReqTitle;
	uint8	m_bReqStr;
	uint8	m_bReqSta;
	uint8	m_bReqDex;
	uint8	m_bReqIntel;
	uint8	m_bReqCha;
	uint8	m_bSellingGroup;
	uint8	m_ItemType;
	uint16	m_sHitrate;
	uint16	m_sEvarate;
	uint16	m_sDaggerAc;
	uint16	m_sJamadarAc;
	uint16	m_sSwordAc;
	uint16	m_sMaceAc;
	uint16	m_sAxeAc;
	uint16	m_sSpearAc;
	uint16	m_sBowAc;
	uint8	m_bFireDamage;
	uint8	m_bIceDamage;
	uint8	m_bLightningDamage;
	uint8	m_bPoisonDamage;
	uint8	m_bHPDrain;
	uint8	m_bMPDamage;
	uint8	m_bMPDrain;
	uint8	m_bMirrorDamage;
	int16	m_sStrB;
	int16	m_sStaB;
	int16	m_sDexB;
	int16	m_sIntelB;
	int16	m_sChaB;
	int16	m_MaxHpB;
	int16	m_MaxMpB;
	int16	m_bFireR;
	int16	m_bColdR;
	int16	m_bLightningR;
	int16	m_bMagicR;
	int16	m_bPoisonR;
	int16	m_bCurseR;
	int16	ItemClass;
	int16	ItemExt;
	uint8	UpgradeNotice;
	uint32	m_iNPBuyPrice;
	uint8	m_Bound;

	INLINE bool isStackable() { return m_bCountable != 0; }

	INLINE uint8 GetKind() { return m_bKind; }
	INLINE uint8 Gettype() { return m_ItemType; }
	INLINE uint32 Getnum() { return m_iNum; }
	INLINE uint8 GetItemGroup() { return uint8(m_bKind / 10); }

	INLINE bool isDagger() { return GetItemGroup() == WEAPON_DAGGER; }
	INLINE bool isJamadar() { return GetItemGroup() == WEAPON_JAMADAR; }
	INLINE bool isSword() { return GetItemGroup() == WEAPON_SWORD; }
	INLINE bool is2HSword() { return GetKind() == WEAPON_2H_SWORD; }
	INLINE bool isAxe() { return GetItemGroup() == WEAPON_AXE; }
	INLINE bool is2HAxe() { return GetKind() == WEAPON_2H_AXE; }
	INLINE bool isMace() { return GetItemGroup() == WEAPON_MACE || GetItemGroup() == WEAPON_MACE2; }
	INLINE bool is2HMace() { return GetKind() == WEAPON_2H_MACE || GetItemGroup() == WEAPON_MACE2; }
	INLINE bool isSpear() { return GetItemGroup() == WEAPON_SPEAR; }
	INLINE bool is2HSpear() { return GetKind() == WEAPON_2H_SPEAR; }
	INLINE bool isShield() { return GetItemGroup() == WEAPON_SHIELD; }
	INLINE bool isStaff() { return GetItemGroup() == WEAPON_STAFF; }
	INLINE bool isBow() { return GetItemGroup() == WEAPON_BOW || GetItemGroup() == WEAPON_LONGBOW; }
	INLINE bool isPickaxe() { return GetKind() == WEAPON_PICKAXE; }
	INLINE bool isFishing() { return GetKind() == WEAPON_FISHING; }
	INLINE bool isRON() { return Getnum() == 189401287 || Getnum() == 189401288 || Getnum() == 189401289; }
	INLINE bool isLigh() { return Getnum() == 189301277 || Getnum() == 189301278 || Getnum() == 189301279; }
	INLINE bool isNormal() { return Gettype() == 4 || Gettype() == 5; }
	INLINE bool isRebirth1() { return Gettype() == 11 || Gettype() == 12; }
	INLINE bool isAll() { return GetKind() > 0; }
	INLINE bool is2Handed() { return m_bSlot == ItemSlot2HLeftHand || m_bSlot == ItemSlot2HRightHand; }
	INLINE bool isAccessory() { return GetKind() == ACCESSORY_EARRING || GetKind() == ACCESSORY_NECKLACE || GetKind() == ACCESSORY_RING || GetKind() == ACCESSORY_BELT; }
	INLINE bool isEarring() { return GetKind() == ACCESSORY_EARRING; }
	INLINE bool isNecklace() { return GetKind() == ACCESSORY_NECKLACE; }
	INLINE bool isRing() { return GetKind() == ACCESSORY_RING; }
	INLINE bool isBelt() { return GetKind() == ACCESSORY_BELT; }
};

struct _ZONE_SERVERINFO
{
	short		sServerNo;
	std::string	strServerIP;
};

struct _KNIGHTS_CAPE
{
	uint16	sCapeIndex;
	uint32	nReqCoins;
	uint32	nReqClanPoints;	// clan point requirement
	uint8	byGrade;		// clan grade requirement
	uint8	byRanking;		// clan rank requirement (e.g. royal, accredited, etc)
};

struct _KNIGHTS_SIEGE_WARFARE
{
	uint16	sCastleIndex;
	uint16	sMasterKnights;
	uint8	bySiegeType;
	uint8	byWarDay;
	uint8	byWarTime;
	uint8	byWarMinute;
	uint16	sChallengeList_1;
	uint16	sChallengeList_2;
	uint16	sChallengeList_3;
	uint16	sChallengeList_4;
	uint16	sChallengeList_5;
	uint16	sChallengeList_6;
	uint16	sChallengeList_7;
	uint16	sChallengeList_8;
	uint16	sChallengeList_9;
	uint16	sChallengeList_10;
	uint8	byWarRequestDay;
	uint8	byWarRequestTime;
	uint8	byWarRequestMinute;
	uint8	byGuerrillaWarDay;
	uint8	byGuerrillaWarTime;
	uint8	byGuerrillaWarMinute;
	std::string	strChallengeList;
	uint16	sMoradonTariff;
	uint16	sDellosTariff;
	int32	nDungeonCharge;
	int32	nMoradonTax;
	int32	nDellosTax;
	uint16	sRequestList_1;
	uint16	sRequestList_2;
	uint16	sRequestList_3;
	uint16	sRequestList_4;
	uint16	sRequestList_5;
	uint16	sRequestList_6;
	uint16	sRequestList_7;
	uint16	sRequestList_8;
	uint16	sRequestList_9;
	uint16	sRequestList_10;
};

struct _KNIGHTS_ALLIANCE
{
	uint16	sMainAllianceKnights;
	uint16	sSubAllianceKnights;
	uint16	sMercenaryClan_1;
	uint16	sMercenaryClan_2;
};

struct _START_POSITION
{
	uint16	ZoneID;
	uint16	sKarusX;
	uint16	sKarusZ;
	uint16	sElmoradX;
	uint16	sElmoradZ;
	uint16	sKarusGateX;
	uint16	sKarusGateZ;
	uint16	sElmoradGateX;
	uint16	sElmoradGateZ;
	uint8	bRangeX;
	uint8	bRangeZ;
};

struct _KNIGHTS_RATING
{
	uint32 nSlot;
	uint32 nRank;
	uint16 sClanID;
	uint32 nPoints;
};

struct _USER_RANK
{
	uint16	nRank;  // shIndex for USER_KNIGHTS_RANK
	std::string strUserID[2];
	uint32	nSalary; // nMoney for USER_KNIGHTS_RANK
	uint32	nLoyalty[2]; // nKarusLoyaltyMonthly/nElmoLoyaltyMonthly for USER_PERSONAL_RANK
};

// TO-DO: Rewrite this system to be less script dependent for exchange logic.
// Coin requirements should be in the database, and exchanges should be grouped.
#define ITEMS_IN_ORIGIN_GROUP 5
#define ITEMS_IN_EXCHANGE_GROUP 5

struct _ITEM_EXCHANGE
{
	uint32	nIndex;
	uint8	bRandomFlag;

	uint32	nOriginItemNum[ITEMS_IN_ORIGIN_GROUP];
	uint16	sOriginItemCount[ITEMS_IN_ORIGIN_GROUP];

	uint32	nExchangeItemNum[ITEMS_IN_EXCHANGE_GROUP];
	uint16	sExchangeItemCount[ITEMS_IN_EXCHANGE_GROUP];

	uint32	Unk2;
	uint32	Unk3;
	uint32	Unk4;
	uint32	Unk5;
};

#define MAX_ITEMS_REQ_FOR_UPGRADE 8
struct _ITEM_UPGRADE
{
	uint32	nIndex;
	uint16	sNpcNum;
	int8	bOriginType;
	uint16	sOriginItem;
	uint32	nReqItem[MAX_ITEMS_REQ_FOR_UPGRADE];
	uint32	nReqNoah;
	uint8	bRateType;
	uint16	sGenRate;
	int32	nGiveItem;

	INLINE uint32 Getscroll() { return nReqItem[MAX_ITEMS_REQ_FOR_UPGRADE]; }
	INLINE bool isReverse() { return Getscroll() == 379257000; }
	INLINE bool isTransform() { return Getscroll() == 379256000; }
};

enum ItemTriggerType
{
	TriggerTypeAttack = 3,
	TriggerTypeDefend = 13
};

struct _ITEM_OP
{
	uint32	nItemID;
	uint8	bTriggerType;
	uint32	nSkillID;
	uint8	bTriggerRate;
};

struct _ITEM_DUPER
{
	uint32	     n_Index;
	uint32		 d_ItemID;
	uint64		 d_Serial;
};

struct _ILEGAL_ITEMS
{
	uint32		i_Index;
	uint32		i_ItemID;
};

struct _SET_ITEM
{
	uint32 SetIndex;

	uint16 HPBonus;
	uint16 MPBonus;
	uint16 StrengthBonus;
	uint16 StaminaBonus;
	uint16 DexterityBonus;
	uint16 IntelBonus;
	uint16 CharismaBonus;
	uint16 FlameResistance;
	uint16 GlacierResistance;
	uint16 LightningResistance;
	uint16 PoisonResistance;
	uint16 MagicResistance;
	uint16 CurseResistance;

	uint16 XPBonusPercent;
	uint16 CoinBonusPercent;

	uint16 APBonusPercent;		// +AP% for all classes
	uint16 APBonusClassType;	// defines a specific class for +APBonusClassPercent% to be used against
	uint16 APBonusClassPercent;	// +AP% for APBonusClassType only

	uint16 ACBonus;				// +AC amount for all classes
	uint16 ACBonusClassType;	// defines a specific class for +ACBonusClassPercent% to be used against
	uint16 ACBonusClassPercent;	// +AC% for ACBonusClassType only

	uint16 MaxWeightBonus;
	uint8 NPBonus;
};

struct _QUEST_HELPER
{
	uint32	nIndex;
	uint8	bMessageType;
	uint8	bLevel;
	uint32	nExp;
	uint8	bClass;
	uint8	bNation;
	uint8	bQuestType;
	uint8	bZone;
	uint16	sNpcId;
	uint16	sEventDataIndex;
	int8	bEventStatus;
	uint32	nEventTriggerIndex;
	uint32	nEventCompleteIndex;
	uint32	nExchangeIndex;
	uint32	nEventTalkIndex;
	std::string strLuaFilename;
};

struct _USER_SEAL_ITEM
{
	uint64 nSerialNum;
	uint32 nItemID;
	uint8 bSealType;
};

#define QUEST_MOB_GROUPS		4
#define QUEST_MOBS_PER_GROUP	4
struct _QUEST_MONSTER
{
	uint16	sQuestNum;
	uint16	sNum[QUEST_MOB_GROUPS][QUEST_MOBS_PER_GROUP]; 
	uint16	sCount[QUEST_MOB_GROUPS];

	_QUEST_MONSTER()
	{
		memset(&sCount, 0, sizeof(sCount));
		memset(&sNum, 0, sizeof(sNum));
	}
};

enum SpecialQuestIDs
{
	QUEST_KILL_GROUP1	= 32001,
	QUEST_KILL_GROUP2	= 32002,
	QUEST_KILL_GROUP3	= 32003,
	QUEST_KILL_GROUP4	= 32004,
};

struct _RENTAL_ITEM
{
	uint32	nRentalIndex;
	uint32	nItemID;
	uint16	sDurability;
	uint64	nSerialNum;
	uint8	byRegType;
	uint8	byItemType;
	uint8	byClass;
	uint16	sRentalTime;
	uint32	nRentalMoney;
	std::string strLenderCharID;
	std::string strBorrowerCharID;
};

struct _PREMIUM_ITEM
{
	uint8	Type;
	uint16	ExpRestorePercent;
	uint16	NoahPercent;
	uint16	DropPercent;
	uint32	BonusLoyalty;
	uint16	RepairDiscountPercent;
	uint16	ItemSellPercent;
};

struct _PREMIUM_ITEM_EXP
{
	uint16	nIndex;
	uint8	Type;
	uint8	MinLevel;
	uint8	MaxLevel;
	uint16	sPercent;
};

struct _USER_RANKING 
{
	uint16 m_socketID;
	int16 m_bEventRoom;
	uint16 m_bZone;
	uint8 m_bNation;
	uint32 m_iLoyaltyDaily;
	uint16 m_iLoyaltyPremiumBonus;
	uint16 m_KillCount; // Chaos Dungeon
	uint16 m_DeathCount; // Chaos Dungeon
};


struct _TEMPLE_EVENT_USER
{
	uint16 m_socketID;
	uint16 m_bEventRoom;
};

struct _EVENT_TRIGGER
{
	uint32 nIndex;
	uint16 bNpcType;
	uint32 sNpcID;
	uint32 nTriggerNum;
};

struct _USER_DAILY_OP
{
	std::string strUserId;
	int32 ChaosMapTime;
	int32 UserRankRewardTime;
	int32 PersonalRankRewardTime;
	int32 KingWingTime;
	int32 WarderKillerTime1;
	int32 WarderKillerTime2;
	int32 KeeperKillerTime;
	int32 UserLoyaltyWingRewardTime;
};

struct _MONUMENT_INFORMATION
{
	uint16 sSid;
	uint16 sNid;
	int32 RepawnedTime;
};

struct _MONSTER_CHALLENGE
{
	uint16 sIndex;
	uint8 bStartTime1;
	uint8 bStartTime2;
	uint8 bStartTime3;
	uint8 bLevelMin;
	uint8 bLevelMax;
};


typedef std::map<uint16,std::string>		RoomUserList;
struct _CHAT_ROOM
{
	int nIndex;
	std::string  strRoomName;
	std::string  strAdministrator;
	std::string  strPassword;

	bool isPassword(){return STRCASECMP(strPassword.c_str(), "") != 0; };
	uint8 isAdministrator(std::string strUserID){ return STRCASECMP(strAdministrator.c_str(), strUserID.c_str()) != 0 ? 1 : 2; };
 
	RoomUserList m_UserList;
	uint16 m_sMaxUser;
	uint16 m_sCurrentUser;
	uint8 m_bRoomNation;
 
	bool AddUser(std::string strUserID)
	{
		m_UserList.insert(std::make_pair(++m_sCurrentUser,strUserID)); 
		return true;
	}
};

struct _EVENT_TIMES
{
	uint16 sIndex;
	uint8 bTime1;
	uint8 bTime2;
	uint8 bTime3;
	uint8 bLvMin;
	uint8 bLvMax;
	uint8 AllDays;
};

struct _MONSTER_CHALLENGE_SUMMON_LIST
{
	uint16 sIndex;
	uint8 bLevel;
	uint8 bStage;
	uint8 bStageLevel;
	uint16 sTime;
	uint16 sSid;
	uint16 sCount;
	uint16 sPosX;
	uint16 sPosZ;
	uint8 bRange;
};

struct _EVENT_STATUS
{
	int16 ActiveEvent;
	int8 ZoneID;
	uint8 LastEventRoom;
	uint32 StartTime;
	uint16 AllUserCount;
	uint16 ElMoradUserCount;
	uint16 KarusUserCount;
	uint16 ElmoDeathCount[MAX_TEMPLE_EVENT_ROOM];
	uint16 KarusDeathCount[MAX_TEMPLE_EVENT_ROOM];
	uint16 m_sBdwMiniTimer[MAX_TEMPLE_EVENT_ROOM];
	uint8 m_sMiniTimerNation[MAX_TEMPLE_EVENT_ROOM];
	bool isAttackable;
	bool isActive;
	bool isDevaFlag;
	bool isDevaControl;
};
struct _START_POSITION_RANDOM
{
	uint16 sIndex;
	uint8 ZoneID;
	uint16 PosX;
	uint16 PosZ;
	uint8 Radius;
};

struct _USER_ITEM
{
	uint32 nItemID;
	std::vector<uint64> nItemSerial;
};

enum LootErrorCodes
{
	LootError					= 0,
	LootSolo					= 1,
	LootPartyCoinDistribution	= 2,
	LootPartyNotification		= 3,
	LootPartyItemGivenAway		= 4,
	LootPartyItemGivenToUs		= 5,
	LootNoRoom					= 6
};

enum BuffType
{
	BUFF_TYPE_NONE					= 0,
	BUFF_TYPE_HP_MP					= 1,
	BUFF_TYPE_AC					= 2,
	BUFF_TYPE_SIZE					= 3,
	BUFF_TYPE_DAMAGE				= 4,
	BUFF_TYPE_ATTACK_SPEED			= 5,
	BUFF_TYPE_SPEED					= 6,
	BUFF_TYPE_STATS					= 7,
	BUFF_TYPE_RESISTANCES			= 8,
	BUFF_TYPE_ACCURACY				= 9,
	BUFF_TYPE_MAGIC_POWER			= 10,
	BUFF_TYPE_EXPERIENCE			= 11,
	BUFF_TYPE_WEIGHT				= 12,
	BUFF_TYPE_WEAPON_DAMAGE			= 13,
	BUFF_TYPE_WEAPON_AC				= 14,
	BUFF_TYPE_LOYALTY				= 15,
	BUFF_TYPE_NOAH_BONUS			= 16,
	BUFF_TYPE_PREMIUM_MERCHANT		= 17,
	BUFF_TYPE_ATTACK_DAMAGE_AMOUNT	= 18,  // Berserker
	BUFF_TYPE_DAMAGE_DOUBLE			= 19,  // Critical Point
	BUFF_TYPE_DISABLE_TARGETING		= 20,  // Smoke Screen / Light Shock
	BUFF_TYPE_BLIND					= 21,  // Blinding (Strafe)
	BUFF_TYPE_FREEZE				= 22,  // Freezing Distance
	BUFF_TYPE_INSTANT_MAGIC			= 23,  // Instantly Magic
	BUFF_TYPE_DECREASE_RESIST		= 24,  // Minor resist
	BUFF_TYPE_MAGE_ARMOR			= 25,  // Fire / Ice / Lightning Armor
	BUFF_TYPE_PROHIBIT_INVIS		= 26,  // Source Marking
	BUFF_TYPE_RESIS_AND_MAGIC_DMG	= 27,  // Elysian Web
	BUFF_TYPE_TRIPLEAC_HALFSPEED	= 28,  // Wall of Iron || Divide Armor
	BUFF_TYPE_BLOCK_CURSE			= 29,  // Counter Curse
	BUFF_TYPE_BLOCK_CURSE_REFLECT	= 30,  // Curse Refraction
	BUFF_TYPE_MANA_ABSORB			= 31,  // Outrage / Frenzy
	BUFF_TYPE_IGNORE_WEAPON			= 32,  // Weapon cancellation
	BUFF_TYPE_VARIOUS_EFFECTS		= 33,  // ... whatever the event item grants.
	BUFF_TYPE_PASSION_OF_SOUL		= 35,  // Passion of the Soul
	BUFF_TYPE_FIRM_DETERMINATION	= 36,  // Firm Determination
	BUFF_TYPE_ATTACK_MAGIC_ATTACK	= 37,  // increases attack and magic attack percent
	BUFF_TYPE_ATTACK_TIME			= 39,  // increases attack by ** minutes
	BUFF_TYPE_SPEED2				= 40,  // Cold Wave -- Fear
	BUFF_TYPE_ARMORED				= 41,  // Armored Skin
	BUFF_TYPE_UNK_EXPERIENCE		= 42,  // unknown buff type, used for something relating to XP.
	BUFF_TYPE_ATTACK_RANGE_ARMOR	= 43,  // Inevitable Murderous
	BUFF_TYPE_MIRROR_DAMAGE_PARTY	= 44,  // Minak's Thorn 
	BUFF_TYPE_DAGGER_BOW_DEFENSE	= 45,  // Eskrima
	BUFF_TYPE_GM_BUFF				= 46,  // 30 minutes 10 all stats rise
	BUFF_TYPE_STUN					= 47,  // Lighting Skill 
	BUFF_TYPE_FISHING_FLASH			= 48,  // FISHING Skill- Premium FLASH
	BUFF_TYPE_DEVIL_TRANSFORM		= 49,  // Kurian/Porutu Devil Transformation
	BUFF_TYPE_DRAKEY				= 50,  // Drakey's Nemesis 
	BUFF_TYPE_SPEED3				= 52,  // Lost Speed
	BUFF_TYPE_LOYALTY_AMOUNT		= 55,  // Santa's Present
	BUFF_TYPE_NO_RECALL				= 150, // "Cannot use against the ones to be summoned"
	BUFF_TYPE_REDUCE_TARGET			= 151, // "Reduction" (reduces target's stats, but enlarges their character to make them easier to attack)
	BUFF_TYPE_SILENCE_TARGET		= 152, // Silences the target to prevent them from using any skills (or potions)
	BUFF_TYPE_NO_POTIONS			= 153, // "No Potion" prevents target from using potions.
	BUFF_TYPE_KAUL_TRANSFORMATION	= 154, // Transforms the target into a Kaul (a pig thing), preventing you from /town'ing or attacking, but increases defense.
	BUFF_TYPE_UNDEAD				= 155, // User becomes undead, increasing defense but preventing the use of potions and converting all health received into damage.
	BUFF_TYPE_UNSIGHT				= 156, // Blocks the caster's sight (not the target's).
	BUFF_TYPE_BLOCK_PHYSICAL_DAMAGE	= 157, // Blocks all physical damage.
	BUFF_TYPE_BLOCK_MAGICAL_DAMAGE	= 158, // Blocks all magical/skill damage.
	BUFF_TYPE_UNK_POTION			= 159, // unknown potion, "Return of the Warrior", "Comeback potion", perhaps some sort of revive?
	BUFF_TYPE_SLEEP					= 160, // Zantman (Sandman)
	BUFF_TYPE_INC_CONTRIBUTION		= 162, // Increase of the contribution
	BUFF_TYPE_INVISIBILITY_POTION	= 163, // "Unidentified potion"
	BUFF_TYPE_GODS_BLESSING			= 164, // Increases your defense/max HP 
	BUFF_TYPE_HELP_COMPENSATION		= 165, // Compensation for using the help system (to help, ask for help, both?)
	BUFF_TYPE_UNKNOW				= 166, // Unknow Skill Buff type
	BUFF_TYPE_IMIR_ROAR				= 167, // Creates a physical damage immune area around 10 meter radius of the caster for 20 seconds.
	BUFF_TYPE_LOGOS_HORNS			= 168, // Creates a magic damage immune area around 10 meter radius of the caster for 20 seconds.
	BUFF_TYPE_DROP_RATE				= 169, // During the 2-hour, +10% item drop rate.
	BUFF_TYPE_MAMA_MAGPIE			= 170, // Magpie is transformed into a mother
	BUFF_TYPE_BATTLE_CRY			= 171, // Battle Cry
	BUFF_TYPE_ATTACK_AMMONUT2		= 172, // Attack increased by 5%
};  

enum FlyingSantaOrAngel
{
	FLYING_NONE		= 0,
	FLYING_SANTA	= 1,
	FLYING_ANGEL	= 2
};

enum Chatroomopcodes
{
	CHATROOM_LIST			= 0x04,
	CHATROOM_CREATE			= 0x05,
	CHATROOM_JOIN			= 0x06,
	CHATROOM_LEAVE			= 0x07,
	CHATROOM_SEARCH			= 0x08,
	CHATROOM_UPDATECONFIG	= 0x09,
	CHATROOM_MEMBEROPTION	= 0x0B,
	CHATROOM_ADMIN			= 0x0C,
	CHATROOM_MANUEL			= 0x0B
};

#include "../shared/database/structs.h"