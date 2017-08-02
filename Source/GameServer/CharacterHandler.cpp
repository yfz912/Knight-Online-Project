#include "stdafx.h"
#include "DBAgent.h"
#include "../shared/DateTime.h"
#include <cmath>
#include "Map.h"

using std::string;

#pragma region Nation Transfer

void CUser::RecvNationTransfer(Packet & pkt)
{
	RobItem(ITEM_NATION_TRANSFER);

	Packet result(WIZ_NATION_TRANSFER);

	uint8 kNation, kSuccess, kSuccess2, kAccountCount;
	uint8 kNewRace, unk3;
	uint16 kClass, kCharCount, unk, unk2;
	string kCharID;

	float Px = (float)818.000000, Pz = (float)435.000000, Py = (float)4.590000;

	pkt >> kSuccess >> kSuccess2 >> kAccountCount;

	for (int x = 0; x < kAccountCount; x++)
	{		
		pkt >> kCharCount >> kCharID >> kNewRace
			>> unk >> unk2 >> unk3;

		_NATION_DATA * pNation = m_NationTransferArray.GetData(kCharCount);
	
		if (!pNation)
			continue;

		if (pNation->bNation == KARUS)
		{
			kNation = pNation->bNation +1;
			kClass = (pNation->sClass + 100);
		}
		else
		{
			kNation = pNation->bNation -1;
			kClass = (pNation->sClass - 100);
		}

		if (kCharID == m_strUserID)
		{
			m_bRace = kNewRace;
			m_sClass = kClass;
			m_bNation = kNation;
			m_nHair = 0;
			m_bFace = 0;
			m_curx = Px;
			m_curz = Pz;
			m_cury = Px;
		}

		g_DBAgent.NationTransferSave(m_strAccountID, pNation->bCharName, kNewRace, kNation, kClass, this);

	}

	m_NationTransferArray.DeleteAllData();

	result << kSuccess
		<< kSuccess2;

	Send(&result);
}

