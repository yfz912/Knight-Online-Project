local Ret = 0;
local NPC = 27600;

if (EVENT == 168) then
	Ret = 1
end

if EVENT == 100 then
	SelectMsg(UID, 2, 4502, 8667, NPC, 10, 175);
end

if (EVENT == 175) then
	SelectMsg(UID, 2, 4502, 175, NPC,  25, 176, 13, 168);
end

if (EVENT == 176) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 4502, 176, NPC, 22, 178, 23, 168);
	else
		SelectMsg(UID, 2, 4502, 173, NPC, 10, 168);
	end
end

if (EVENT == 178) then
	SaveEvent(UID, 49);
end

if (EVENT == 180) then
	SaveEvent(UID, 51);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 4502, 181, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 4502, 182, NPC, 14, 168);
	end
end

if (EVENT == 185) then
	MonsterCount = CountMonsterQuestSub(UID, 4502, 1);
	if (MonsterCount < 5) then
		SelectMsg(UID, 2, 4502, 186, NPC, 10, 188);
	else
		SelectMsg(UID, 2, 4502, 187, NPC, 10, 187, 27, 168);
	end
end

if (EVENT == 188) then
	ShowMap(UID, 1);
end

if (EVENT == 187) then
	ExpChange(UID, 20)
	GiveItem(UID, 389016000, 5)
	GiveItem(UID, 389010000, 10)
	SaveEvent(UID, 50);
end