local UserClass;
local QuestNum;
local Ret = 0;
local NPC = 27300;

--Event Start
if (EVENT) == 100 then
    SelectMsg(UID, 3, -1, 7110, NPC, 50205, 150, 50206, 151, 50207, 152, 50208, 153); --, 50209, 154
end

--Event Exit
if (EVENT == 50) then
	ret = 1
end

--NT Scroll
if (EVENT == 150) then
	UserNP = CheckLoyalty (UID);
	CheckNT = isRoomForItem(UID, 800360000);
	if (UserNP >= 3000) then
		if (CheckNT == -1) then
			SelectMsg(UID, 2, -1, 7111, NPC, 10, 50);
		else
			RobLoyalty(UID, 3000)
			GiveItem(UID, 800360000, 1)
		end
	else
		SelectMsg(UID, 3, -1, 7112, NPC, 10, 50)
	end
end

--Gender Scroll
if (EVENT == 151) then
	UserNP = CheckLoyalty (UID);
	CheckGen = isRoomForItem(UID, 800560000);
	if (UserNP >= 2000) then
		if (CheckGen == -1) then
			SelectMsg(UID, 2, -1, 7111, NPC, 10, 50);
		else
			RobLoyalty(UID, 2000)
			GiveItem(UID, 800560000, 1)
		end
	else
		SelectMsg(UID, 3, -1, 7112, NPC, 10, 50)
	end
end

--Job Scroll
if (EVENT == 152) then
	UserNP = CheckLoyalty (UID);
	CheckJob = isRoomForItem(UID, 800570000);
	if (UserNP >= 5000) then
		if (CheckJob == -1) then
			SelectMsg(UID, 2, -1, 7111, NPC, 10, 50);
		else
			RobLoyalty(UID, 5000)
			GiveItem(UID, 800570000, 1)
		end
	else
		SelectMsg(UID, 3, -1, 7112, NPC, 10, 50)
	end
end

--NC Scroll
if (EVENT == 153) then
	UserNP = CheckLoyalty (UID);
	CheckNam = isRoomForItem(UID, 800032000);
	if (UserNP >= 5000) then
		if (CheckNam == -1) then
			SelectMsg(UID, 2, -1, 7111, NPC, 10, 50);
		else
			RobLoyalty(UID, 5000)
			GiveItem(UID, 800032000, 1)
		end
	else
		SelectMsg(UID, 3, -1, 7112, NPC, 10, 50)
	end	
end

--if (EVENT == 154) then
--	SelectMsg(UID, 3, -1, 7109, NPC, 10, 50)
--end
