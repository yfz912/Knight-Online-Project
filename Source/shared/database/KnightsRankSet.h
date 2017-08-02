#pragma once

class CKnightsRankSet : public OdbcRecordset
{
public:
	CKnightsRankSet(OdbcConnection * dbConnection, void * dummy) 
		: OdbcRecordset(dbConnection), nKarusCount(0), nElmoCount(0) 
	{
		memset(&strKarusCaptain, 0, sizeof(strKarusCaptain));
		memset(&strElmoCaptain, 0, sizeof(strElmoCaptain));
	}

	virtual tstring GetTableName() { return _T("KNIGHTS_RATING"); }
	virtual tstring GetColumns() { return _T("nRank, shIndex, nPoints"); }

	int rKCount;
	int rECount;

	virtual bool Fetch()
	{
		_KNIGHTS_RATING * pData = new _KNIGHTS_RATING;

		if(!g_pMain->nFirst)
		{
			rKCount = 1;
			rECount = 1;
			g_pMain->nFirst = true;
		}

		_dbCommand->FetchUInt32(1, pData->nRank);
		_dbCommand->FetchUInt16(2, pData->sClanID);
		_dbCommand->FetchUInt32(3, pData->nPoints);

		CKnights *pKnights = g_pMain->GetClanPtr(pData->sClanID);
		if (pKnights == nullptr 
			|| (pKnights->m_byNation != KARUS && pKnights->m_byNation != ELMORAD))
		{
			delete pData;
			return true;
		}

		if (pKnights->m_byNation == KARUS)
		{
			pData->nSlot = rKCount++;

			if (!g_pMain->m_KnightsRatingArray[0].PutData(pData->nSlot, pData))
			{
				delete pData;
				rKCount--;
				return true;
			}

			if (nKarusCount == 5)
				return true;

			CUser *pUser = g_pMain->GetUserPtr(pKnights->m_strChief, TYPE_CHARACTER);
			if (pUser == nullptr || !pUser->GetMap()->isWarZone())
				return true;

			if (pUser->GetClanID() == pData->sClanID)
			{
				_snprintf(strKarusCaptain[nKarusCount++], 50, "[%s][%s]", pKnights->m_strName.c_str(), pUser->GetName().c_str());
				pUser->ChangeFame(COMMAND_CAPTAIN);
			}
		}
		else if (pKnights->m_byNation == ELMORAD)
		{
			pData->nSlot = rECount++;

			if (!g_pMain->m_KnightsRatingArray[1].PutData(pData->nSlot, pData))
			{
				delete pData;
				rECount--;
				return true;
			}

			if (nElmoCount == 5)
				return true;

			CUser *pUser = g_pMain->GetUserPtr(pKnights->m_strChief, TYPE_CHARACTER);
			if (pUser == nullptr || !pUser->GetMap()->isWarZone())
				return true;

			if (pUser->GetClanID() == pData->sClanID)
			{
				_snprintf(strElmoCaptain[nElmoCount++], 50, "[%s][%s]", pKnights->m_strName.c_str(), pUser->GetName().c_str());
				pUser->ChangeFame(COMMAND_CAPTAIN);
			}
		}

		g_pMain->nFirst = false;
		return true;
	}

	char strKarusCaptain[5][50], strElmoCaptain[5][50];	
	uint32 nKarusCount, nElmoCount;
};