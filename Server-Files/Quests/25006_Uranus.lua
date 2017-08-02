local Ret = 0;
local NPC = 25006;

if (EVENT == 100) then
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 4515, NPC, 10, 193);
	elseif (QuestNum > 1 and  QuestNum < 100) then
		NpcMsg(UID, 4516, NPC)
	else
		EVENT = QuestNum
	end
end

local savenum = 1285;
local talknum = 44135;

if (EVENT == 110) then
SaveEvent(UID, 7855);
end

if (EVENT == 112) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, talknum, NPC, 22, 113, 23, 293);
	else
		SelectMsg(UID, 2, savenum, talknum, NPC, 10, 193);
	end
end

if (EVENT == 113) then
SaveEvent(UID, 7856);
end

if (EVENT == 114) then
SaveEvent(UID, 7858);
end

if (EVENT == 115) then
	MonsterCount = CountMonsterQuestSub(UID, 1285, 1);
	if (MonsterCount < 20) then
		SelectMsg(UID, 2, savenum, talknum, NPC, 18, 116);
	else
		SelectMsg(UID, 4, savenum, talknum, NPC, 41, 117, 27, 193);
	end
end

if (EVENT == 116) then
	ShowMap(UID, 1245);
end

if (EVENT == 117) then
	RunExchange(UID,6081)
	SaveEvent(UID, 7857);   
end
--Bu Luların'n satılması ve paylaşılması yasaktır.Created by TheThyke. Editör & Administrator
local savenum1 = 1286;
local talknum1 = 44136;

if (EVENT == 120) then
SaveEvent(UID, 7861);
end

if (EVENT == 122) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum1, talknum1, NPC, 22, 123, 23, 293);
	else
		SelectMsg(UID, 2, savenum1, talknum1, NPC, 10, 193);
	end
end

if (EVENT == 123) then
SaveEvent(UID, 7862);
end

if (EVENT == 124) then
SaveEvent(UID, 7864);
end


if (EVENT == 125) then
	MonsterCount = CountMonsterQuestSub(UID, 1286, 1);
	if (MonsterCount < 30) then
		SelectMsg(UID, 2, savenum1, talknum1, NPC, 18, 126);
	else
		SelectMsg(UID, 4, savenum1, talknum1, NPC, 41, 127, 27, 193);
	end
end

if (EVENT == 126) then
	ShowMap(UID, 488);
end

if (EVENT == 127) then
	RunExchange(UID,6082)
	SaveEvent(UID, 7863);   
end
--Bu Luların'n satılması ve paylaşılması yasaktır.Created by TheThyke. Editör & Administrator
local savenum2 = 1287;
local talknum2 = 44137;

if (EVENT == 130) then
SaveEvent(UID, 7867);
end

if (EVENT == 132) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum2, talknum2, NPC, 22, 133, 23, 293);
	else
		SelectMsg(UID, 2, savenum2, talknum2, NPC, 10, 193);
	end
end

if (EVENT == 133) then
SaveEvent(UID, 7868);
end

if (EVENT == 137) then
SaveEvent(UID, 7870);
end

if (EVENT == 134) then
	ShowMap(UID, 488);
end


if (EVENT == 135) then
	CONTTA = HowmuchItem(UID, 900687000);
	if (CONTTA < 10) then
		SelectMsg(UID, 2, savenum2, talknum2, NPC, 19, 134);
	else
		SelectMsg(UID, 4, savenum2, talknum2, NPC, 22, 136, 23, 158);
	end
end


if (EVENT == 136) then
	RunExchange(UID,6083)
	SaveEvent(UID, 7869);   
	end
--Bu Luların'n satılması ve paylaşılması yasaktır.Created by TheThyke. Editör & Administrator
local savenum3 = 1288;
local talknum3 = 44138;

if (EVENT == 140) then
SaveEvent(UID, 7873);
end

if (EVENT == 142) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum3, talknum3, NPC, 22, 143, 23, 293);
	else
		SelectMsg(UID, 2, savenum3, talknum3, NPC, 10, 193);
	end
end

if (EVENT == 143) then
SaveEvent(UID, 7874);
SaveEvent(UID, 7876);
end

if (EVENT == 145) then
		SelectMsg(UID, 4, savenum3, talknum3, NPC, 22, 146, 23, 158);
end

if (EVENT == 146) then
	RunExchange(UID,6084)
	SaveEvent(UID, 7875);   
end