void CUser::SendNationTransfer()
{
	Packet result(WIZ_NATION_TRANSFER);
	uint16	CharClass = 0, nNum = 0;
	uint8	CharNation, CharRace, AccountCount = 0, error = 1;
	string strCharID1, strCharID2, strCharID3, strCharID4;

	if (g_pMain->isWarOpen())
	{
		error = 1;
		goto ErrorWar;
	}

	_NATION_DATA* pNationTransfer = nullptr;

	g_DBAgent.GetAllCharID(m_strAccountID, strCharID1, strCharID2, strCharID3, strCharID4);
	
	if(strCharID1.length() != 0)
	{
		FindClanChar_Read(strCharID1, error, nNum, pNationTransfer);
		if (error > 1)
			goto ErrorInClan_IsKing;

		m_NationTransferArray.PutData(pNationTransfer->nNum, pNationTransfer);
		pNationTransfer = NULL;

		AccountCount++;
	}
	if(strCharID2.length() != 0)
	{
		FindClanChar_Read(strCharID2, error, nNum, pNationTransfer);
		if (error > 1)
			goto ErrorInClan_IsKing;

		m_NationTransferArray.PutData(pNationTransfer->nNum, pNationTransfer);
		pNationTransfer = NULL;

		AccountCount++;
	}
	if(strCharID3.length() != 0)
	{
		FindClanChar_Read(strCharID3, error, nNum, pNationTransfer);
		if (error > 1)
			goto ErrorInClan_IsKing;

		m_NationTransferArray.PutData(pNationTransfer->nNum, pNationTransfer);
		pNationTransfer = NULL;

		AccountCount++;
	}
	if(strCharID4.length() != 0)
	{
		FindClanChar_Read(strCharID4, error, nNum, pNationTransfer);
		if (error > 1)
			goto ErrorInClan_IsKing;
	
		m_NationTransferArray.PutData(pNationTransfer->nNum, pNationTransfer);
		pNationTransfer = NULL;

		AccountCount++;
	}	

	result << uint8(NationOpenBox)		// 1 = war status || 2 = open box || 3 = success transfered
		<< uint8(error)						// 1 Sopen Box || 2 = if any in clan error
		<< uint8(AccountCount);				// Character count in Account

	for (int x = 0; x < AccountCount; x++)
	{
		_NATION_DATA * pNation = m_NationTransferArray.GetData(x);
	
		if (!pNation)
			continue;

		if (pNation->bNation == KARUS)
		{
			if (pNation->bRace == KARUS_BIG)
				CharRace = BABARIAN;
			else if (pNation->bRace == KARUS_MIDDLE)
				CharRace = ELMORAD_MAN;
			else if (pNation->bRace == KARUS_SMALL)
				CharRace = ELMORAD_MAN;
			else if (pNation->bRace == KARUS_WOMAN)
				CharRace = ELMORAD_WOMAN;
			else if (pNation->bRace == KARUS_KURIAN)
				CharRace = ELMORAD_PORTU;

			CharNation = pNation->bNation +1;
			CharClass = (pNation->sClass + 100);			
		}
		else
		{
			if (m_bRace == BABARIAN)
				CharRace = KARUS_BIG;
			else if (m_bRace == ELMORAD_MAN && pNation->sClass == 206)
				CharRace = KARUS_BIG;
			else if (m_bRace == ELMORAD_WOMAN && pNation->sClass == 206)
				CharRace = KARUS_BIG;
			else if (m_bRace == ELMORAD_MAN && pNation->sClass == 208)
				CharRace = KARUS_MIDDLE;
			else if (m_bRace == ELMORAD_WOMAN && pNation->sClass == 208)
				CharRace = KARUS_MIDDLE;
			else if (m_bRace == ELMORAD_MAN && pNation->sClass == 210)
				CharRace = KARUS_SMALL;
			else if (m_bRace == ELMORAD_WOMAN && pNation->sClass == 210)
				CharRace = KARUS_WOMAN;
			else if (m_bRace == ELMORAD_MAN && pNation->sClass == 212)
				CharRace = KARUS_MIDDLE;
			else if (m_bRace == ELMORAD_WOMAN && pNation->sClass == 212)
				CharRace = KARUS_WOMAN;
			else if (m_bRace == ELMORAD_PORTU)
				CharRace = KARUS_KURIAN;

			CharNation = pNation->bNation -1;
			CharClass = (pNation->sClass - 100);
		}

		result	<< uint16(pNation->nNum)
			<< pNation->bCharName
			<< uint8(CharRace)
			<< uint8(CharNation)
			<< uint16(CharClass)
			<< uint8(0)
			<< uint32(0);
	}
	
	Send(&result);
	return;

ErrorInClan_IsKing:
	result << uint8(NationOpenBox)
		<< error;
	Send(&result);
	return;

ErrorWar:
	result << uint8(NationWarStatus)
		<< error
		<< uint16(1)
		<< uint16(2);
	Send(&result);
}

void CUser::FindClanChar_Read(string strCharID, uint8 & error, uint16 & nNum, _NATION_DATA* & m_NationTransfer)
{
	error  = g_DBAgent.NationTransferValidate(strCharID.c_str());
	if (error > 1)
		return;

	g_DBAgent.GetAllCharInfo(strCharID, nNum, m_NationTransfer);
}

