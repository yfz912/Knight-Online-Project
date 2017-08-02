local Ret = 0;
local NPC = 13013;

if (EVENT == 165) then
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 166, NPC, 10, 168);
	elseif (QuestNum > 1 and QuestNum < 100) then
		NpcMsg(UID, 167, NPC);
	else
		EVENT = QuestNum
	end
end

if (EVENT == 168) then
	Ret = 1;
end

if (EVENT == 170) then -- 1 Level Hunt Worm
	SelectMsg(UID, 2, 60, 170, NPC, 24, 171);
end

if (EVENT == 171) then
	ShowMap(UID, 4);
	UpdateEvent(UID, 48);
end

if (EVENT == 172) then
	SelectMsg(UID, 2, 60, 172, NPC, 24, 171);
end

if (EVENT == 175) then
	SelectMsg(UID, 2, 60, 175, NPC,  25, 176, 13, 168);
end

if (EVENT == 176) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub < 5) then -- need change th
		SelectMsg(UID, 4, 60, 176, NPC, 22, 178, 23, 168);
	else
		SelectMsg(UID, 2, 60, 173, NPC, 10, 168);
	end
end

if (EVENT == 178) then
	UpdateEvent(UID, 49);
end

if (EVENT == 180) then
	UpdateEvent(UID, 51);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 60, 181, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 60, 182, NPC, 14, 168);
	end
end

if (EVENT == 185) then
	MonsterCount = CountMonsterQuestSub(UID, 60, 1);
	if (MonsterCount < 5) then
		SelectMsg(UID, 2, 60, 186, NPC, 10, 188);
	else
		SelectMsg(UID, 4, 60, 187, NPC, 10, 187, 27, 168);
	end
end

if (EVENT == 188) then
	ShowMap(UID, 1);
end

if (EVENT == 187) then
	UpdateEvent(UID, 50);
end

if (EVENT == 220) then -- 3 Level Hunt Bandicoot
	SelectMsg(UID, 2, 62, 220, NPC, 24, 221, 14, 222);
end

if (EVENT == 221) then
	ShowMap(UID, 4);
	UpdateEvent(UID, 63);
end

if (EVENT == 222) then
	UpdateEvent(UID, 63);
end

if (EVENT == 223) then
	SelectMsg(UID, 2, 62, 223, NPC, 24, 221, 14, 222);
end

if (EVENT == 225) then
	SelectMsg(UID, 2, 62, 225, NPC,  33, 226);
end
--SeventDataIndex
if (EVENT == 226) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 62, 228, NPC, 22, 229, 23, 168);
	else
		SelectMsg(UID, 2, 62, 173, NPC, 10, 168);
	end
end

if (EVENT == 229) then
	UpdateEvent(UID, 64);
end

if (EVENT == 231) then
	UpdateEvent(UID, 66);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 62, 232, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 62, 233, NPC, 14, 168);
	end
end

if (EVENT == 235) then
	MonsterCount = CountMonsterQuestSub(UID, 62, 1);
	if (MonsterCount < 5) then
		SelectMsg(UID, 2, 62, 237, NPC, 18, 239);
	else
		SelectMsg(UID, 4, 62, 236, NPC, 10, 238, 27, 168);
	end
end

if (EVENT == 239) then
	ShowMap(UID, 7);
end

if (EVENT == 238) then
	ExpChange (UID, 150)
	GoldGain(UID, 700)  
	UpdateEvent(UID, 65);   
end

if (EVENT == 370) then -- 6 Level Hunt Kekoon
	SelectMsg(UID, 2, 65, 3150, NPC, 24, 371);
end

if (EVENT == 371) then
	ShowMap(UID, 4);
	UpdateEvent(UID, 3322);
end

if (EVENT == 372) then
	SelectMsg(UID, 2, 65, 3151, NPC, 24, 371);
end

if (EVENT == 300) then
	SelectMsg(UID, 2, 65, 3152, NPC, 3012, 301, 13, 168);
