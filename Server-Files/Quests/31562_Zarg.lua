local Ret = 0;
local NPC = 31562;

if (EVENT == 100) then
	QuestStatus = GetQuestStatus(UID, 663)
	
	if(QuestStatus == 1) then
		SaveEvent(UID, 12753)
	end
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 3156, NPC, 3001, 193);
	elseif (QuestNum > 1 and  QuestNum < 100) then
		NpcMsg(UID, 1175, NPC)
	else
		EVENT = QuestNum
	end
end

if(EVENT == 193) then
	Ret = -1
end
--Görev 1 Konuşma

local savenum=663
local talknum=21305
local exchangeid=3148

if(EVENT == 1001)then  
	SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1006, 23, 112);
end

if(EVENT == 1006) then
	SaveEvent(UID, 12751)
end

if(EVENT == 1003) then
	SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1004, 23, 112);
end

if(EVENT == 1004) then
	SaveEvent(UID,12752)
end

-- Görev 2 HornCrossbow
local savenum=664
local talknum=21307
local exchangeid=3149

if(EVENT == 1101)then  
	SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1102, 23, 112);
end

if(EVENT == 1102) then
	SaveEvent(UID, 12761)
end

if(EVENT == 1106) then
	SaveEvent(UID, 12763)
end

if(EVENT == 1105)then
	ITEMA = HowmuchItem(UID, 370004000)	
	ITEMB = HowmuchItem(UID, 168210003)	
	ITEMC = HowmuchItem(UID, 391010000)	
	if(ITEMA > 9 and ITEMB > 0 and ITEMC > 4999) then
		SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1107, 23, 193);
	else
		SelectMsg(UID, 4, savenum, talknum, NPC, 10, 193);
	end
end

if(EVENT == 1107) then
	ITEMA = HowmuchItem(UID, 370004000)	
	ITEMB = HowmuchItem(UID, 168210003)	
	ITEMC = HowmuchItem(UID, 391010000)	
	if(ITEMA > 9 and ITEMB > 0 and ITEMC > 4999) then
		RunSelectExchange(UID, exchangeid)
		SaveEvent(UID, 12764)
	end
end

 -- Görev 3 Hornet
local savenum=665
local talknum=21309
local exchangeid=3150

if(EVENT == 1201)then 
	SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1202, 23, 112);
end

if(EVENT == 1202) then
	SaveEvent(UID, 12775)
end

if(EVENT == 1206) then
	SaveEvent(UID, 12777)
end

if(EVENT == 1205) then
	MonsterCount = CountMonsterQuestSub(UID, savenum, 1);
	if (MonsterCount < 7) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 1007);
	else
		SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1207, 23, 193);
	end
end

if(EVENT == 1207) then
	RunSelectExchange(UID, 3150)
	SaveEvent(UID, 12776)
end

-- Görev 4 - Tyon

local savenum=667
local talknum=21311
local exchangeid=3151

if(EVENT == 1301)then 
	SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1302, 23, 112);
end

if(EVENT == 1302) then
	SaveEvent(UID, 12787)
end

if(EVENT == 1306) then
	SaveEvent(UID, 12789)
end

if(EVENT == 1305) then
	MonsterCount = CountMonsterQuestSub(UID, savenum, 1);
	if (MonsterCount < 7) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 193);
	else
		SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1307, 23, 193);
	end
end

if(EVENT == 1307) then
	RunSelectExchange(UID, exchangeid )
	SaveEvent(UID, 12788)
end

-- Görev 5 - Undying

local savenum=669
local talknum=21313
local exchangeid=3152
local complateindex=12801
local acceptindex=12799
local rewardindex=12800

if(EVENT == 1401)then 
	SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1402, 23, 112);
end

if(EVENT == 1402) then
	SaveEvent(UID, acceptindex)
end

if(EVENT == 1406) then
	SaveEvent(UID, complateindex)
end

if(EVENT == 1405) then
	MonsterCount = CountMonsterQuestSub(UID, savenum, 1);
	if (MonsterCount < 7) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 193);
	else
		SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1407, 23, 193);
	end
end

if(EVENT == 1407) then
	RunSelectExchange(UID, exchangeid )
	SaveEvent(UID, rewardindex)
end

-- Görev 5 - Half troll warrior

local savenum=671
local talknum=21315
local exchangeid=3153
local complateindex=12813
local acceptindex=12811
local rewardindex=12812

if(EVENT == 1501)then 
	SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1502, 23, 112);
end

if(EVENT == 1502) then
	SaveEvent(UID, acceptindex)
end

if(EVENT == 1506) then
	SaveEvent(UID, complateindex)
end

if(EVENT == 1505) then
	MonsterCount = CountMonsterQuestSub(UID, savenum, 1);
	if (MonsterCount < 7) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 193);
	else
		SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1507, 23, 193);
	end
end

if(EVENT == 1507) then
	RunSelectExchange(UID, exchangeid )
	SaveEvent(UID, rewardindex)
end

-- Görev 6 - Centaur

local savenum=673
local talknum=21317
local exchangeid=3154
local acceptindex=12823
local rewardindex=12824
local complateindex=12825

if(EVENT == 1601)then 
	SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1602, 23, 112);
end

if(EVENT == 1602) then
	SaveEvent(UID, acceptindex)
end

if(EVENT == 1606) then
	SaveEvent(UID, complateindex)
end

if(EVENT == 1605) then
	MonsterCount = CountMonsterQuestSub(UID, savenum, 1);
	if (MonsterCount < 7) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 193);
	else
		SelectMsg(UID, 5, savenum, talknum, NPC, 22, 1607, 23, 193);
	end
end

if(EVENT == 1607) then
	RunSelectExchange(UID, exchangeid )
	SaveEvent(UID, rewardindex)
end