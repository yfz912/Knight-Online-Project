local UserClass;
local QuestNum;
local Ret = 0;
local NPC = 27200;

--Exit Event
if (EVENT == 101) then
	Ret = 1
end

--Menu Npc
if (EVENT == 100) then
	SelectMsg(UID, 3, -1, 7105, NPC, 9108, 150);	
end

if (EVENT == 150) then
	SelectMsg(UID, 3, -1, 7115, NPC, 9110, 151, 9111, 152);
end

if (EVENT == 151) then
	SelectMsg(UID, 3, -1, 7114, NPC, 10, 153);
end

--Join New Event
if (EVENT == 153) then
	CaveEventJoin(UID)
end

--EventCountUsers Check
if (EVENT == 152) then
	CaveEventLeave(UID)
end
		