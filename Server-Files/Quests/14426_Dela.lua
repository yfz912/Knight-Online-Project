local Ret = 0;
local NPC = 14426;

if (EVENT == 190) then
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 4605, NPC, 10, 193);
	elseif (QuestNum > 1 and  QuestNum < 100) then
		NpcMsg(UID, 4606, NPC)
	else
		EVENT = QuestNum
	end
end

if (EVENT == 193) then
	Ret = 1;
end

local savenum = 987;

if (EVENT == 170) then -- 60 Level Darkness Knight
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 244, NPC, 22, 171, 23, 172);
	else
		SelectMsg(UID, 2, savenum, 244, NPC, 10, 193);
	end
end

if (EVENT == 171) then
	UpdateEvent(UID, 209);
end

if (EVENT == 172) then
	UpdateEvent(UID, 212);
end

if (EVENT == 174) then
	UpdateEvent(UID, 211);
	SelectMsg(UID, 2, savenum, 244, NPC, 14, 193);
end

if (EVENT == 175) then
	MonsterCount = CountMonsterQuestSub(UID, 987, 1);
	if (MonsterCount < 120) then
		SelectMsg(UID, 2, savenum, 244, NPC, 18, 177);
	else
		SelectMsg(UID, 4, savenum, 244, NPC, 41, 176, 27, 193);
	end
end

if (EVENT == 177) then
	ShowMap(UID, 80);
end

if (EVENT == 176) then
	Prem = GetPremium(UID);
	if (Prem > 0) then
		ExpChange(UID, 1200000)
		UpdateEvent(UID, 210);  
	else
		ExpChange(UID, 500000)
		UpdateEvent(UID, 210); 
	end   
end

local savenum = 988;

if (EVENT == 180) then -- 60 Level Troll Shaman
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 261, NPC, 22, 181, 23, 182);
	else
		SelectMsg(UID, 2, savenum, 261, NPC, 10, 193);
	end
end

if (EVENT == 181) then
	UpdateEvent(UID, 219);
end

if (EVENT == 182) then
	UpdateEvent(UID, 222);
end

if (EVENT == 184) then
	UpdateEvent(UID, 221);
	SelectMsg(UID, 2, savenum, 224, NPC, 14, 193);
end

if (EVENT == 185) then
	MonsterCount = CountMonsterQuestSub(UID, 988, 1);
	if (MonsterCount < 100) then
		SelectMsg(UID, 2, savenum, 244, NPC, 18, 187);
	else
		SelectMsg(UID, 4, savenum, 244, NPC, 41, 186, 27, 193);
	end
end

if (EVENT == 187) then
	ShowMap(UID, 86);
end

if (EVENT == 186) then
	Prem = GetPremium(UID);
	if (Prem > 0) then
		ExpChange(UID, 2200000)
		UpdateEvent(UID, 220);  
	else
		ExpChange(UID, 1000000)
		UpdateEvent(UID, 220); 
	end   
end

local savenum = 989;

if (EVENT == 200) then -- 60 Level Crimson Wing
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 270, NPC, 22, 201, 23, 202);
	else
		SelectMsg(UID, 2, savenum, 270, NPC, 10, 193);
	end
end

if (EVENT == 201) then
	UpdateEvent(UID, 229);
end

if (EVENT == 202) then
	UpdateEvent(UID, 232);
end

if (EVENT == 204) then
	UpdateEvent(UID, 231);
	SelectMsg(UID, 2, savenum, 270, NPC, 14, 193);
end

if (EVENT == 205) then
	MonsterCount = CountMonsterQuestSub(UID, 989, 1);
	if (MonsterCount < 250) then
		SelectMsg(UID, 2, savenum, 270, NPC, 18, 207);
	else
		SelectMsg(UID, 4, savenum, 270, NPC, 41, 206, 27, 193);
	end
end

if (EVENT == 207) then
	ShowMap(UID, 83);
end

if (EVENT == 206) then
	Prem = GetPremium(UID);
	if (Prem > 0) then
		ExpChange(UID, 2000000)
		UpdateEvent(UID, 230);  
	else
		ExpChange(UID, 1000000)
		UpdateEvent(UID, 230); 
	end   
end

local savenum = 990;

if (EVENT == 210) then -- 60 Level Apostle Piercing
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 280, NPC, 22, 211, 23, 212);
	else
		SelectMsg(UID, 2, savenum, 280, NPC, 10, 193);
	end
end

if (EVENT == 211) then
	UpdateEvent(UID, 239);
end

if (EVENT == 212) then
	UpdateEvent(UID, 242);
end

if (EVENT == 214) then
	UpdateEvent(UID, 241);
	SelectMsg(UID, 2, savenum, 280, NPC, 14, 193);
end

if (EVENT == 215) then
	MonsterCount = CountMonsterQuestSub(UID, 990, 1);
	if (MonsterCount < 120) then
		SelectMsg(UID, 2, savenum, 280, NPC, 18, 217);
	else
		SelectMsg(UID, 4, savenum, 280, NPC, 41, 216, 27, 193);
	end
