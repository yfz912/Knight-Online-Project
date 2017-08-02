#include "stdafx.h"
#include "Map.h"
#include "../shared/DateTime.h"
#include <cmath>

void CUser::HandleSoccer(Packet & pkt)
{
	Packet result(WIZ_MINING, uint8(MiningSoccer));
	uint16 resultCode = MiningResultSuccess;

	if (isMining())
		resultCode = MiningResultMiningAlready;

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