end

if (EVENT == 301) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub >= 0) then
		SelectMsg(UID, 4, 65, 3153, NPC, 22, 302, 23, 308);
	else
		SelectMsg(UID, 2, 65, 173, NPC, 10, 168);
	end
end

if (EVENT == 308) then
	SelectMsg(UID, 2, 65, 3155, NPC, 10, 168);
end

if (EVENT == 302) then
	UpdateEvent(UID, 3323);
	SelectMsg(UID, 2, 65, 3154, NPC, 10, 168);
end

if (EVENT == 303) then
	UpdateEvent(UID, 3325);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 65, 3157, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 65, 3158, NPC, 14, 168);
	end
end

if (EVENT == 305) then
--	MonsterCount = CountMonsterQuestSub(UID, 65, 1);
--	if (MonsterCount < 5) then
--		SelectMsg(UID, 2, 65, 3156, NPC, 10, 306);
--	else
		SelectMsg(UID, 4, 65, 3159, NPC, 10, 309, 27, 306);
--	end
end

if (EVENT == 306) then
	ShowMap(UID, 11);
end

if (EVENT == 309) then
	ExpChange(UID, 750) 
	UpdateEvent(UID, 3324);
end

if (EVENT == 470) then -- 8 Level Hunt Bulcan
	SelectMsg(UID, 2, 67, 170, NPC, 24, 471);
end

if (EVENT == 471) then
	ShowMap(UID, 4);
	UpdateEvent(UID, 3332);
end

if (EVENT == 472) then
	SelectMsg(UID, 2, 67, 172, NPC, 24, 471);
end

if (EVENT == 400) then
	SelectMsg(UID, 2, 67, 3160, NPC,  3012, 401, 13, 168);
end

if (EVENT == 401) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 67, 3161, NPC, 22, 402, 23, 408);
	else
		SelectMsg(UID, 2, 67, 173, NPC, 10, 168);
	end
end

if (EVENT == 408) then
	SelectMsg(UID, 2, 67, 3163, NPC, 10, 168);
end

if (EVENT == 402) then
	UpdateEvent(UID, 3333);
	SelectMsg(UID, 2, 67, 3162, NPC, 10, 168);
end

if (EVENT == 403) then
	UpdateEvent(UID, 3335);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 1, 67, 3165, NPC, 14, 168);
	else
		SelectMsg(UID, 1, 67, 3166, NPC, 14, 168);
	end
end

if (EVENT == 405) then
	MonsterCount = CountMonsterQuestSub(UID, 67, 1);
	if (MonsterCount < 5) then
		SelectMsg(UID, 2, 67, 3164, NPC, 10, 406);
	else
		SelectMsg(UID, 4, 67, 3167, NPC, 10, 409, 27, 168);
	end
end

if (EVENT == 406) then
	ShowMap(UID, 34);
end

if (EVENT == 409) then
	UpdateEvent(UID, 3334);
end

if (EVENT == 570) then -- 9 Level Hunt Wild Bulcan
	SelectMsg(UID, 2, 70, 170, NPC, 24, 571);
end

if (EVENT == 571) then
	ShowMap(UID, 4);
	UpdateEvent(UID, 3342);
end

if (EVENT == 572) then
	SelectMsg(UID, 2, 70, 172, NPC, 24, 571);
end

if (EVENT == 500) then
	SelectMsg(UID, 2, 70, 3168, NPC,  3012, 501, 13, 168);
end

if (EVENT == 501) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub >= 0) then
		SelectMsg(UID, 4, 70, 3169, NPC, 22, 502, 23, 508);
	else
		SelectMsg(UID, 2, 70, 173, NPC, 10, 168);
	end
end

if (EVENT == 508) then
	SelectMsg(UID, 2, 70, 3171, NPC, 10, 168);
end

if (EVENT == 502) then
	SelectMsg(UID, 2, 70, 3170, NPC, 10, 168);
	UpdateEvent(UID, 3343);
