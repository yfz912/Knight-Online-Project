local Ret = 0;
local NPC = 25017;


if (EVENT == 100) then
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 43796, NPC, 10, 193);
	elseif (QuestNum > 1 and  QuestNum < 100) then
		SelectMsg(UID, 2, -1, 43796, NPC, 8818, 300, 8819, 400);
	else
		EVENT = QuestNum
	end
end

if (EVENT == 193) then
	Ret = 1;
end


-- First quest

if (EVENT == 300) then
	SelectMsg(UID, 2, -1, 43801, NPC, 40191, 301);
end

if (EVENT == 301) then
	SelectMsg(UID, 2, -1, 43802, NPC, 40236, 302);
end

if (EVENT == 302) then
	SelectMsg(UID, 2, -1, 43803, NPC, 40237, 303, 47, 193);
end

if (EVENT == 303) then
	SelectMsg(UID, 4, savenum, 156, NPC, 22, 112, 23, 193);
end


-- Second quest

if (EVENT == 400) then
	SelectMsg(UID, 2, -1, 43806, NPC, 40238, 401, 4591, 193);
end

if (EVENT == 401) then
	SelectMsg(UID, 4, savenum, 156, NPC, 22, 112, 23, 193);
end