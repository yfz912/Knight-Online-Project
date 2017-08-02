#include "stdafx.h"
#include "Map.h"
#include "../shared/DateTime.h"
#include <cmath>

void CUser::PetHandle(Packet & pkt)
{
	Packet result(WIZ_PET, uint8(0));
	Send(&result);
}