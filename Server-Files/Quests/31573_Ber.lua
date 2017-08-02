local Ret = 0;
local NPC = 31573;

if (EVENT == 100) then
	QuestStatus = GetQuestStatus(UID, 631)
	
	if(QuestStatus == 1) then
		SaveEvent(UID, 12374)
	end

	
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then 
		SelectMsg(UID, 2, savenum, 4178, NPC, 10, 101);
	elseif (QuestNum > 1 and QuestNum < 100) then 
		NpcMsg(UID, 4174, NPC)
	else
		EVENT = QuestNum
	end
end

local savenum=631
local talknum=21242
local exchangeid=3116

if(EVENT == 1001) then  -- Chat
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1002, 23, 193);
end

if(EVENT == 1002) then
	SaveEvent(UID, 12372)
end

if(EVENT == 1003) then
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1004, 23, 193);
end

if(EVENT == 1004) then
	SaveEvent(UID, 12373)
end

local savenum=632
local talknum=21244
local exchangeid=3117

if(EVENT == 1101) then  -- Oak Posionus
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1102, 23, 193);
end

if(EVENT == 1102) then
	SaveEvent(UID, 12384)
end

if(EVENT == 1106) then
	SaveEvent(UID, 12386)
end

if(EVENT == 1105) then
	ITEMA = HowmuchItem(UID, 389520000)
	if(ITEMA < 4) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 193);
	else
		SelectMsg(UID, 4, savenum, talknum, NPC, 41, 1104, 27, 193); 
	end
end

if(EVENT == 1104) then
	RunExchange(UID, exchangeid)
	SaveEvent(UID, 12385)
	SaveEvent(UID, 12396)
end

local savenum=633
local exchangeid=3118
local talknum=21246

if(EVENT == 1201) then  -- Oak Posionus
	SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1202, 23, 193);
end

if(EVENT == 1202) then
	SaveEvent(UID, 12396)
end

if(EVENT == 1206) then
	SaveEvent(UID, 12398)
end

if(EVENT == 1205) then
	ITEMA = HowmuchItem(UID, 900151000)
	ITEMB = HowmuchItem(UID, 900156000)
	ITEMC = HowmuchItem(UID, 900165000)
	if(ITEMA < 1 and ITEMB < 1 and ITEMC < 1) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 193);
	else
		SelectMsg(UID, 4, savenum, talknum, NPC, 41, 1204, 27, 193); 
	end
end

if(EVENT == 1204) then
	RunExchange(UID, exchangeid)
	SaveEvent(UID, 12397)
end