end

if (EVENT == 217) then
	ShowMap(UID, 87);
end

if (EVENT == 216) then
	Prem = GetPremium(UID);
	if (Prem > 0) then
		ExpChange(UID, 1400000)
		UpdateEvent(UID, 240);  
	else
		ExpChange(UID, 600000)
		UpdateEvent(UID, 240); 
	end  
end

local savenum = 991;

if (EVENT == 220) then -- 60 Level Apostle Flame
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 8650, NPC, 22, 221, 23, 222);
	else
		SelectMsg(UID, 2, savenum, 8650, NPC, 10, 193);
	end
end

if (EVENT == 221) then
	UpdateEvent(UID, 249);
end

if (EVENT == 222) then
	UpdateEvent(UID, 252);
end

if (EVENT == 224) then
	UpdateEvent(UID, 251);
	SelectMsg(UID, 2, savenum, 8650, NPC, 14, 193);
end

if (EVENT == 225) then
	MonsterCount = CountMonsterQuestSub(UID, 991, 1);
	if (MonsterCount < 120) then
		SelectMsg(UID, 2, savenum, 8650, NPC, 18, 227);
	else
		SelectMsg(UID, 4, savenum, 8650, NPC, 41, 226, 27, 193);
	end
end

if (EVENT == 227) then
	ShowMap(UID, 88);
end

if (EVENT == 226) then
	Prem = GetPremium(UID);
	if (Prem > 0) then
		ExpChange(UID, 1400000)
		UpdateEvent(UID, 250);  
	else
		ExpChange(UID, 600000)
		UpdateEvent(UID, 250); 
	end   
end

local savenum = 986;

if (EVENT == 160) then -- 60 Level Doom Soldier
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 224, NPC, 22, 161, 23, 163);
	else
		SelectMsg(UID, 2, savenum, 224, NPC, 10, 193);
	end
end

if (EVENT == 161) then
	UpdateEvent(UID, 265);
end

if (EVENT == 163) then
	UpdateEvent(UID, 268);
end

if (EVENT == 164) then
	UpdateEvent(UID, 267);
	SelectMsg(UID, 2, savenum, 224, NPC, 14, 193);
end

if (EVENT == 165) then
	MonsterCount = CountMonsterQuestSub(UID, 986, 1);
	if (MonsterCount < 200) then
		SelectMsg(UID, 2, savenum, 224, NPC, 18, 167);
	else
		SelectMsg(UID, 4, savenum, 224, NPC, 41, 166, 27, 193);
	end
end

if (EVENT == 167) then
	ShowMap(UID, 81);
end

if (EVENT == 166) then
	Prem = GetPremium(UID);
	if (Prem > 0) then
		ExpChange(UID, 1400000)
		UpdateEvent(UID, 266);
	else
		ExpChange(UID, 600000)
		UpdateEvent(UID, 266); 
	end   
end

local savenum = 1025;

if (EVENT == 530) then -- 70 Level 100 Kill
	UpdateEvent(UID, 832);
	SelectMsg(UID, 2, savenum, 724, NPC, 4080, 193);
end

if (EVENT == 532) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 724, NPC, 22, 533, 23, 534);
	else
		SelectMsg(UID, 2, savenum, 724, NPC, 10, 193);
	end
end

if (EVENT == 533) then
	UpdateEvent(UID, 833);
end

if (EVENT == 534) then
	UpdateEvent(UID, 836);
end

if (EVENT == 535) then
	UpdateEvent(UID, 835);
	SelectMsg(UID, 2, savenum, 724, NPC, 14, 193);
end

if (EVENT == 536) then
	MonsterCount = CountMonsterQuestSub(UID, 1025, 1);
	if (MonsterCount < 100) then
		SelectMsg(UID, 2, savenum, 724, NPC, 18, 538);
	else
		SelectMsg(UID, 4, savenum, 724, NPC, 4172, 537, 4173, 193);
	end
end

if (EVENT == 538) then
	ShowMap(UID, 488);
end

if (EVENT == 537) then
	ExpChange(UID, 20000000)
	UpdateEvent(UID, 834);   
end

local savenum = 1029;

if (EVENT == 320) then -- 70 Level Ewil Wizard
	UpdateEvent(UID, 911);
end

if (EVENT == 321) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 391, NPC, 22, 322, 23, 323);
	else
		SelectMsg(UID, 2, savenum, 391, NPC, 10, 193);
	end
end

if (EVENT == 322) then
	UpdateEvent(UID, 912);
end

if (EVENT == 323) then
	UpdateEvent(UID, 915);
end

if (EVENT == 324) then
	UpdateEvent(UID, 914);
	SelectMsg(UID, 2, savenum, 391, NPC, 14, 193);
end

