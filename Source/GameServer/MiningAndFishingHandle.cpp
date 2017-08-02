#include "stdafx.h"
#include "Map.h"
#include "../shared/DateTime.h"

void CUser::HandleMiningSystem(Packet & pkt)
{
	uint8 opcode;
	pkt >> opcode;

	switch (opcode)
	{
	case MiningStart:
		HandleMiningStart(pkt);
		break;

	case MiningAttempt:
		HandleMiningAttempt(pkt);
		break;

	case MiningStop:
		HandleMiningStop(pkt);
		break;

	case FishingStart:
		HandleFishingStart(pkt);
		break;

	case FishingAttempt:
		HandleFishingAttempt(pkt);
		break;

	case FishingStop:
		HandleFishingStop(pkt);
		break;

	case MiningSoccer:
		HandleSoccer(pkt);
		break;

	default:
		TRACE("[SID=%d] Unknown packet %X\n", GetSocketID(), opcode);
		return;
	}
}

/**
* @brief	Handles users requesting to start mining.
* 			NOTE: This is a mock-up, so be warned that it does not 
* 			handle checks such as identifying if the user is allowed
* 			to mine in this area.
*
* @param	pkt	The packet.
*/
void CUser::HandleMiningStart(Packet & pkt)
{
	Packet result(WIZ_MINING, uint8(MiningStart));
	uint16 resultCode = MiningResultSuccess;

	if (isMining())
		resultCode = MiningResultMiningAlready;

	_ITEM_DATA * pItem;
	_ITEM_TABLE * pTable = GetItemPrototype(RIGHTHAND, pItem);
	if (pItem == nullptr || pTable == nullptr
		|| pItem->sDuration <= 0
		|| !pTable->isPickaxe())
		resultCode = MiningResultNotPickaxe;

	if (m_bResHpType == USER_SITDOWN)
		resultCode = MiningResultError;

	result << resultCode;

	if (resultCode == MiningResultSuccess)
	{
		m_bMining = true;
		result << GetID();
		SendToRegion(&result);
	}
	else
	{
		Send(&result);
	}
}


