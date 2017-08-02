local Ret = 0;
local NPC = 18010;

if (EVENT == 100) then
	QuestNum = SearchQuest(UID, NPC);
	if (QuestNum == 0) then
		SelectMsg(UID, 2, -1, 9727, NPC, 10, 101);
	elseif (QuestNum > 1 and  QuestNum < 100) then
		NpcMsg(UID, 9727, NPC)
	else
		EVENT = QuestNum
	end
end

if (EVENT == 101) then
	Ret = 1;
end

local savenum = 8000;

if (EVENT == 1000) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 1005);
end

if (EVENT == 1005) then
	SelectMsg(UID, 4, savenum, 9710, NPC, 22, 1001, 23, 1002);
end

if (EVENT == 1001) then
	SaveEvent(UID, 2805);
end

if (EVENT == 1002) then
	SaveEvent(UID, 2804);
end

if (EVENT == 1003) then
	SaveEvent(UID, 2807);
end

if (EVENT == 1004) then
	MonsterCount = CountMonsterQuestSub(UID, 8000, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 1006, 3008, 101);
	end
end

if (EVENT == 1006) then
	SaveEvent(UID, 2806);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8001;

if (EVENT == 1100) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 1105);
end

if (EVENT == 1105) then
	SelectMsg(UID, 4, savenum, 9711, NPC, 22, 1101, 23, 1102);
end

if (EVENT == 1101) then
	SaveEvent(UID, 2810);
end

if (EVENT == 1102) then
	SaveEvent(UID, 2809);
end

if (EVENT == 1103) then
	SaveEvent(UID, 2812);
end

if (EVENT == 1104) then
	MonsterCount = CountMonsterQuestSub(UID, 8001, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 1106, 3008, 101);
	end
end

if (EVENT == 1106) then
	SaveEvent(UID, 2811);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8002;

if (EVENT == 1200) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 1105);
end

if (EVENT == 1205) then
	SelectMsg(UID, 4, savenum, 9712, NPC, 22, 1201, 23, 1202);
end

if (EVENT == 1201) then
	SaveEvent(UID, 2815);
end

if (EVENT == 1202) then
	SaveEvent(UID, 2814);
end

if (EVENT == 1203) then
	SaveEvent(UID, 2817);
end

if (EVENT == 1204) then
	MonsterCount = CountMonsterQuestSub(UID, 8002, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 1206, 3008, 101);
	end
end

if (EVENT == 1206) then
	SaveEvent(UID, 2816);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8003;

if (EVENT == 1300) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 1305);
end

if (EVENT == 1305) then
	SelectMsg(UID, 4, savenum, 9713, NPC, 22, 1301, 23, 1302);
end

if (EVENT == 1301) then
	SaveEvent(UID, 2820);
end

if (EVENT == 1302) then
	SaveEvent(UID, 2819);
end

if (EVENT == 1303) then
	SaveEvent(UID, 2822);
end

if (EVENT == 1304) then
	MonsterCount = CountMonsterQuestSub(UID, 8003, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 1306, 3008, 101);
	end
end

if (EVENT == 1306) then
	SaveEvent(UID, 2821);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8004;

if (EVENT == 1400) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 1405);
end

if (EVENT == 1405) then
	SelectMsg(UID, 4, savenum, 9714, NPC, 22, 1401, 23, 1402);
end

if (EVENT == 1401) then
	SaveEvent(UID, 2825);
end

if (EVENT == 1402) then
	SaveEvent(UID, 2824);
end

if (EVENT == 1403) then
	SaveEvent(UID, 2827);
end

if (EVENT == 1404) then
	MonsterCount = CountMonsterQuestSub(UID, 8004, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 1406, 3008, 101);
	end
end

if (EVENT == 1406) then
	SaveEvent(UID, 2826);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8005;

if (EVENT == 1500) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 1505);
end

if (EVENT == 1505) then
	SelectMsg(UID, 4, savenum, 9715, NPC, 22, 1501, 23, 1502);
end

if (EVENT == 1501) then
	SaveEvent(UID, 2830);
end

if (EVENT == 1502) then
	SaveEvent(UID, 2829);
end

if (EVENT == 1503) then
	SaveEvent(UID, 2832);
end

if (EVENT == 1504) then
	MonsterCount = CountMonsterQuestSub(UID, 8005, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 1506, 3008, 101);
	end
end

if (EVENT == 1506) then
	SaveEvent(UID, 2831);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8006;

if (EVENT == 1600) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 1605);
end

if (EVENT == 1605) then
	SelectMsg(UID, 4, savenum, 9716, NPC, 22, 1601, 23, 1602);
end

if (EVENT == 1601) then
	SaveEvent(UID, 2835);
end

if (EVENT == 1602) then
	SaveEvent(UID, 2834);
end

if (EVENT == 1603) then
	SaveEvent(UID, 2837);
end

if (EVENT == 1604) then
	MonsterCount = CountMonsterQuestSub(UID, 8006, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 1606, 3008, 101);
	end
end

if (EVENT == 1606) then
	SaveEvent(UID, 2836);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8007;

if (EVENT == 1700) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 1705);
end

if (EVENT == 1705) then
	SelectMsg(UID, 4, savenum, 9717, NPC, 22, 1701, 23, 1702);
end

if (EVENT == 1701) then
	SaveEvent(UID, 2840);
end

if (EVENT == 1702) then
	SaveEvent(UID, 2839);
end

if (EVENT == 1703) then
	SaveEvent(UID, 2842);
end

if (EVENT == 1704) then
	MonsterCount = CountMonsterQuestSub(UID, 8007, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 1706, 3008, 101);
	end
end

