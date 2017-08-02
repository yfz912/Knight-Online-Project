local Ret = 0;
local NPC = 25020;

if (EVENT == 100) then
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 44135, NPC, 10, 193);
	elseif (QuestNum > 1 and  QuestNum < 100) then
		NpcMsg(UID, 44135, NPC)
	else
		EVENT = QuestNum
	end
end


local savenum = 1347;
local talknum = 44135;

if (EVENT == 1110) then
SaveEvent(UID, 3791);
end

if (EVENT == 1112) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, talknum, NPC, 22, 1113, 23, 293);
	else
		SelectMsg(UID, 2, savenum, talknum, NPC, 10, 193);
	end
end

if (EVENT == 1113) then
SaveEvent(UID, 3792);
end

if (EVENT == 1114) then
SaveEvent(UID, 3794);
end

if (EVENT == 1115) then
	MonsterCount = CountMonsterQuestSub(UID, 1347, 1);
	if (MonsterCount < 20) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 1116);
	else
		SelectMsg(UID, 4, savenum, talknum, NPC, 41, 1117, 27, 193);
	end
end

if (EVENT == 1116) then
	ShowMap(UID, 1245);
end

if (EVENT == 1117) then
	RunExchange(UID,6141)
	SaveEvent(UID, 3793);   
end
--Bu Luların'n satılması ve paylaşılması yasaktır.Created by TheThyke. Editör & Administrator

local savenum1 = 1348;
local talknum1 = 44136;

if (EVENT == 1120) then
SaveEvent(UID, 3797);
end

if (EVENT == 1122) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum1, talknum1, NPC, 22, 1123, 23, 293);
	else
		SelectMsg(UID, 2, savenum1, talknum1, NPC, 10, 193);
	end
end

if (EVENT == 1123) then
SaveEvent(UID, 3798);
end

if (EVENT == 1124) then
SaveEvent(UID, 3800);
end


if (EVENT == 1125) then
	MonsterCount = CountMonsterQuestSub(UID, 1348, 1);
	if (MonsterCount < 30) then
		SelectMsg(UID, 2, savenum1, talknum1, NPC, 18, 1126);
	else
		SelectMsg(UID, 4, savenum1, talknum1, NPC, 41, 1127, 27, 193);
	end
end

if (EVENT == 1126) then
	ShowMap(UID, 488);
end

if (EVENT == 1127) then
	RunExchange(UID,6142)
	SaveEvent(UID, 3799);   
end
--Bu Luların'n satılması ve paylaşılması yasaktır.Created by TheThyke. Editör & Administrator

local savenum2 = 1349;
local talknum2 = 44137;

if (EVENT == 1130) then
SaveEvent(UID, 3803);
end

if (EVENT == 1132) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum2, talknum2, NPC, 22, 1133, 23, 293);
	else
		SelectMsg(UID, 2, savenum2, talknum2, NPC, 10, 193);
	end
end

if (EVENT == 1133) then
SaveEvent(UID, 3804);
end

if (EVENT == 1137) then
SaveEvent(UID, 3806);
end

if (EVENT == 1134) then
	ShowMap(UID, 488);
end


if (EVENT == 1135) then
	CONTTA = HowmuchItem(UID, 900687000);
	if (CONTTA < 10) then
		SelectMsg(UID, 2, savenum2, talknum2, NPC, 19, 1134);
	else
		SelectMsg(UID, 4, savenum2, talknum2, NPC, 22, 1136, 23, 158);
	end
end


if (EVENT == 1136) then
	RunExchange(UID,6143)
	SaveEvent(UID, 3805);   
end


--Bu Luların'n satılması ve paylaşılması yasaktır.Created by TheThyke. Editör & Administrator
local savenum3 = 1350;
local talknum3 = 44138;

if (EVENT == 1140) then
SaveEvent(UID, 3809);
end

if (EVENT == 1142) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum3, talknum3, NPC, 22, 1143, 23, 293);
	else
		SelectMsg(UID, 2, savenum3, talknum3, NPC, 10, 193);
	end
end

if (EVENT == 1143) then
SaveEvent(UID, 3810);
SaveEvent(UID, 3812);
end

if (EVENT == 1145) then
		SelectMsg(UID, 4, savenum3, talknum3, NPC, 22, 1146, 23, 158);
end

if (EVENT == 1146) then
	RunExchange(UID,6144)
	SaveEvent(UID, 3811);   
end