end

if (EVENT == 503) then
	UpdateEvent(UID, 3345);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 70, 3173, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 70, 3174, NPC, 14, 168);
	end
end

if (EVENT == 505) then
	MonsterCount = CountMonsterQuestSub(UID, 70, 1);
	if (MonsterCount < 5) then
		SelectMsg(UID, 2, 70, 3172, NPC, 10, 506);
	else
		SelectMsg(UID, 4, 70, 3175, NPC, 10, 509, 27, 506);
	end
end

if (EVENT == 506) then
	ShowMap(UID, 325);
end

if (EVENT == 509) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		ExpChange(UID, 1800) 
		GiveItem(UID, 202005005, 1)
		UpdateEvent(UID, 3344);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		ExpChange(UID, 1800) 
		GiveItem(UID, 242005005, 1)
		UpdateEvent(UID, 3344);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		ExpChange(UID, 1800) 
		GiveItem(UID, 262005005, 1)
		UpdateEvent(UID, 3344);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		ExpChange(UID, 1800) 
		GiveItem(UID, 282005005, 1)
		UpdateEvent(UID, 3344);
	end
end

if (EVENT == 670) then -- 10 Level Hunt Kekoon Warrior
	SelectMsg(UID, 2, 80, 3176, NPC, 3013, 671);
end

if (EVENT == 671) then
	UpdateEvent(UID, 3352);
	SelectMsg(UID, 2, 80, 3182, NPC, 10, 168);
end

if (EVENT == 672) then
	SelectMsg(UID, 2, 80, 3177, NPC, 24, 671);
end

if (EVENT == 600) then
	SelectMsg(UID, 2, 80, 3193, NPC, 3017, 601);
end

if (EVENT == 601) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 80, 3195, NPC, 3018, 602, 3019, 608);
	else
		SelectMsg(UID, 2, 80, 3197, NPC, 3001, 168);
	end
end

if (EVENT == 608) then
	SelectMsg(UID, 2, 80, 3197, NPC, 10, 168);
end

if (EVENT == 602) then
	SelectMsg(UID, 2, 80, 3193, NPC, 10, 168);
	UpdateEvent(UID, 3353);
end

if (EVENT == 603) then
	UpdateEvent(UID, 3355);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 80, 3187, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 80, 3188, NPC, 14, 168);
	end
end

if (EVENT == 605) then
	MonsterCount = CountMonsterQuestSub(UID, 80, 1);
	if (MonsterCount < 5) then
		SelectMsg(UID, 2, 80, 3197, NPC, 10, 606);
	else
		SelectMsg(UID, 4, 80, 3189, NPC, 10, 609, 27, 168);
	end
end

if (EVENT == 606) then
	ShowMap(UID, 326);
end

if (EVENT == 609) then
	UpdateEvent(UID, 3354);
	SelectMsg(UID, 2, 80, 3190, NPC, 10, 168); 
end

if (EVENT == 770) then -- 11 Level Hunt Gavolt
	SelectMsg(UID, 2, 83, 3798, NPC, 10, 771);
end

if (EVENT == 771) then
	ShowMap(UID, 4);
	UpdateEvent(UID, 3362);
end

if (EVENT == 772) then
	SelectMsg(UID, 2, 83, 3799, NPC, 10, 771);
end

if (EVENT == 700) then
	SelectMsg(UID, 2, 83, 3800, NPC,  3012, 701, 13, 168);
end

if (EVENT == 701) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 83, 3801, NPC, 22, 702, 23, 708);
	else
		SelectMsg(UID, 2, 83, 173, NPC, 10, 168);
	end
end

if (EVENT == 708) then
	SelectMsg(UID, 2, 83, 3803, NPC, 10, 168);
end

if (EVENT == 702) then
	SelectMsg(UID, 2, 83, 3802, NPC, 10, 168);
	UpdateEvent(UID, 3363);
end

if (EVENT == 703) then
	UpdateEvent(UID, 3365);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 83, 3805, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 83, 3806, NPC, 14, 168);
	end
