local Ret = 0;
local NPC = 18005;

if (EVENT == 100) then
	SelectMsg(UID, 3, savenum, 101, NPC, 4262, 200, 4554, 300, 40514, 400, 8209, 500, 7591, 600, 7746, 700, 7785, 800, 7799, 900, 40515, 1000);
end

--Licence List
if (EVENT == 200) then
	Cakmavoid(UID)
--> Report List code in Source
end

-- Information of King's inspector
if (EVENT == 300) then
--> Show King & Sheriff Names code in Source
end

--Bilbor's Gift -> Start
if (EVENT == 400) then
	SelectMsg(UID, 2, 60, 470, NPC, 4518, 401, 40515);
end

if (EVENT == 401) then
	SelectMsg(UID, 2, 60, 471, NPC, 4160, 402);
end

if (EVENT == 402) then
	-- Show quest
end

if (EVENT == 403) then
	RobItem(UID, 379048000, 3)
	GiveItem(UID, 910139000, 3) -- Armor Scroll(300)
	GiveItem(UID, 800015000, 3) -- Swift Potion
	GiveItem(UID, 810079000, 3) -- Hp Scroll(1500)
	GiveItem(UID, 800051000, 3) -- Ascend
--	SaveEvent(UID);
end
--Bilbor's Gift -> End


-- Celebration of the 10th Anniversary
if (EVENT == 500) then
	GiveItem(UID, 900562000, 1)
end

-- VIP Card Exchange
if (EVENT == 600) then
end

-- Joe's Slogan
if (EVENT == 700) then
	GoldLose(UID, 10000)
	GiveItem(UID, 810181843, 1) -- Joe Slogan
end

-- Chaos Knight Day
if (EVENT == 800) then
end

--[Knight Chaos Day]
if (EVENT == 900) then
end

-- Just Go
if (EVENT == 1000) then
	Ret = 1;
end
