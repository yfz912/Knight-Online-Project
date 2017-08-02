local Ret = 0;
local NPC = 19008;

if (EVENT == 100) then
	SelectMsg(UID, 3, -1, 8903, NPC, 4519, 8975, 7316, 8639, 8428, 900);
end

if (EVENT == 101) then
Ret = 1;
end

--Open the armory
if (EVENT == 8975) then
	SelectMsg(UID, 2, -1, 9208, NPC, 4160, 8976)
end

if (EVENT == 8976) then 
	Class = CheckClass(UID);
	if (Class == 1 or Class == 13) then -- Beginner Warripr & Portu
	SelectMsg(UID, 2, -1, 8893, NPC, 4466, 4000, 3019)
	elseif (Class == 5 or Class == 14) then -- Novice Warrior & Portu
	SelectMsg(UID, 2, -1, 8885, NPC, 4466, 4000, 3019)
	elseif (Class == 2) then -- Beginner Rogue 
		SelectMsg(UID, 2, -1, 8894, NPC, 4466, 4000, 3019)
	elseif (Class == 5 or Class == 14) then -- Novice Rogue
		SelectMsg(UID, 2, -1, 8886, NPC, 4466, 4000, 3019)
	elseif (Class == 3) then -- Beginner Mage
		SelectMsg(UID, 2, -1, 8895, NPC, 4466, 4000, 3019)
	elseif (Class == 5 or Class == 14) then -- Novice Mage
		SelectMsg(UID, 2, -1, 8887, NPC, 4466, 4000, 3019)
	elseif (Class == 4) then -- Beginner Priest
		SelectMsg(UID, 2, -1, 8896, NPC, 4466, 4000, 3019)
	elseif (Class == 5 or Class == 14) then -- Novice Priest
	SelectMsg(UID, 2, -1, 8888, NPC, 4466, 4000, 3019)
	end
end

if (EVENT == 4000) then -- Beginner Items
	Class = CheckClass(UID);
	Level = GetLevel(UID);
	MONEY = HowmuchItem(UID, 200000);
	if (Class == 1 or Class == 13) then 
		if (Level >= 30 and Level <= 45) then-- Warrior & Portu
		GiveItem(UID, 121430000, 1) -- Training Sword
		GiveItem(UID, 121440000, 1) -- Training Sword
		GiveItem(UID, 125030000, 1) -- Training TwoHandedSword
		GiveItem(UID, 202021000, 1) -- Armor +5
		GiveItem(UID, 202022000, 1) -- Pads +5
		GiveItem(UID, 202023000, 1) -- Helmet +5
		GiveItem(UID, 202024000, 1) -- Gloves +5
		GiveItem(UID, 202025000, 1) -- Boots +5
		GoldLose(UID, 200000)
		end
	elseif (Class == 2) then
		if (Level >= 30 and Level <= 45) then -- Rogue 
			GiveItem(UID, 111470000, 1) -- Training Dagger
			GiveItem(UID, 111470000, 1) -- Training Dagger
			GiveItem(UID, 161470000, 1) -- Training Bow
			GiveItem(UID, 242021000, 1) -- Armor +5
			GiveItem(UID, 242022000, 1) -- Pads +5
			GiveItem(UID, 242023000, 1) -- Helmet +5
			GiveItem(UID, 242024000, 1) -- Gloves +5
			GiveItem(UID, 242025000, 1) -- Boots +5			
			GoldLose(UID, 200000)	
		end
	elseif (Class == 3) then
		if (Level >= 30 and Level <= 45) then	-- Mage
			GiveItem(UID, 181430000, 1)	-- Staff 1 
			GiveItem(UID, 181440000, 1)	-- Staff 2
			GiveItem(UID, 262021000, 1) -- Armor
			GiveItem(UID, 262022000, 1) -- Pads
			GiveItem(UID, 262023000, 1) -- Helmet
			GiveItem(UID, 262024000, 1) -- Gloves
			GiveItem(UID, 262025000, 1) -- Boots			
			GoldLose(UID, 200000)	
			end
	elseif (Class == 4) then 
		if (Level >= 30 and Level <= 45) then-- Priest
		GiveItem(UID, 191440000, 1)	-- Mace 
		GiveItem(UID, 282021000, 1) -- Armor +5
		GiveItem(UID, 282022000, 1) -- Pads +5
		GiveItem(UID, 282023000, 1) -- Helmet +5 
		GiveItem(UID, 282024000, 1) -- Gloves +5
		GiveItem(UID, 282025000, 1) -- Boots +5 
		GoldLose(UID, 200000)
		end
	end
end

--mounting
if (EVENT == 8639) then
	ITEM = HowmuchItem(UID, 900387000);
	if (ITEM > 0) then
	RobItem(UID, 900387000, 1)
	GiveItem(UID, 700042769, 1)
	else 
	SelectMsg(UID, 2, -1, 10101, NPC, 4170, 101);
	end
end

--Settlement support
if (EVENT == 900) then
	SelectMsg(UID, 2, -1, 11846, NPC, 8429, 901);
end

if (EVENT == 901) then
	SelectMsg(UID, 2, -1, 11847, NPC, 10, 101);
end