end

if (EVENT == 705) then
	MonsterCount = CountMonsterQuestSub(UID, 83, 1);
	if (MonsterCount < 5) then
		SelectMsg(UID, 2, 83, 3804, NPC, 10, 706);
	else
		SelectMsg(UID, 4, 83, 3807, NPC, 10, 709, 27, 706);
	end
end

if (EVENT == 706) then
	ShowMap(UID, 12);
end

if (EVENT == 709) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		UpdateEvent(UID, 3364);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		UpdateEvent(UID, 3364);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		UpdateEvent(UID, 3364);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		UpdateEvent(UID, 3364);
	end
end

if (EVENT == 9200) then -- 13 Level Hunt Kekoon Captain
	SelectMsg(UID, 2, 85, 175, NPC, 10, 9201);
end

if (EVENT == 9201) then
	UpdateEvent(UID, 5274);
end

if (EVENT == 9202) then
	SelectMsg(UID, 2, 85, 175, NPC, 10, 9201);
end

if (EVENT == 9205) then
	SelectMsg(UID, 2, 85, 175, NPC,  25, 9206, 13, 168);
end

local MonsterSub = 0;

if (EVENT == 9206) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub >= 0) then
		SelectMsg(UID, 4, 85, 8667, NPC, 22, 9207, 23, 168);
	else
		SelectMsg(UID, 2, 85, 8667, NPC, 10, 168);
	end
end

if (EVENT == 9207) then
	UpdateEvent(UID, 5275);
end

if (EVENT == 9215) then
	MonsterCount = CountMonsterQuestSub(UID, 85, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, 85, 8667, NPC, 10, 9216);
	else
		SelectMsg(UID, 4, 85, 8667, NPC, 10, 9217, 27, 168);
	end
end

if (EVENT == 9216) then
	ShowMap(UID, 54);
end

if (EVENT == 9217) then
	ExpChange(UID, 4500)
	GoldGain(UID, 50000)
	UpdateEvent(UID, 5276);
end

if (EVENT == 870) then -- 14 Level Hunt Bulture
	SelectMsg(UID, 2, 86, 170, NPC, 24, 871);
end

if (EVENT == 871) then
	ShowMap(UID, 4);
	UpdateEvent(UID, 3372);
end

if (EVENT == 872) then
	SelectMsg(UID, 2, 86, 172, NPC, 24, 871);
end

if (EVENT == 800) then
	SelectMsg(UID, 2, 86, 3808, NPC,  3012, 801, 13, 168);
end

if (EVENT == 801) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 86, 3809, NPC, 22, 802, 23, 808);
	else
		SelectMsg(UID, 2, 86, 173, NPC, 10, 168);
	end
end

if (EVENT == 808) then
	SelectMsg(UID, 2, 86, 3811, NPC, 10, 168);
end

if (EVENT == 802) then
	SelectMsg(UID, 2, 86, 3810, NPC, 10, 168);
	UpdateEvent(UID, 3373);
end

if (EVENT == 803) then
	UpdateEvent(UID, 3375);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 86, 3813, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 86, 3814, NPC, 14, 168);
	end
end

if (EVENT == 805) then
	MonsterCount = CountMonsterQuestSub(UID, 86, 1);
	if (MonsterCount < 15) then
		SelectMsg(UID, 2, 86, 3812, NPC, 10, 806);
	else
		SelectMsg(UID, 4, 86, 3815, NPC, 10, 809, 27, 806);
	end
end

if (EVENT == 806) then
	ShowMap(UID, 38);
end

if (EVENT == 809) then
	ExpChange(UID, 5500)
	UpdateEvent(UID, 3374);
end

if (EVENT == 9220) then -- 15 Level Hunt Giant Bulcan
	SelectMsg(UID, 2, 87, 170, NPC, 10, 9221);
end

if (EVENT == 9221) then
	UpdateEvent(UID, 5281);