void CUser::HandleMiningAttempt(Packet & pkt)
{
    if (!isMining())
        return;

    Packet result(WIZ_MINING, uint8(MiningAttempt));
    uint16 resultCode = MiningResultSuccess;

    _ITEM_DATA * pItem;
    _ITEM_TABLE * pTable = GetItemPrototype(RIGHTHAND, pItem);
    if (pItem == nullptr || pTable == nullptr
        || pItem->sDuration <= 0
        || !pTable->isPickaxe())
        resultCode = MiningResultNotPickaxe;

    if ((UNIXTIME - m_tLastMiningAttempt) < MINING_DELAY)
        resultCode = MiningResultMiningAlready;

    uint16 sEffect = 0;

    if (resultCode == MiningResultSuccess)
    {
        int rate = myrand(1, 100), random = myrand(1, 10000);

        if (m_bPremiumInUse > 0)
        {
            rate += (rate / 100) * GetPremiumProperty(PremiumDropPercent);
            random += (rate / 100) * GetPremiumProperty(PremiumDropPercent);
        }

        if (pTable->m_iNum == GOLDEN_MATTOCK)
        {
            rate += (rate / 100) * 10;
            random += (random / 100) * 10;
        }

        if (rate > 100)
            rate = 100;
        if (random > 10000)
            random = 10000;

        if (rate <= 50 && random <= 5000)
        {
            if (pTable->m_iNum == MATTOCK) {
                if(GetLevel() > 1 && GetLevel() < 10)
                {
                    ExpChange(50);
                } else if(GetLevel() > 10 && GetLevel() < 20) {
                    ExpChange(100);
                } else if(GetLevel() > 20 && GetLevel() < 30) {
                    ExpChange(200);
                } else if(GetLevel() > 30 && GetLevel() < 40) {
                    ExpChange(300);
                } else if(GetLevel() > 40 && GetLevel() < 50) {
                    ExpChange(400);
                } else if(GetLevel() > 50 && GetLevel() < 60) {
                    ExpChange(500);
                } else if(GetLevel() > 60 && GetLevel() < 70) {
                    ExpChange(1000);
                } else if(GetLevel() > 70 && GetLevel() <= 83) {
                    ExpChange(2000);
                }
            } else if(pTable->m_iNum == GOLDEN_MATTOCK) {
                if(GetLevel() > 1 && GetLevel() < 10)
                {
                    ExpChange(100);
                } else if(GetLevel() > 10 && GetLevel() < 20) {
                    ExpChange(200);
                } else if(GetLevel() > 20 && GetLevel() < 30) {
                    ExpChange(300);
                } else if(GetLevel() > 30 && GetLevel() < 40) {
                    ExpChange(400);
                } else if(GetLevel() > 40 && GetLevel() < 50) {
                    ExpChange(500);
                } else if(GetLevel() > 50 && GetLevel() < 60) {
                    ExpChange(600);
                } else if(GetLevel() > 60 && GetLevel() < 70) {
                    ExpChange(1200);
                } else if(GetLevel() > 70 && GetLevel() <= 83) {
                    ExpChange(2400);
                }
            }
            sEffect = 13082;
        }
        else if (rate >= 75 && rate <= 100 && random <= 10000)
        {
            if (pTable->m_iNum == MATTOCK) {
                int MiningItemRandomGroup = 0;
                srand((unsigned)time(0));
                MiningItemRandomGroup = rand() % 16;
                switch(MiningItemRandomGroup) {
					case 1:
                        GiveItem(g_pMain->m_rainworm); 
                    break;
                    case 2:
                        GiveItem(g_pMain->m_Drop1); 
                    break;
                    case 3:
                        GiveItem(g_pMain->m_Drop2); 
                    break;
                    case 4:
                        GiveItem(g_pMain->m_Drop3); 
                    break;
                    case 5:
                        GiveItem(g_pMain->m_Drop4); 
                    break;
                    case 6:
                        GiveItem(g_pMain->m_Drop5); 
                    break;
                    case 7:
                        GiveItem(g_pMain->m_Drop6); 
                    break;
                    case 8:
                        GiveItem(g_pMain->m_Drop7); 
                    break;
                    case 9:
                        GiveItem(g_pMain->m_Drop8); 
                    break;
                    case 10:
                        GiveItem(g_pMain->m_Drop9); 
                    break;
					case 11:
                        GiveItem(g_pMain->m_Drop10); 
                    break;
					case 12:
                        GiveItem(g_pMain->m_Drop11); 
                    break;
					case 13:
                        GiveItem(g_pMain->m_Drop12); 
                    break;
					case 14:
                        GiveItem(g_pMain->m_Drop13); 
                    break;
					case 15:
                        GiveItem(g_pMain->m_Drop14); 
                    break;
					case 16:
                        GiveItem(g_pMain->m_Drop15); 
                    break;

					default:
                        GiveItem(g_pMain->m_rainworm); 
                    break;

                }            
            }
			
			else if(pTable->m_iNum == GOLDEN_MATTOCK) {
                int MiningItemRandomGroup = 0;
                srand((unsigned)time(0));
                MiningItemRandomGroup = rand() % 16;
                switch(MiningItemRandomGroup) {

					case 1:
                        GiveItem(g_pMain->m_grainworm); 
                    break;
                    case 2:
                        GiveItem(g_pMain->m_gDrop1); 
                    break;
                    case 3:
                        GiveItem(g_pMain->m_gDrop2); 
                    break;
                    case 4:
                        GiveItem(g_pMain->m_gDrop3); 
                    break;
                    case 5:
                        GiveItem(g_pMain->m_gDrop4); 
                    break;
                    case 6:
                        GiveItem(g_pMain->m_gDrop5); 
                    break;
                    case 7:
                        GiveItem(g_pMain->m_gDrop6); 
                    break;
                    case 8:
                        GiveItem(g_pMain->m_gDrop7); 
                    break;
                    case 9:
                        GiveItem(g_pMain->m_gDrop8); 
                    break;
                    case 10:
                        GiveItem(g_pMain->m_gDrop9); 
                    break;
					case 11:
                        GiveItem(g_pMain->m_gDrop10); 
                    break;
					case 12:
                        GiveItem(g_pMain->m_gDrop11); 
                    break;
					case 13:
                        GiveItem(g_pMain->m_gDrop12); 
                    break;
					case 14:
                        GiveItem(g_pMain->m_gDrop13); 
                    break;
					case 15:
                        GiveItem(g_pMain->m_gDrop14); 
                    break;
					case 16:
                        GiveItem(g_pMain->m_gDrop15); 
                    break;

					default:
                        GiveItem(g_pMain->m_grainworm); 
                    break;

                }            
            }

            sEffect = 13081;
        }
        else
        {
        }

        m_tLastMiningAttempt = UNIXTIME;
    }

    result << resultCode << GetID() << sEffect;

    ItemWoreOut(ATTACK,100); 

    if (resultCode != MiningResultSuccess
        && resultCode != MiningResultNothingFound)
    {
        Send(&result);
        HandleMiningStop(pkt);
        return;
    }

    if(resultCode != MiningResultNothingFound)
        SendToRegion(&result);
    else if(resultCode == MiningResultNothingFound)
        Send(&result);
}

