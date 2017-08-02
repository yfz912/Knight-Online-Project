local Ret = 0;
local NPC = 25073;

if (EVENT == 100) then
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 8256, NPC, 10, 158);
	elseif (QuestNum > 1 and  QuestNum < 100) then
		NpcMsg(UID, 8258, NPC)
	else
		EVENT = QuestNum
	end
end

local savenum = 1200
if(EVENT == 102) then -- 
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 8244, NPC, 22, 106, 23, 158);
	else
		SelectMsg(UID, 2, savenum, 8265, NPC, 10, 158);
	end
end

if(EVENT == 106) then
	SaveEvent(UID, 7310)
end

if(EVENT == 107) then
	SaveEvent(UID, 7312)
end

if(EVENT == 105) then
	CountA = HowmuchItem(UID, 810418000)
	
	if( CountA < 2) then
		SelectMsg(UID, 2, savenum, 8267, NPC, 18, 108);
	else
		SelectMsg(UID, 5, savenum, 8268, NPC, 41, 110, 27, 158);
	end
end

if(EVENT == 108) then
	ShowMap(UID, 1)
end

if(EVENT == 110) then
	RunSelectExchange(UID, 6000);
	SaveEvent(UID, 7311)
end

local savenum = 1201

if(EVENT == 112) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 8244, NPC, 22, 114, 23, 158);
	else
		SelectMsg(UID, 2, savenum, 8265, NPC, 10, 158);
	end
end

if(EVENT == 114) then
	SaveEvent(UID, 7317)
end

if(EVENT == 117) then
	SaveEvent(UID, 7319)
end

if(EVENT == 115) then
	CountA = HowmuchItem(UID, 810418000)
	
	if( CountA < 2) then
		SelectMsg(UID, 2, savenum, 8267, NPC, 18, 118);
	else
		SelectMsg(UID, 5, savenum, 8268, NPC, 41, 120, 27, 158);
	end
end

if (EVENT == 118 ) then
	ShowMap(UID, 2)
end

if(EVENT == 120) then
	RunSelectExchange(UID, 6001);
	SaveEvent(UID, 7318)
end


local savenum = 1202


if(EVENT == 122) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 8244, NPC, 22, 124, 23, 158);
	else
		SelectMsg(UID, 2, savenum, 8265, NPC, 10, 158);
	end
end

if(EVENT == 124) then
	SaveEvent(UID, 7324)
end

if(EVENT == 128) then
	SaveEvent(UID, 7326)
end

if(EVENT == 125) then
	MonsterCount  = CountMonsterQuestSub(UID, savenum, 1);
	if (MonsterCount < 5) then
		SelectMsg(UID, 2, savenum, 8267, NPC, 18, 129);
	else
		SelectMsg(UID, 5, savenum, 8268, NPC, 41, 130, 27, 158);
	end
end

if(EVENT == 129) then
	ShowMap(UID, 2)
end

if(EVENT == 130) then
	RunSelectExchange(UID, 6002);
	SaveEvent(UID, 7325)
end