end

if (EVENT == 9222) then
	SelectMsg(UID, 2, 87, 172, NPC, 10, 9221);
end

if (EVENT == 9225) then
	SelectMsg(UID, 2, 87, 3168, NPC, 10, 9226);
end

if (EVENT == 9226) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 87, 3169, NPC, 22, 9227, 23, 168);
	else
		SelectMsg(UID, 2, 87, 173, NPC, 10, 168);
	end
end

if (EVENT == 9227) then
	SelectMsg(UID, 2, 87, 3170, NPC, 14, 168);
	UpdateEvent(UID, 5282);
end

if (EVENT == 9230) then
	UpdateEvent(UID, 5284);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 87, 3173, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 87, 3174, NPC, 14, 168);
	end
end

if (EVENT == 9235) then
	MonsterCount = CountMonsterQuestSub(UID, 87, 1);
	if (MonsterCount < 25) then
		SelectMsg(UID, 2, 87, 3172, NPC, 10, 9236);
	else
		SelectMsg(UID, 4, 87, 3175, NPC, 10, 9239, 27, 9236);
	end 
end

if (EVENT == 9236) then
	ShowMap(UID, 593);
end

if (EVENT == 9239) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		ExpChange(UID, 6000) 
		GiveItem(UID, 202004005, 1)
		UpdateEvent(UID, 5283);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		ExpChange(UID, 6000) 
		GiveItem(UID, 242004005, 1)
		UpdateEvent(UID, 5283);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		ExpChange(UID, 6000) 
		GiveItem(UID, 262004005, 1)
		UpdateEvent(UID, 5283);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		ExpChange(UID, 6000) 
		GiveItem(UID, 282004005, 1)
		UpdateEvent(UID, 5283);
	end
end

if (EVENT == 1070) then -- 16 Level Hunt Werewolf
	SelectMsg(UID, 2, 90, 3827, NPC, 3005, 1071);
end

if (EVENT == 1071) then
	ShowMap(UID, 4);
	UpdateEvent(UID, 3392);
end

if (EVENT == 1072) then
	SelectMsg(UID, 2, 90, 3828, NPC, 3005, 1071);
end

if (EVENT == 1000) then
	SelectMsg(UID, 2, 90, 3835, NPC,  3012, 1001, 13, 168);
end

if (EVENT == 1001) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub >= 0) then
		SelectMsg(UID, 4, 90, 3836, NPC, 22, 1002, 23, 1008);
	else
		SelectMsg(UID, 2, 90, 173, NPC, 10, 168);
	end
end

if (EVENT == 1002) then
	SelectMsg(UID, 2, 90, 3838, NPC, 10, 168);
	UpdateEvent(UID, 3393);
end

if (EVENT == 1008) then
	SelectMsg(UID, 2, 90, 3839, NPC, 10, 168);
end

if (EVENT == 1003) then
	UpdateEvent(UID, 3395);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 90, 3841, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 90, 3842, NPC, 14, 168);
	end
end

if (EVENT == 1005) then
	MonsterCount = CountMonsterQuestSub(UID, 90, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, 90, 3840, NPC, 10, 1006);
	else
		SelectMsg(UID, 4, 90, 3843, NPC, 10, 1009, 27, 1006);
	end
end

if (EVENT == 1006) then
	ShowMap(UID, 629);
end

if (EVENT == 1009) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		ExpChange(UID, 6000) 
		GiveItem(UID, 202005006, 1)
		UpdateEvent(UID, 3394);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		ExpChange(UID, 6000) 
		GiveItem(UID, 242005006, 1)
		UpdateEvent(UID, 3394);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		ExpChange(UID, 6000) 
		GiveItem(UID, 262005006, 1)
		UpdateEvent(UID, 3394);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		ExpChange(UID, 6000) 
		GiveItem(UID, 282005006, 1)
		UpdateEvent(UID, 3394);
	end
end

