local Ret = 0;
local NPC = 32552;
local savenum = -1;

if (EVENT == 100) then
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 1057, NPC, 4171, 102,4169,101);
	elseif (QuestNum > 1 and QuestNum < 100) then
		NpcMsg(UID, 1057, NPC)
	else
		EVENT = QuestNum
	end
end

if (EVENT == 101) then
	Ret = 1;
end

if (EVENT == 102) then
Nation = CheckNation(UID);
if (Nation == 2) then
SelectMsg(UID, 2, -1, 1057, NPC, 23);
else
GiveItem(UID,900068000,1)
end
end