void CUser::RecvGenderChange(Packet & pkt)
{
	int8 opcode, gRace, gFace; 
	uint32 bHair;

	pkt >> opcode >> gRace >> gFace >> bHair;

	m_bRace = gRace;
	m_bFace = gFace;
	m_nHair = bHair;

	Packet result(WIZ_GENDER_CHANGE, uint8(GenderSuccess));
	result << m_bRace
		<< m_bFace
		<< m_nHair
		<< GetClass();
	

	Send(&result);
}
/*
uint8 CUser::NationChange()
{
	if(!CheckExistItem(ITEM_NATION_TRANSFER))
		return 1; // Item does exist.

	bool CanNT1 = false;
	bool CanNT2 = false;
	bool CanNT3 = false;
	bool CanNT4 = false;

	uint8 sRet  =0;
	string strCharID1, strCharID2, strCharID3, strCharID4;

	g_DBAgent.GetAllCharID(m_strAccountID, strCharID1, strCharID2, strCharID3, strCharID4);
	 
	if(strCharID1.length() != 0)
	{
		sRet  = g_DBAgent.NationTransferValidate(strCharID1.c_str());	 
		if ( sRet> 0)
			return sRet; // 2 = Character(s) in the clan / 3 = Database error.
		else
			CanNT1 = true;
	}

	if( strCharID2.length() != 0)
	{
		sRet  = g_DBAgent.NationTransferValidate(strCharID2.c_str());	 
		if ( sRet> 0)
			return sRet; // 2 = Character(s) in the clan / 3 = Database error.
		else
			CanNT2 = true;
	}
	
	if( strCharID3.length() != 0)
	{
		sRet  = g_DBAgent.NationTransferValidate(strCharID3.c_str());	 
		if ( sRet> 0)
			return sRet; // 2 = Character(s) in the clan / 3 = Database error.
		else
			CanNT3 = true;
	}

	if( strCharID4.length() != 0)
	{
		sRet  = g_DBAgent.NationTransferValidate(strCharID4.c_str());	 
		if ( sRet> 0)
			return sRet; // 2 = Character(s) in the clan / 3 = Database error.
		else
			CanNT4 = true;
	}

	if (CanNT1 == true)
		g_DBAgent.NationTransfer(m_strAccountID, strCharID1.c_str());

	if (CanNT2 == true)
		g_DBAgent.NationTransfer(m_strAccountID, strCharID2.c_str());

	if (CanNT3 == true)
		g_DBAgent.NationTransfer(m_strAccountID, strCharID3.c_str());

	if (CanNT4 == true)
		g_DBAgent.NationTransfer(m_strAccountID, strCharID4.c_str());

	RobItem(ITEM_NATION_TRANSFER);

	// if database operation is successfull but inline code have a problem disconnect to user...
	if (GetNewRace() == 0)
		Disconnect();
	
	m_bRank = 0;
	m_bTitle = 0;
	m_bRace = GetNewRace();
	m_sClass = GetNation() == KARUS ? GetClass() + 100 : GetClass() - 100;	
	m_bNation = GetNation() == KARUS ? ELMORAD : KARUS;
	
	if (GetHealth() < (GetMaxHealth() / 2))
		HpChange(GetMaxHealth());

	SendMyInfo();

	InitType4();
	RecastSavedMagic();

	return 0; // Successfull
}
*/
uint8 CUser::GetNewRace()
{
	uint8 nNewRace = 0;

	if (GetNation() == KARUS)
	{
		if (m_bRace == KARUS_BIG)
			nNewRace = BABARIAN;
		else if (m_bRace == KARUS_MIDDLE)
			nNewRace = ELMORAD_MAN;
		else if (m_bRace == KARUS_SMALL)
			nNewRace = ELMORAD_MAN;
		else if (m_bRace == KARUS_WOMAN)
			nNewRace = ELMORAD_WOMAN;
		else if (m_bRace == KARUS_KURIAN)
			nNewRace = ELMORAD_PORTU;
	}
	else
	{
		if (m_bRace == BABARIAN)
			nNewRace = KARUS_BIG;
		// El Morad Male and El Morad Warriors
		else if (m_bRace == ELMORAD_MAN && isWarrior())
			nNewRace = KARUS_BIG;
		// El Morad Female and El Morad Warriors
		else if (m_bRace == ELMORAD_WOMAN && isWarrior())
			nNewRace = KARUS_BIG;
		// El Morad Male and El Morad Rogues
		else if (m_bRace == ELMORAD_MAN && isRogue())
			nNewRace = KARUS_MIDDLE;
		// El Morad Female and El Morad Rogues
		else if (m_bRace == ELMORAD_WOMAN && isRogue())
			nNewRace = KARUS_MIDDLE;
		// El Morad Male and El Morad Magicians
		else if (m_bRace == ELMORAD_MAN && isMage())
			nNewRace = KARUS_SMALL;
		// El Morad Female and El Morad Magicians
		else if (m_bRace == ELMORAD_WOMAN && isMage())
			nNewRace = KARUS_WOMAN;
		// El Morad Male and El Morad Priests
		else if (m_bRace == ELMORAD_MAN && isPriest())
			nNewRace = KARUS_MIDDLE;
		// El Morad Female and El Morad Priests
		else if (m_bRace == ELMORAD_WOMAN && isPriest())
			nNewRace = KARUS_WOMAN;
		// El Morad Portu
		else if (m_bRace == ELMORAD_PORTU)
			nNewRace = KARUS_KURIAN;
	}

	return nNewRace;
}