if (EVENT == 970) then -- 18 Level Hunt Silan
	SelectMsg(UID, 2, 92, 170, NPC, 24, 971);
end

if (EVENT == 971) then
	ShowMap(UID, 4);
	UpdateEvent(UID, 3382);
end

if (EVENT == 972) then
	SelectMsg(UID, 2, 92, 172, NPC, 24, 971);
end

if (EVENT == 900) then
	SelectMsg(UID, 2, 92, 3816, NPC,  3012, 901, 13, 168);
end

if (EVENT == 901) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 92, 3817, NPC, 22, 902, 23, 908);
	else
		SelectMsg(UID, 2, 92, 173, NPC, 10, 168);
	end
end

if (EVENT == 902) then
	SelectMsg(UID, 2, 92, 3818, NPC, 10, 168);
	UpdateEvent(UID, 3383);
end

if (EVENT == 908) then
	SelectMsg(UID, 2, 92, 3819, NPC, 10, 168);
end

if (EVENT == 903) then
	UpdateEvent(UID, 3385);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 92, 3821, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 92, 3822, NPC, 14, 168);
	end
end

if (EVENT == 905) then
	MonsterCount = CountMonsterQuestSub(UID, 92, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, 92, 3820, NPC, 10, 906);
	else
		SelectMsg(UID, 4, 92, 3823, NPC, 10, 909, 27, 906);
	end
end

if (EVENT == 906) then
	ShowMap(UID, 60);
end

if (EVENT == 909) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		ExpChange(UID, 7000) 
		GoldGain(UID, 150000)
		GiveItem(UID, 202003006, 1)
		UpdateEvent(UID, 3384);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		ExpChange(UID, 7000) 
		GoldGain(UID, 150000)
		GiveItem(UID, 242003006, 1)
		UpdateEvent(UID, 3384);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		ExpChange(UID, 7000) 
		GoldGain(UID, 150000)
		GiveItem(UID, 262003006, 1)
		UpdateEvent(UID, 3384);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		ExpChange(UID, 7000) 
		GoldGain(UID, 150000)
		GiveItem(UID, 282003006, 1)
		UpdateEvent(UID, 3384);
	end
end

if (EVENT == 9240) then -- 19 Level Hunt Giant Gavolt
	SelectMsg(UID, 2, 96, 3798, NPC, 10, 9241);
end

if (EVENT == 9241) then
	UpdateEvent(UID, 5288);
end

if (EVENT == 9242) then
	SelectMsg(UID, 2, 96, 3799, NPC, 10, 9241);
end

if (EVENT == 9245) then
	SelectMsg(UID, 2, 96, 3800, NPC, 10, 9246);
end

if (EVENT == 9246) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 96, 3801, NPC, 22, 9247, 23, 168);
	else
		SelectMsg(UID, 2, 96, 173, NPC, 10, 168);
	end
end

if (EVENT == 9247) then
	SelectMsg(UID, 2, 96, 3802, NPC, 14, 168);
	UpdateEvent(UID, 5289);
end

if (EVENT == 9250) then
	UpdateEvent(UID, 5291);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 96, 3805, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 96, 3806, NPC, 14, 168);
	end
end

if (EVENT == 9255) then
	MonsterCount = CountMonsterQuestSub(UID, 96, 1);
	if (MonsterCount < 25) then
		SelectMsg(UID, 2, 96, 3804, NPC, 10, 9256);
	else
		SelectMsg(UID, 4, 96, 3807, NPC, 10, 9259, 27, 9256);
	end 
end

if (EVENT == 9256) then
	ShowMap(UID, 594);
end

if (EVENT == 9259) then
	ExpChange(UID, 19000)
	UpdateEvent(UID, 5290);
end

if (EVENT == 9431) then -- 20 Level Wolf Hide 
	SelectMsg(UID, 2, 97, 3798, NPC, 10, 9432);
end

if (EVENT == 9432) then
	UpdateEvent(UID, 5295);
end

if (EVENT == 9433) then
	SelectMsg(UID, 2, 97, 3799, NPC, 10, 9432);