if (EVENT == 325) then
	MonsterCount = CountMonsterQuestSub(UID, 1029, 1);
	if (MonsterCount < 250) then
		SelectMsg(UID, 2, savenum, 391, NPC, 18, 327);
	else
		SelectMsg(UID, 4, savenum, 391, NPC, 41, 326, 27, 193);
	end
end

if (EVENT == 327) then
	ShowMap(UID, 169);
end

if (EVENT == 326) then
	ExpChange(UID, 46000000)
	UpdateEvent(UID, 913);   
end

local savenum = 1028;

if (EVENT == 310) then -- 74 Level Keramash & Manicmash & Nigmash
	UpdateEvent(UID, 899);
end

if (EVENT == 311) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 371, NPC, 22, 312, 23, 313);
	else
		SelectMsg(UID, 2, savenum, 371, NPC, 10, 193);
	end
end

if (EVENT == 312) then
	UpdateEvent(UID, 900);
end

if (EVENT == 323) then
	UpdateEvent(UID, 903);
end

if (EVENT == 314) then
	UpdateEvent(UID, 902);
	SelectMsg(UID, 2, savenum, 371, NPC, 14, 193);
end

if (EVENT == 315) then
	MonsterCount1 = CountMonsterQuestSub(UID, 1028, 1);
	MonsterCount2 = CountMonsterQuestSub(UID, 1029, 1);
	MonsterCount3 = CountMonsterQuestSub(UID, 1029, 1);
	if (MonsterCount1 < 60) then
		SelectMsg(UID, 2, savenum, 371, NPC, 18, 317);
	elseif (MonsterCount2 < 60) then
		SelectMsg(UID, 2, savenum, 371, NPC, 18, 318);
	elseif (MonsterCount3 < 60) then
		SelectMsg(UID, 2, savenum, 371, NPC, 18, 319);
	else
		SelectMsg(UID, 4, savenum, 371, NPC, 41, 316, 27, 193);
	end
end

if (EVENT == 317) then
	ShowMap(UID, 168);
end

if (EVENT == 318) then
	ShowMap(UID, 167);
end

if (EVENT == 319) then
	ShowMap(UID, 166);
end

if (EVENT == 316) then
	ExpChange(UID, 100000000)
	UpdateEvent(UID, 901);   
end

local savenum = 1027;

if (EVENT == 300) then -- 80 Level Enigma & Cruel
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		UpdateEvent(UID, 872);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		UpdateEvent(UID, 877);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		UpdateEvent(UID, 882);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		UpdateEvent(UID, 887);
	end
end

if (EVENT == 302) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, savenum, 351, NPC, 22, 303, 23, 304);
	else
		SelectMsg(UID, 2, savenum, 351, NPC, 10, 193);
	end
end

if (EVENT == 303) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		UpdateEvent(UID, 873);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		UpdateEvent(UID, 878);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		UpdateEvent(UID, 883);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		UpdateEvent(UID, 888);
	end
end

if (EVENT == 304) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		UpdateEvent(UID, 876);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		UpdateEvent(UID, 881);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		UpdateEvent(UID, 886);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		UpdateEvent(UID, 891);
	end
end

if (EVENT == 305) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		UpdateEvent(UID, 875);
		SelectMsg(UID, 2, savenum, 351, NPC, 14, 193);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		UpdateEvent(UID, 880);
		SelectMsg(UID, 2, savenum, 351, NPC, 14, 193);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		UpdateEvent(UID, 885);
		SelectMsg(UID, 2, savenum, 351, NPC, 14, 193);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		UpdateEvent(UID, 890);
		SelectMsg(UID, 2, savenum, 351, NPC, 14, 193);
	end
end

if (EVENT == 307) then
	MonsterCount1 = CountMonsterQuestSub(UID, 1027, 1);
	MonsterCount2 = CountMonsterQuestSub(UID, 1027, 2);
	if (MonsterCount1 < 1) then
		SelectMsg(UID, 2, savenum, 351, NPC, 18, 306);
	elseif (MonsterCount2 < 1) then
		SelectMsg(UID, 2, savenum, 351, NPC, 18, 309);
	else
		SelectMsg(UID, 4, savenum, 351, NPC, 41, 308, 27, 193);
	end
end

if (EVENT == 306) then
	ShowMap(UID, 165);
end

if (EVENT == 309) then
	ShowMap(UID, 163);
end

if (EVENT == 308) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		GiveItem(UID, 910120350, 1)
		GiveItem(UID, 910121300, 1)
		GiveItem(UID, 910126544, 1)
		UpdateEvent(UID, 874);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		GiveItem(UID, 910119300, 1)
		GiveItem(UID, 910122350, 1)
		UpdateEvent(UID, 879);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		GiveItem(UID, 910123355, 1)
		GiveItem(UID, 910124351, 1)
		UpdateEvent(UID, 884);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		GiveItem(UID, 910125324, 1)
		GiveItem(UID, 910126544, 1)
		UpdateEvent(UID, 889);
	end  
end