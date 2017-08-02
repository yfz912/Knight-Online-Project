local NPC = 19005;
local Ret = 0;


if (EVENT == 100) then
 SelectMsg(UID, 3, 974, 8075, NPC, 4481, 101, 8265, 102, 3019, 203);
end

if (EVENT == 203) then
 Ret = 1;
end

if (EVENT == 560) then
	SelectMsg(UID, 53, -1, -1);
end

if (EVENT == 204) then
 ShowMap(UID, 336);
end

if (EVENT == 101) then
 MONEY = HowmuchItem(UID, 900000000);
 if (MONEY >= 10000) then
  SelectMsg(UID, 53, -1, -1);
 else
  SelectMsg(UID, 2, 974, 8084, NPC, 18, 204);
 end
end

if (EVENT == 205) then
 GoldLose(UID, 10000)
 SelectMsg(UID, 16, 974, NPC);
end

--Rebirth System
if (EVENT == 102) then
SelectMsg(UID, 3, 974, 11705, NPC, 8246, 208, 8254, 209, 8258 , 210, 8265, 211);
end

if (EVENT == 208) then
SelectMsg(UID, 2, 974, 11686, NPC, 8247,212);
end

if (EVENT == 212) then
SelectMsg(UID, 2, 974, 11687, NPC, 8248,213);
end

if (EVENT == 213) then
SelectMsg(UID, 2, 974, 11688, NPC, 8249,214);
end

if (EVENT == 214) then
SelectMsg(UID, 2, 974, 11689, NPC, 8250,215);
end

if (EVENT == 215) then
SelectMsg(UID, 2, 974, 11690, NPC, 8251,216);
end

if (EVENT == 216) then
SelectMsg(UID, 2, 974, 11691, NPC, 8252,217);
end

if (EVENT == 217) then
SelectMsg(UID, 2, 974, 11692, NPC, 8253,218);
end

if (EVENT == 218) then
SelectMsg(UID, 2, 974, 11693, NPC, 40223,219);
end

if (EVENT == 209) then
 SelectMsg(UID, 2, 974, 11695, NPC, 8255,220);
end

if (EVENT == 220) then
 SelectMsg(UID, 2, 974, 11696, NPC, 8256,221);
end

if (EVENT == 221) then
 SelectMsg(UID, 2, 974, 11697, NPC, 40223,222);
end
if (EVENT == 222) then
 MONEY = HowmuchItem(UID, 900000000);
 if (MONEY >= 100000000) then
 GoldLose(UID, 100000000)
 else
  SelectMsg(UID, 2, 974, 8084, NPC, 18, 204);
 end
end

if (EVENT == 210) then
	Loyalty = CheckLoyalty(UID,10000);
	if (Loyalty >= 10000) then
	RobLoyalty(UID, 10000);
	GiveItem(UID, 900579000, 1)
	else
 SelectMsg(UID, 2, 974, 11699, NPC, 8259,223);
 end
end

if (EVENT == 223) then
 SelectMsg(UID, 2, 974, 11700, NPC, 8260,224);
end

if (EVENT == 224) then
 SelectMsg(UID, 2, 974, 11701, NPC, 8256,225);
end

if (EVENT == 225) then
 SelectMsg(UID, 2, 974, 11702, NPC, 40223,226);
end

if (EVENT == 211) then
	bLevel = GetLevel(UID);
	bRebLevel = GetRebLevel(UID);
	bMaxExp = GetMaxExp(UID);
	bExp = GetExp(UID);
	if (bLevel < 83 or bRebLevel > 4) then
		SelectMsg(UID, 2, -1, 7116, NPC, 10, 151);
	elseif (bLevel == 83 and bExp < bMaxExp) then
		SelectMsg(UID, 2, -1, 7116, NPC, 10, 151);
	else
		SelectMsg(UID, 48, -1, -1);
	end
end

if (EVENT == 227) then
end