void CUser::HandleMiningStop(Packet & pkt)
{
	if (!isMining())
		return;

	Packet result(WIZ_MINING, uint8(MiningStop));
	result << uint16(1) << GetID();
	m_bMining = false;
	SendToRegion(&result);
}


void CUser::HandleFishingStart(Packet & pkt)
{
	Packet result(WIZ_MINING, uint8(FishingStart));
	uint16 resultCode = MiningResultSuccess;

	if (isMining())
		resultCode = MiningResultMiningAlready;

	_ITEM_DATA * pItem;
	_ITEM_TABLE * pTable = GetItemPrototype(RIGHTHAND, pItem);
	if (pItem == nullptr || pTable == nullptr
		|| pItem->sDuration <= 0
		|| !pTable->isFishing()
		|| GetItemCount(RAINWORM) <= 0)
		resultCode = MiningResultNotPickaxe;

	result << resultCode;

	if (resultCode == MiningResultSuccess)
	{
		m_bMining = true;
		result << GetID();
		SendToRegion(&result);
	}
	else
	{
		Send(&result);
	}
}


void CUser::HandleFishingAttempt(Packet & pkt)
{
	if (!isMining())
		return;

	Packet result(WIZ_MINING, uint8(FishingAttempt));

	uint16 resultCode = MiningResultSuccess;

	_ITEM_DATA * pItem;
	_ITEM_TABLE * pTable = GetItemPrototype(RIGHTHAND, pItem);
	if (pItem == nullptr || pTable == nullptr
		|| pItem->sDuration <= 0
		|| !pTable->isFishing()
		|| GetItemCount(RAINWORM) <= 0)
		resultCode = MiningResultNotPickaxe;

	if ((UNIXTIME - m_tLastMiningAttempt) < MINING_DELAY)
		resultCode = MiningResultMiningAlready; 

	uint16 sEffect = 0;

	if (resultCode == MiningResultSuccess)
	{
		int rate = myrand(1, 100), random = myrand(1, 10000);

		if (GetPremiumProperty(PremiumDropPercent) > 0)
		{
			rate += (rate / 100) * GetPremiumProperty(PremiumDropPercent);
			random += (rate / 100) * GetPremiumProperty(PremiumDropPercent);
		}

		if (pTable->m_iNum == GOLDEN_FISHING)
		{
			rate += (rate / 100) * 10;
			random += (random / 100) * 10;
		}

		if (rate > 100)
			rate = 100;
		if (random > 10000)
			random = 10000;

		if (rate <= 50 && random <= 5000)
		{
			if (GetLevel() >= 35 && GetLevel() <= 59)
				ExpChange(100);
			if (GetLevel() >= 60 && GetLevel() <= 69)
				ExpChange(200);
			if (GetLevel() >= 70)
				ExpChange(300);


			sEffect = 13082;
		}

			        else if (rate >= 75 && rate <= 100 && random <= 10000)
        {
            if (pTable->m_iNum == FISHING) {
                int MiningItemRandomGroup = 0;
                srand((unsigned)time(0));
                MiningItemRandomGroup = rand() % 12;
                switch(MiningItemRandomGroup) {
					case 1:
                        GiveItem(g_pMain->f_Drop1); 
                    break;
                    case 2:
                        GiveItem(g_pMain->f_Drop2); 
                    break;
                    case 3:
                        GiveItem(g_pMain->f_Drop3); 
                    break;
                    case 4:
                        GiveItem(g_pMain->f_Drop4); 
                    break;
                    case 5:
                        GiveItem(g_pMain->f_Drop5); 
                    break;
                    case 6:
                        GiveItem(g_pMain->f_Drop6); 
                    break;
                    case 7:
                        GiveItem(g_pMain->f_Drop7); 
                    break;
                    case 8:
                        GiveItem(g_pMain->f_Drop8); 
                    break;
                    case 9:
                        GiveItem(g_pMain->f_Drop9); 
                    break;
                    case 10:
                        GiveItem(g_pMain->f_Drop10); 
                    break;
					case 11:
                        GiveItem(g_pMain->f_Drop11); 
					break;
					case 12:
                        GiveItem(g_pMain->f_Drop12); 
                    break;
                }            
            }
			
			else if(pTable->m_iNum == GOLDEN_FISHING) {
                int MiningItemRandomGroup = 0;
                srand((unsigned)time(0));
                MiningItemRandomGroup = rand() % 12;
                switch(MiningItemRandomGroup) {

                    case 1:
                        GiveItem(g_pMain->f_gDrop1); 
                    break;
                    case 2:
                        GiveItem(g_pMain->f_gDrop2); 
                    break;
                    case 3:
                        GiveItem(g_pMain->f_gDrop3); 
                    break;
                    case 4:
                        GiveItem(g_pMain->f_gDrop4); 
                    break;
                    case 5:
                        GiveItem(g_pMain->f_gDrop5); 
                    break;
                    case 6:
                        GiveItem(g_pMain->f_gDrop6); 
                    break;
                    case 7:
                        GiveItem(g_pMain->f_gDrop7); 
                    break;
                    case 8:
                        GiveItem(g_pMain->f_gDrop8); 
                    break;
                    case 9:
                        GiveItem(g_pMain->f_gDrop9); 
                    break;
					case 10:
                        GiveItem(g_pMain->f_gDrop10); 
                    break;
					case 11:
                        GiveItem(g_pMain->f_gDrop11); 
                    break;
					case 12:
                        GiveItem(g_pMain->f_gDrop12); 
                    break;
                }            
            }

            sEffect = 13081;
        }
									
			else
		{
			sEffect = 30731;
		}
		
		m_tLastMiningAttempt = UNIXTIME;
	}

	result << resultCode << GetID() << sEffect;
	RobItem(RAINWORM,1);
	ItemWoreOut(ATTACK,100); 

	if (resultCode != MiningResultSuccess
		&& resultCode != MiningResultNothingFound)
	{
		Send(&result);
		HandleFishingStop(pkt);
		return;
	}

	if(resultCode != MiningResultNothingFound)
		SendToRegion(&result);
	else if(resultCode == MiningResultNothingFound)
		Send(&result);

}

void CUser::HandleFishingStop(Packet & pkt)
{
	if (!isMining())
		return;

	Packet result(WIZ_MINING, uint8(FishingStop));
	result << uint16(1) << GetID();
	m_bMining = false;
	SendToRegion(&result);
}
