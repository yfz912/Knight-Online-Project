local NPC = 32556;
local Ret = 0;

if (EVENT == 100) then
	NATION = CheckNation(UID);
	if (NATION == 2) then
		GiveItem(UID, 900071000, 1)
		SelectMsg(UID, 2, -1, 9846, NPC, 10, 101);
	else
	    GiveItem(UID, 900071000, 1)
		SelectMsg(UID, 2, -1, 1028, NPC, 10, 101);
	end	
end

if (EVENT == 101) then
	Ret = 1;
end