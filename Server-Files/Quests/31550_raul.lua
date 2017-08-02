local Ret = 0;
local NPC = 31550;

if (EVENT == 100) then
	QuestStatus = GetQuestStatus(UID, 621)
	
	if(QuestStatus == 1) then
		SaveEvent(UID, 12302)
	end

	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then 
		SelectMsg(UID, 2, -1, 1312, NPC, 10, 193);
	elseif (QuestNum > 1 and  QuestNum < 100) then
		NpcMsg(UID, 1313, NPC)
	else
		EVENT = QuestNum
	end
end

if (EVENT == 193) then
	Ret = 1;
end


local savenum=621
local talknum=21230
local exchangeid=3110

if(EVENT == 1001) then -- Konuşma
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1002, 23, 193);
end

if(EVENT == 1002) then
	SaveEvent(UID,12300)
end

if(EVENT == 1003) then
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1004, 23, 193);
end

if(EVENT == 1004) then
	SaveEvent(UID, 12301)
end

local savenum=622
local talknum=21232
local exchangeid=3111

if(EVENT == 1101) then -- Kabold
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1102, 23, 193);
end

if(EVENT == 1102) then
	SaveEvent(UID,12312)
end

if(EVENT == 1106) then
	SaveEvent(UID, 12314)
end

if(EVENT == 1105) then
	
	MonsterCount = CountMonsterQuestSub(UID, savenum, 1);
	if (MonsterCount < 7) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 193);
	else
		SaveEvent(UID, 12314)
		SelectMsg(UID, 4, savenum, talknum, NPC, 41, 1104, 27, 193);
	end
end

if(EVENT == 1104) then
	RunExchange(UID, exchangeid)
	SaveEvent(UID,12313);
end

local savenum=624
local talknum=21234
local exchangeid=3112

if(EVENT == 1201) then -- Bulgear
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1202, 23, 193);
end

if(EVENT == 1202) then
	SaveEvent(UID,12324)
end

if(EVENT == 1206) then
	SaveEvent(UID, 12326)
end

if(EVENT == 1205) then
	
	MonsterCount = CountMonsterQuestSub(UID, savenum, 1);
	if (MonsterCount < 7) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 193);
	else
		SaveEvent(UID, 12326)
		SelectMsg(UID, 4, savenum, talknum, NPC, 41, 1204, 27, 193);
	end
end

if(EVENT == 1204) then
	RunExchange(UID, exchangeid)
	SaveEvent(UID,12325);
end

local savenum=626
local talknum=21236
local exchangeid=3113

if(EVENT == 1301) then -- Pooka
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1302, 23, 193);
end

if(EVENT == 1302) then
	SaveEvent(UID,12336)
end

if(EVENT == 1306) then
	SaveEvent(UID, 12338)
end

if(EVENT == 1305) then	
	MonsterCount = CountMonsterQuestSub(UID, savenum, 1);
	if (MonsterCount < 7) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 193);
	else
		SaveEvent(UID, 12338)
		SelectMsg(UID, 4, savenum, talknum, NPC, 41, 1304, 27, 193);
	end
end

if(EVENT == 1304) then
	RunExchange(UID, exchangeid)
	SaveEvent(UID,12337);
end

local savenum=628
local talknum=21238
local exchangeid=3114


if(EVENT == 1401) then -- Pooka
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1402, 23, 193);
end

if(EVENT == 1402) then
	SaveEvent(UID,12348)
end

if(EVENT == 1406) then
	SaveEvent(UID, 12350)
end

if(EVENT == 1405) then	
	MonsterCount = CountMonsterQuestSub(UID, savenum, 1);
	if (MonsterCount < 7) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 193);
	else
		SaveEvent(UID, 12350)
		SelectMsg(UID, 4, savenum, talknum, NPC, 41, 1404, 27, 193);
	end
end

if(EVENT == 1404) then
	RunExchange(UID, exchangeid)
	SaveEvent(UID,12349);
	SaveEvent(UID, 12360);
end