end

if (EVENT == 9434) then
	SelectMsg(UID, 2, 97, 8671, NPC, 10, 9435);
end

if (EVENT == 9435) then
	SelectMsg(UID, 4, 97, 8672, NPC, 22, 9436, 23, 168);
end

if (EVENT == 9436) then
	SelectMsg(UID, 2, 97, 3802, NPC, 14, 168);
	UpdateEvent(UID, 5296);
end

if (EVENT == 9437) then
	UpdateEvent(UID, 5298);
	NATION = CheckNation(UID);
	if (NATION == 1) then
		SelectMsg(UID, 2, 97, 8671, NPC, 14, 168);
	else
		SelectMsg(UID, 2, 97, 8672, NPC, 14, 168);
	end
end

if (EVENT == 9439) then
	ITEMWH = HowmuchItem(UID, 379254000);
	if (ITEMWH < 15) then
		SelectMsg(UID, 2, 97, 8671, NPC, 10, 9440);
	else
		SelectMsg(UID, 4, 97, 8672, NPC, 10, 9441, 27, 9440);
	end 
end

if (EVENT == 9440) then
	ShowMap(UID, 523);
end

if (EVENT == 9441) then
	RobItem(UID, 379254000, 15)
	ExpChange(UID, 30000)
	UpdateEvent(UID, 5297);
end

if (EVENT == 9260) then -- 21 Level Hunt Glyptodont
	SelectMsg(UID, 2, 98, 3168, NPC, 10, 9261);
end

if (EVENT == 9261) then
	UpdateEvent(UID, 5302);
end

if (EVENT == 9262) then
	SelectMsg(UID, 2, 98, 3168, NPC, 10, 9261);
end   

if (EVENT == 9265) then
	SelectMsg(UID, 2, 98, 3168, NPC,  3012, 9266, 13, 168);
end

if (EVENT == 9266) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 98, 3169, NPC, 22, 9267, 23, 9268);
	else
		SelectMsg(UID, 2, 98, 173, NPC, 10, 168);
	end
end

if (EVENT == 9267) then
	SelectMsg(UID, 2, 98, 3170, NPC, 10, 168);
	UpdateEvent(UID, 5303);
end

if (EVENT == 9268) then
	SelectMsg(UID, 2, 98, 3171, NPC, 10, 168);
end

if (EVENT == 9270) then
	UpdateEvent(UID, 5305);
	SelectMsg(UID, 2, 98, 3190, NPC, 14, 168);
end

if (EVENT == 9275) then
	MonsterCount = CountMonsterQuestSub(UID, 98, 1);
	if (MonsterCount < 1) then
		SelectMsg(UID, 2, 98, 173, NPC, 10, 9276);
	else
		SelectMsg(UID, 4, 98, 3169, NPC, 10, 9277, 27, 9276);
	end
end

if (EVENT == 9276) then
	ShowMap(UID, 595);
end

if (EVENT == 9277) then
	ExpChange(UID, 20000)
	UpdateEvent(UID, 5304);
end

if (EVENT == 9280) then -- 22 Level Hunt Gloomwing
	SelectMsg(UID, 2, 99, 3168, NPC, 10, 9281);
end

if (EVENT == 9281) then
	UpdateEvent(UID, 5309);
end

if (EVENT == 9282) then
	SelectMsg(UID, 2, 99, 3168, NPC, 10, 9281);
end   

if (EVENT == 9285) then
	SelectMsg(UID, 2, 99, 3800, NPC,  3012, 9286, 13, 168);
end

if (EVENT == 9286) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub == 0) then
		SelectMsg(UID, 4, 99, 3801, NPC, 22, 9287, 23, 9288);
	else
		SelectMsg(UID, 2, 99, 173, NPC, 10, 168);
	end
end

if (EVENT == 9287) then
	SelectMsg(UID, 2, 99, 3802, NPC, 10, 168);
	UpdateEvent(UID, 5310);