if (EVENT == 1706) then
	SaveEvent(UID, 2841);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8008;

if (EVENT == 1800) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 1805);
end

if (EVENT == 1805) then
	SelectMsg(UID, 4, savenum, 9718, NPC, 22, 1801, 23, 1802);
end

if (EVENT == 1801) then
	SaveEvent(UID, 2845);
end

if (EVENT == 1802) then
	SaveEvent(UID, 2844);
end

if (EVENT == 1803) then
	SaveEvent(UID, 2847);
end

if (EVENT == 1804) then
	MonsterCount = CountMonsterQuestSub(UID, 8008, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 1806, 3008, 101);
	end
end

if (EVENT == 1806) then
	SaveEvent(UID, 2846);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8009;

if (EVENT == 1900) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 1905);
end

if (EVENT == 1905) then
	SelectMsg(UID, 4, savenum, 9719, NPC, 22, 1901, 23, 1902);
end

if (EVENT == 1901) then
	SaveEvent(UID, 2850);
end

if (EVENT == 1902) then
	SaveEvent(UID, 2849);
end

if (EVENT == 1903) then
	SaveEvent(UID, 2852);
end

if (EVENT == 1904) then
	MonsterCount = CountMonsterQuestSub(UID, 8009, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 1906, 3008, 101);
	end
end

if (EVENT == 1906) then
	SaveEvent(UID, 2851);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8010;

if (EVENT == 2000) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 2005);
end

if (EVENT == 2005) then
	SelectMsg(UID, 4, savenum, 9720, NPC, 22, 2001, 23, 2002);
end

if (EVENT == 2001) then
	SaveEvent(UID, 2855);
end

if (EVENT == 2002) then
	SaveEvent(UID, 2854);
end

if (EVENT == 2003) then
	SaveEvent(UID, 2857);
end

if (EVENT == 2004) then
	MonsterCount = CountMonsterQuestSub(UID, 8010, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 2006, 3008, 101);
	end
end

if (EVENT == 2006) then
	SaveEvent(UID, 2856);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8011;

if (EVENT == 2100) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 2105);
end

if (EVENT == 2105) then
	SelectMsg(UID, 4, savenum, 9721, NPC, 22, 2101, 23, 2102);
end

if (EVENT == 2101) then
	SaveEvent(UID, 2860);
end

if (EVENT == 2102) then
	SaveEvent(UID, 2859);
end

if (EVENT == 2103) then
	SaveEvent(UID, 2862);
end

if (EVENT == 2104) then
	MonsterCount = CountMonsterQuestSub(UID, 8011, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 2106, 3008, 101);
	end
end

if (EVENT == 2106) then
	SaveEvent(UID, 2861);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8012;

if (EVENT == 2200) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 2205);
end

if (EVENT == 2205) then
	SelectMsg(UID, 4, savenum, 9722, NPC, 22, 2201, 23, 2202);
end

if (EVENT == 2201) then
	SaveEvent(UID, 2865);
end

if (EVENT == 2202) then
	SaveEvent(UID, 2864);
end

if (EVENT == 2203) then
	SaveEvent(UID, 2867);
end

if (EVENT == 2204) then
	MonsterCount = CountMonsterQuestSub(UID, 8012, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 2206, 3008, 101);
	end
end

if (EVENT == 2206) then
	SaveEvent(UID, 2866);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8013;

if (EVENT == 2300) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 2305);
end

if (EVENT == 2305) then
	SelectMsg(UID, 4, savenum, 9723, NPC, 22, 2301, 23, 2302);
end

if (EVENT == 2301) then
	SaveEvent(UID, 2870);
end

if (EVENT == 2302) then
	SaveEvent(UID, 2869);
end

if (EVENT == 2303) then
	SaveEvent(UID, 2872);
end

if (EVENT == 2304) then
	MonsterCount = CountMonsterQuestSub(UID, 8013, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 2306, 3008, 101);
	end
end

if (EVENT == 2306) then
	SaveEvent(UID, 2871);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8014;

if (EVENT == 2400) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 2405);
end

if (EVENT == 2405) then
	SelectMsg(UID, 4, savenum, 9724, NPC, 22, 2401, 23, 2402);
end

if (EVENT == 2401) then
	SaveEvent(UID, 2875);
end

if (EVENT == 2402) then
	SaveEvent(UID, 2874);
end

if (EVENT == 2403) then
	SaveEvent(UID, 2877);
end

if (EVENT == 2404) then
	MonsterCount = CountMonsterQuestSub(UID, 8014, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 2406, 3008, 101);
	end
end

if (EVENT == 2406) then
	SaveEvent(UID, 2876);
	ZoneChange(UID, 21, 817, 448);
end

local savenum = 8015;

if (EVENT == 2500) then
	SelectMsg(UID, 2, savenum, 9725, NPC, 10, 2505);
end

if (EVENT == 2505) then
	SelectMsg(UID, 4, savenum, 9724, NPC, 22, 2501, 23, 2502);
end

if (EVENT == 2501) then
	SaveEvent(UID, 2885);
end

if (EVENT == 2502) then
	SaveEvent(UID, 2884);
end

if (EVENT == 2503) then
	SaveEvent(UID, 2887);
end

if (EVENT == 2504) then
	MonsterCount = CountMonsterQuestSub(UID, 8016, 1);
	if (MonsterCount < 10) then
		SelectMsg(UID, 2, savenum, 9728, NPC, 10, 101);
	else
		SelectMsg(UID, 4, savenum, 9729, NPC, 3006, 2506, 3008, 101);
	end
end

if (EVENT == 2506) then
	SaveEvent(UID, 2886);
	ZoneChange(UID, 21, 817, 448);
end