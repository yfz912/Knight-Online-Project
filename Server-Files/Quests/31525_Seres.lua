local Ret = 0;
local NPC = 31525;

if (EVENT == 100) then
	SelectMsg(UID, 3, -1, 12436, NPC, 8975, 8976, 8639, 7636, 10, 7587);
end

--Apparance Change
if (EVENT == 8976) then
	SelectMsg(UID, 24, -1, -1);	
end

--Gender Change
if (EVENT == 7636) then
	SelectMsg(UID, 53, -1, -1);
end

--Confirm
if (EVENT == 10) then
	Ret = 1;
end