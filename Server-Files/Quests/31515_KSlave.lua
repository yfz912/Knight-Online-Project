local Ret = 0;
local NPC = 31515;

if (EVENT == 100) then
	QuestStatus = GetQuestStatus(UID, 539)
	
	if(QuestStatus == 1) then
		SaveEvent(UID, 11310)
	end
	
	
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 8256, NPC, 10, 158);
	elseif (QuestNum > 1 and  QuestNum < 100) then
		NpcMsg(UID, 8258, NPC)
	else
		EVENT = QuestNum
	end
end


local savenum=539
local talknum=20046
local exchangeid=3026

if(EVENT == 1002)then  -- Konuşma
	SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1006, 23, 112);
end

if(EVENT == 1006) then
	SaveEvent(UID, 11308)
end

if(EVENT == 1005) then
	SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1004, 23, 112);
end

if(EVENT == 1004) then
	SaveEvent(UID,11309)
end


local savenum=540
local talknum=20048
local exchangeid=3027

if(EVENT == 1101)then
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1102, 23, 112);
end

if(EVENT == 1102) then
	SaveEvent(UID, 11320)
end

if(EVENT == 1106) then
	ITEMA = HowmuchItem(UID, 508106000)	
	if(ITEMA > 0) then
		SaveEvent(UID, 11322)
	end
end

if(EVENT == 1103) then
	ITEMA = HowmuchItem(UID, 508106000)	
	if(ITEMA > 0) then
		SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1104, 23, 112);
	else
		SelectMsg(UID, 4, savenum, talknum, NPC, 10, 193);
	end
end

if(EVENT == 1104) then
	ITEMA = HowmuchItem(UID, 508106000)	
	if(ITEMA > 0) then
		RunSelectExchange(UID, exchangeid)
		SaveEvent(UID, 11321)
		SaveEvent(UID, 11332)
	else
		SelectMsg(UID, 4, savenum, talknum, NPC, 10, 193);
		SaveEvent(UID, 11320)
	end
end
