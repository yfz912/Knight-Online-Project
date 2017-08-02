local Ret = 0;
local NPC = 29001;

if (EVENT == 200) then
	SelectMsg(UID, 2, -1, 43611, NPC, 40426, 300, 40427, 400, 40428, 500, 40429, 600);
end   

if (EVENT == 193) then
	Ret = 1;
end
