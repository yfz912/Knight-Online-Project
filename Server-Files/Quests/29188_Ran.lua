local Ret = 0;
local NPC = 29188;

if (EVENT == 100) then
	SelectMsg(UID, 3, -1, 11972, NPC, 8534, 168, 4074, 169);
end

if (EVENT == 168) then
	Time = CheckUnderTheCastleTime(UID)
	if (Time == 1) then
		Count = CheckUnderTheCastleUserCount(UID)
		if (Count < 3000) then
			ItemA = HowmuchItem(UID, 900000000); 
			if (ItemA > 100000) then
				GoldLose(UID, 100000)
				ZoneChange(UID, 86, 69, 64)
			else
				SelectMsg(UID, 2, -1, 10544, NPC, 18, 200);
			end
		else
			SelectMsg(UID, 2, -1, 10544, NPC, 10, 169);
		end
	else
		SelectMsg(UID, 2, -1, 10544, NPC, 10, 169);
	end
end

if (EVENT == 169) then
	Ret = 1;
end