local Ret = 0;
local NPC= 29071;

if (EVENT == 100) then
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 4174, NPC, 10, 101);
	elseif (QuestNum > 1 and  QuestNum < 100) then
		NpcMsg(UID, 4174, NPC)
	else
		EVENT = QuestNum
	end
end

if (EVENT == 101) then
	Ret = 1;
end

local savenum = 780
local talknum = 22986
--Chat 2
if(EVENT == 1001) then
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1002, 23, 101);
end

if(EVENT == 1002) then
	SaveEvent(UID, 13717)
	SaveEvent(UID, 13719)
end

if(EVENT == 1003) then
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1004, 23, 101);
end

if(EVENT == 1004) then
	SaveEvent(UID,13718)
end

local talknum=22988
local savenum=781

if(EVENT == 1101) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, talknum, NPC, 3018, 1102, 3019, 101);
	else
		SelectMsg(UID, 2, savenum, talknum, NPC, 4242, 101);
	end
end

if(EVENT == 1102) then
	SaveEvent(UID, 13723)
end