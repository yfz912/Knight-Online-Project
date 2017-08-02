local Ret = 0;
local NPC = 29519;


if (EVENT == 100) then
	SelectMsg(UID, 3, -1, 44505, NPC, 40595, 101, 40596, 102, 40597, 103, 40598, 104,40599,105);
end



if (EVENT == 105) then
	LIKE = HowmuchItem(UID, 910334000);
	if (LIKE < 1) then
		SelectMsg(UID, 2, -1, 44506, NPC, 19, 106);
	else
		SelectMsg(UID, 2, -1, 44506, NPC, 10, 107);
	end
end

if (EVENT == 107) then
GiveItem(UID,810333856,1,7)
RobItem(UID, 910334000, 1)
end

if (EVENT == 101) then
SelectMsg(UID, 150, -1, 44506, NPC, 19, 106);
end