end

if (EVENT == 9288) then
	SelectMsg(UID, 2, 99, 3803, NPC, 10, 168);
end

if (EVENT == 9290) then
	UpdateEvent(UID, 5312);
	SelectMsg(UID, 2, 99, 3805, NPC, 14, 168);
end

if (EVENT == 9295) then
	MonsterCount = CountMonsterQuestSub(UID, 99, 1);
	if (MonsterCount < 30) then
		SelectMsg(UID, 2, 99, 3804, NPC, 10, 9296);
	else
		SelectMsg(UID, 4, 99, 3815, NPC, 10, 9297, 27, 9296);
	end
end

if (EVENT == 9296) then
	ShowMap(UID, 596);
end

if (EVENT == 9297) then
	ExpChange(UID, 50000)
	--GiveItem(UID, )
	UpdateEvent(UID, 5311);
end

local savenum = 111;

if (EVENT == 8630) then -- 23 Level Hunt Orch Watcher
	SelectMsg(UID, 2, savenum, 8090, NPC, 10, 8631);
end

if (EVENT == 8631) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		UpdateEvent(UID, 8145);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		UpdateEvent(UID, 8150);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		UpdateEvent(UID, 8155);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		UpdateEvent(UID, 8160);
	end
end

if (EVENT == 8632) then
	MonsterSub = ExistMonsterQuestSub(UID);
	if (MonsterSub < 5) then -- th
		SelectMsg(UID, 4, savenum, 8090, NPC, 22, 8633, 23, 8634);
	else
		SelectMsg(UID, 2, savenum, 8090, NPC, 10, 168);
	end
end

if (EVENT == 8633) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		UpdateEvent(UID, 8146);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		UpdateEvent(UID, 8151);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		UpdateEvent(UID, 8156);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		UpdateEvent(UID, 8161);
	end
end

if (EVENT == 8634) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		UpdateEvent(UID, 8149);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		UpdateEvent(UID, 8154);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		UpdateEvent(UID, 8159);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		UpdateEvent(UID, 8164);
	end
end

if (EVENT == 8640) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		UpdateEvent(UID, 8148);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		UpdateEvent(UID, 8153);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		UpdateEvent(UID, 8158);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		UpdateEvent(UID, 8163);
	end
end

if (EVENT == 8636) then
	MonsterCount = CountMonsterQuestSub(UID, 111, 1);
	if (MonsterCount < 25) then
		SelectMsg(UID, 2, savenum, 8090, NPC, 21, 8637);
	else
		SelectMsg(UID, 4, savenum, 8090, NPC, 41, 8638, 23, 168);
	end
end

if (EVENT == 8637) then
	ShowMap(UID, 597);
end

if (EVENT == 8638) then
	Class = CheckClass(UID);
	if (Class == 1 or Class == 5 or Class == 6) then
		ExpChange(UID, 60000)
		GiveItem(UID, 971910732, 1)
		GiveItem(UID, 971920820, 1)
		GiveItem(UID, 971880792, 1)
		UpdateEvent(UID, 8147);
	elseif (Class == 2 or Class == 7 or Class == 8) then
		ExpChange(UID, 60000)
		GiveItem(UID, 971890916, 1)
		GiveItem(UID, 971850494, 1)
		GiveItem(UID, 971850494, 1)
		UpdateEvent(UID, 8152);
	elseif (Class == 3 or Class == 9 or Class == 10) then
		ExpChange(UID, 60000)
		GiveItem(UID, 971860356, 1)
		GiveItem(UID, 971860364, 1)
		GiveItem(UID, 971860372, 1)
		UpdateEvent(UID, 8157);
	elseif (Class == 4 or Class == 11 or Class == 12) then
		ExpChange(UID, 60000)
		GiveItem(UID, 971870764, 1)
		GiveItem(UID, 971900445, 1)
		GiveItem(UID, 971930764, 1)
		UpdateEvent(UID, 8162);
	end
end