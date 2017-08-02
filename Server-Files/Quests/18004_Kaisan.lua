local Ret = 0;
local NPC = 18004;
local savenum = -1;

if (EVENT == 101) then
 Ret = 1;
end

if (EVENT == 100) then   
	Level = CheckLevel(UID)
	if (Level > 9) then 
		Class = CheckClass(UID);
		if (Class == 1 or Class == 2 or Class == 3 or Class == 4 or Class == 13) then
			ITEM_COUNT = HowmuchItem(UID, 800560000);
			if (ITEM_COUNT < 3000) then
				SelectMsg(UID, 2, savenum, 4064, NPC, 4062, 404, 4063, 101);
			else
			SelectMsg(UID, 2, savenum, 4065, NPC, 10, 101);
			end
		else
			EVENT = 105
		end
	else
		SelectMsg(UID, 2, savenum, 4069, NPC, 10, 101);
	end
end

if (EVENT == 404) then
 UpdateEvent(UID, 4063);
 PromoteUserNovice(UID)
 GoldLose(UID, 3000)
 NATION = CheckNation(UID);
 if (NATION == 1) then
  SelectMsg(UID, 2, savenum, 4066, NPC, 4064, 101);
 else
  SelectMsg(UID, 2, savenum, 4067, NPC, 4064, 101);
 end
end

if (EVENT == 105) then
 SelectMsg(UID, 3, savenum, 147, NPC, 4070, 106, 8676, 1000, 8675, 900, 8674, 800, 8673, 107, 40532, 502, 8677, 700, 8678, 300, 8672, 600);
end

if (EVENT == 107) then
	SelectMsg(UID, 2, -1, 1532, NPC, 10, 108);
end

if (EVENT == 108) then
	SendNationTransfer(UID)
end

if (EVENT == 1000) then
  SelectMsg(UID, 2, 60, 1549, NPC, 10, 101);
end

if (EVENT == 106) then
 SelectMsg(UID, 2, savenum, 4070, NPC, 4070, 408, 10, 101);
end

if (EVENT == 408) then
 SendStatSkillDistribute(UID)
end

-- Repurchase Item
if (EVENT == 502) then
  SelectMsg(UID, 2, 60, 10745, NPC, 22, 171, 23, 101);
end

if (EVENT == 171) then
	SendRepurchase(UID)
end

if (EVENT == 800) then
  SelectMsg(UID, 2, 60, 1546, NPC, 7012, 801, 7013, 805);
end

if (EVENT == 801) then -- Need investigate
	SelectMsg(UID, 2, -1, 1532, NPC, 10, 108);
end

if (EVENT == 805) then -- Need investigate
LEADER = isClanLeader(UID)
	SelectMsg(UID, 2, 60, 1537, NPC, 10, 101);
end

if (EVENT == 900) then
	SelectMsg(UID, 2, 60, 1522, NPC, 7014, 901, 73, 903);
end

if (EVENT == 901) then
	SelectMsg(UID, 2, 60, 1532, NPC, 10, 902);
end

if (EVENT == 902) then
-- Usko sending nothing
end
if (EVENT == 903) then
-- Usko sending nothing
end

if (EVENT == 600) then
	SelectMsg(UID, 2, 60, 11640, NPC, 7014, 601, 73, 101);
end

if (EVENT == 601) then
	SelectMsg(UID, 2, 60, 11641, NPC, 10, 602);
end

if (EVENT == 602) then
-- Usko sending nothing
end

if (EVENT == 700) then
-- Usko sending nothing
end

if (EVENT == 300) then
	SelectMsg(UID, 2, 60, 44294, NPC, 4160, 301);
end

if (EVENT == 301) then
	SelectMsg(UID, 2, 60, 44295, NPC, 4161, 302, 4162, 101);
end

if (EVENT == 302) then
-- Premium Checks has the req premium no money else rob money 100m
SelectMsg(UID, 2, 60, 44296, NPC, 27, 101);
end