#pragma endregion

#pragma region Gender Change

bool CUser::GenderChange(uint8 Race /*= 0*/)
{
	if (Race == 0 || Race > 14)
		return false; 

	if(!CheckExistItem(ITEM_GENDER_CHANGE))
		return false; 

	RobItem(ITEM_GENDER_CHANGE);

	m_bRace = Race;

	g_DBAgent.UpdateUser(GetName(), UPDATE_PACKET_SAVE, this);

	if (GetHealth() < (GetMaxHealth() / 2))
		HpChange(GetMaxHealth());

	SendMyInfo();

	UserInOut(INOUT_OUT);
	SetRegion(GetNewRegionX(), GetNewRegionZ());
	UserInOut(INOUT_WARP);

	g_pMain->UserInOutForMe(this);
	g_pMain->NpcInOutForMe(this);
	g_pMain->MerchantUserInOutForMe(this);

	ResetWindows();

	InitType4();
	RecastSavedMagic();

	return true;
}

#pragma endregion

#pragma region Job Change

uint8 CUser::JobChange(uint8 NewJob /*= 0*/)
{
	uint8 bNewClass = 0, bNewRace = 0;
	uint8 bResult = 0;

	if (NewJob < 1 || NewJob > 4)
		return 5; // Unknown job is selected...

	if(!CheckExistItem(ITEM_JOB_CHANGE))
		return 6; // Job Change scroll is not found...

	for (int i = 0; i < SLOT_MAX; i++)
	{
		if (m_sItemArray[i].nNum) 
		{
			bResult = 7;
			break;
		}
	}

	if (bResult == 7)
	{
		Packet result(WIZ_CLASS_CHANGE, uint8(ALL_POINT_CHANGE));
		result << uint8(4) << int(0);
		Send(&result);
		return bResult; // While there are items equipped on you.
	}

	// If bResult between 1 and 4 character already selected job...

	// If selected a new job Warrior
	if (NewJob == 1)
	{
		if (GetNation() == KARUS)
		{
			// Beginner Karus Rogue, Magician, Priest
			if (isBeginnerRogue() || isBeginnerMage() || isBeginnerPriest() || isBeginnerKurPor())
			{
				bNewClass = KARUWARRIOR;
				bNewRace = KARUS_BIG;
			}
			// Skilled Karus Rogue, Magician, Priest
			else if (isNoviceRogue() || isNoviceMage() || isNovicePriest() || isNoviceKurPor())
			{
				bNewClass = BERSERKER;
				bNewRace = KARUS_BIG;
			}
			// Mastered Karus Rogue, Magician, Priest
			else if (isMasteredRogue() || isMasteredMage() || isMasteredPriest() || isMasteredKurPor())
			{
				bNewClass = GUARDIAN;
				bNewRace = KARUS_BIG;
			}
			// Beginner Karus Kurian
			else if (isBeginnerRogue() || isBeginnerMage() || isBeginnerPriest() || isBeginnerWarrior())
			{
				bNewClass = KARUKURIAN;
				bNewRace = KARUS_KURIAN;
			}
			else if (isMasteredRogue() || isNoviceMage() || isNovicePriest() || isNoviceWarrior())
			{
				bNewClass = KURIANN;
				bNewRace = KARUS_KURIAN;
			}
			else if (isMasteredRogue() || isMasteredMage() || isMasteredPriest() || isMasteredWarrior())
			{
				bNewClass = KURIANM;
				bNewRace = KARUS_KURIAN;
			}
		}
		else
		{
			// Beginner El Morad Rogue, Magician, Priest
			if (isBeginnerRogue() || isBeginnerMage() || isBeginnerPriest() || isBeginnerKurPor())
			{
				bNewClass = ELMORWARRRIOR;
				bNewRace = GetRace();
			}
			else if (isBeginnerRogue() || isBeginnerMage() || isBeginnerPriest() || isBeginnerWarrior())
			{
				bNewClass = ELMOPORTU;
				bNewRace = GetRace();
			}
			// Skilled El Morad Rogue, Magician, Priest
			else if (isNoviceRogue() || isNoviceMage() || isNovicePriest() || isNoviceKurPor())
			{
				bNewClass = BLADE;
				bNewRace = GetRace();
			}
			else if (isNoviceRogue() || isNoviceMage() || isNovicePriest() || isNoviceWarrior())
			{
				bNewClass = PORTUN;
				bNewRace = GetRace();
			}
			// Mastered El Morad Rogue, Magician, Priest
			else if (isMasteredRogue() || isMasteredMage() || isMasteredPriest() || isMasteredKurPor())
			{
				bNewClass = PROTECTOR;
				bNewRace = GetRace();
			}
			else if (isMasteredRogue() || isMasteredMage() || isMasteredPriest() || isMasteredWarrior())
			{
				bNewClass = PORTUM;
				bNewRace = GetRace();
			}
		}

		// Character already Warrior.
		if (bNewClass == 0 || bNewRace == 0)		
			bResult = NewJob;
	}

	// If selected a new job Rogue
	if (NewJob == 2)
	{
		if (GetNation() == KARUS)
		{
			// Beginner Karus Warrior, Magician, Priest
			if (isBeginnerWarrior() || isBeginnerMage() || isBeginnerPriest() || isBeginnerKurPor())
			{
				bNewClass = KARUROGUE;
				bNewRace = KARUS_MIDDLE;
			}
			// Skilled Karus Warrior, Magician, Priest
			else if (isNoviceWarrior() || isNoviceMage() || isNovicePriest() || isNoviceKurPor())
			{
				bNewClass = HUNTER;
				bNewRace = KARUS_MIDDLE;
			}
			// Mastered Karus Warrior, Magician, Priest
			else if (isMasteredWarrior() || isMasteredMage() || isMasteredPriest() || isMasteredKurPor())
			{
				bNewClass = PENETRATOR;
				bNewRace = KARUS_MIDDLE;
			}
		}
		else
		{
			// Beginner El Morad Warrior, Magician, Priest
			if (isBeginnerWarrior() || isBeginnerMage() || isBeginnerPriest() || isBeginnerKurPor())
			{
				bNewClass = ELMOROGUE;

				if (GetRace() == BABARIAN)
					bNewRace = ELMORAD_MAN;
				else
					bNewRace = GetRace();
			}
			// Skilled El Morad Warrior, Magician, Priest
			else if (isNoviceWarrior() || isNoviceMage() || isNovicePriest() || isNoviceKurPor())
			{
				bNewClass = RANGER;

				if (GetRace() == BABARIAN)
					bNewRace = ELMORAD_MAN;
				else
					bNewRace = GetRace();
			}
			// Mastered El Morad Warrior, Magician, Priest
			else if (isMasteredWarrior() || isMasteredMage() || isMasteredPriest() || isMasteredKurPor())
			{
				bNewClass = ASSASSIN;

				if (GetRace() == BABARIAN)
					bNewRace = ELMORAD_MAN;
				else
					bNewRace = GetRace();
			}
		}

		// Character already Rogue.
		if (bNewClass == 0 || bNewRace == 0)
			bResult = NewJob;
	}

	// If selected a new job Magician
	if (NewJob == 3)
	{
		if (GetNation() == KARUS)
		{
			// Beginner Karus Warrior, Rogue, Priest
			if (isBeginnerWarrior() || isBeginnerRogue() || isBeginnerPriest() || isBeginnerKurPor())
			{
				bNewClass = KARUWIZARD;

				if (GetRace() == KARUS_BIG || GetRace() == KARUS_MIDDLE)
					bNewRace = KARUS_SMALL;
				else
					bNewRace = GetRace();
			}
			// Skilled Karus Warrior, Rogue, Priest
			else if (isNoviceWarrior() || isNoviceRogue() || isNovicePriest() || isNoviceKurPor())
			{
				bNewClass = SORSERER;

				if (GetRace() == KARUS_BIG || GetRace() == KARUS_MIDDLE)
					bNewRace = KARUS_SMALL;
				else
					bNewRace = GetRace();
			}
			// Mastered Karus Warrior, Rogue, Priest
			else if (isMasteredWarrior() || isMasteredRogue() || isMasteredPriest() || isMasteredKurPor())
			{
				bNewClass = NECROMANCER;

				if (GetRace() == KARUS_BIG || GetRace() == KARUS_MIDDLE)
					bNewRace = KARUS_SMALL;
				else
					bNewRace = GetRace();
			}
		}
		else
		{
			// Beginner El Morad Warrior, Rogue, Priest
			if (isBeginnerRogue() || isBeginnerRogue() || isBeginnerPriest() || isBeginnerKurPor())
			{
				bNewClass = ELMOWIZARD;

				if (GetRace() == BABARIAN)
					bNewRace = ELMORAD_MAN;
				else
					bNewRace = GetRace();
			}
			// Skilled El Morad Warrior, Rogue, Priest
			else if (isNoviceWarrior() || isNoviceRogue() || isNovicePriest() || isNoviceKurPor())
			{
				bNewClass = MAGE;

				if (GetRace() == BABARIAN)
					bNewRace = ELMORAD_MAN;
				else
					bNewRace = GetRace();
			}
			// Mastered El Morad Warrior, Rogue, Priest
			else if (isMasteredWarrior() || isMasteredRogue() || isMasteredPriest() || isMasteredKurPor())
			{
				bNewClass = ENCHANTER;

				if (GetRace() == BABARIAN)
					bNewRace = ELMORAD_MAN;
				else
					bNewRace = GetRace();
			}
		}

		// Character already Magician.
		if (bNewClass == 0 || bNewRace == 0)
			bResult = NewJob;
	}

	// If selected a new job Priest
	if (NewJob == 4)
	{
		if (GetNation() == KARUS)
		{
			// Beginner Karus Warrior, Rogue, Magician
			if (isBeginnerWarrior() || isBeginnerRogue() || isBeginnerMage() || isBeginnerKurPor())
			{
				bNewClass = KARUPRIEST;

				if (GetRace() == KARUS_BIG || GetRace() == KARUS_SMALL)
					bNewRace = KARUS_MIDDLE;
				else
					bNewRace = GetRace();
			}
			// Skilled Karus Warrior, Rogue, Magician
			else if (isNoviceWarrior() || isNoviceRogue() || isNoviceMage() || isNoviceKurPor())
			{
				bNewClass = SHAMAN;

				if (GetRace() == KARUS_BIG || GetRace() == KARUS_SMALL)
					bNewRace = KARUS_MIDDLE;
				else
					bNewRace = GetRace();
			}
			// Mastered Karus Warrior, Rogue, Magician
			else if (isMasteredRogue() || isMasteredRogue() || isMasteredMage() || isMasteredKurPor())
			{
				bNewClass = DARKPRIEST;

				if (GetRace() == KARUS_BIG || GetRace() == KARUS_SMALL)
					bNewRace = KARUS_MIDDLE;
				else
					bNewRace = GetRace();
			}
		}
		else
		{
			// Beginner El Morad Warrior, Rogue, Magician
			if (isBeginnerRogue() || isBeginnerRogue() || isBeginnerMage() || isBeginnerKurPor())
			{
				bNewClass = ELMOPRIEST;

				if (GetRace() == BABARIAN)
					bNewRace = ELMORAD_MAN;
				else
					bNewRace = GetRace();
			}
			// Skilled El Morad Warrior, Rogue, Magician
			else if (isNoviceRogue() || isNoviceRogue() || isNoviceMage() || isNoviceKurPor())
			{
				bNewClass = CLERIC;

				if (GetRace() == BABARIAN)
					bNewRace = ELMORAD_MAN;
				else
					bNewRace = GetRace();
			}
			// Mastered El Morad Warrior, Rogue, Magician
			else if (isMasteredRogue() || isMasteredRogue() || isMasteredMage() || isMasteredKurPor())
			{
				bNewClass = DRUID;

				if (GetRace() == BABARIAN)
					bNewRace = ELMORAD_MAN;
				else
					bNewRace = GetRace();
			}
		}
	}

	// If selected a new job Kurian/Portu
	if (NewJob == 5)
	{
		if (GetNation() == KARUS)
		{
			// Beginner Karus Warrior, Rogue, Magician
			if (isBeginnerWarrior() || isBeginnerRogue() || isBeginnerMage() || isBeginnerPriest())
			{
				bNewClass = KARUKURIAN;
				bNewRace = GetRace();
			}
			// Skilled Karus Warrior, Rogue, Magician
			else if (isNoviceWarrior() || isNoviceRogue() || isNoviceMage() || isNovicePriest())
			{
				bNewClass = KURIANN;
				bNewRace = GetRace();
			}
			// Mastered Karus Warrior, Rogue, Magician
			else if (isMasteredRogue() || isMasteredRogue() || isMasteredMage() || isMasteredPriest())
			{
				bNewClass = KURIANM;
				bNewRace = GetRace();
			}
		}
		else
		{
			// Beginner El Morad Warrior, Rogue, Magician
			if (isBeginnerRogue() || isBeginnerRogue() || isBeginnerMage() || isBeginnerPriest())
			{
				bNewClass = ELMOPORTU;
				bNewRace = GetRace();
			}
			// Skilled El Morad Warrior, Rogue, Magician
			else if (isNoviceRogue() || isNoviceRogue() || isNoviceMage() || isNovicePriest())
			{
				bNewClass = PORTUN;
				bNewRace = GetRace();
			}
			// Mastered El Morad Warrior, Rogue, Magician
			else if (isMasteredRogue() || isMasteredRogue() || isMasteredMage() || isMasteredPriest())
			{
				bNewClass = PORTUM;
				bNewRace = GetRace();
			}
		}

		// Character already Priest.
		if (bNewClass == 0 || bNewRace == 0)
			bResult = NewJob;
	}

	if (bResult == 0)
	{
		RobItem(ITEM_JOB_CHANGE);

		m_sClass = bNewClass;
		m_bRace = bNewRace;

		// Reset stat and skill points...
		AllPointChange(true);
		AllSkillPointChange(true);

		g_DBAgent.UpdateUser(GetName(), UPDATE_PACKET_SAVE, this);

		if (GetHealth() < (GetMaxHealth() / 2))
			HpChange(GetMaxHealth());

		SendMyInfo();

		UserInOut(INOUT_OUT);
		SetRegion(GetNewRegionX(), GetNewRegionZ());
		UserInOut(INOUT_WARP);

		g_pMain->UserInOutForMe(this);
		g_pMain->NpcInOutForMe(this);
		g_pMain->MerchantUserInOutForMe(this);

		ResetWindows();

		InitType4();
		RecastSavedMagic();
	}

	return bResult;
}

#pragma endregion