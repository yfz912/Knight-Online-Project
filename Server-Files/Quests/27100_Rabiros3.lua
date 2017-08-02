local UserClass;
local QuestNum;
local Ret = 0;
local NPC = 27100;


if EVENT == 100 then
    SelectMsg(UID, 3, -1, 7100, NPC, 9100, 150, 9103, 103, 9104, 104, 9102, 102, 9105, 105, 9106, 106);
end


local ITEMA = 0;
local ITEMB = 0;
local ITEMC = 0;
local ITEMD = 0;
local ITEME = 0;

--Scroll and ibex potion.
if EVENT == 150 then
   ITEMA = HowmuchItem(UID, 700021000);
   nCount = GetCountEmptySlot(UID);
   if (ITEMA >= 1) then
	if (nCount >= 5) then
	  RobItem(UID, 700021000)
      GiveItem(UID, 508011442, 1, 3)
      GiveItem(UID, 508013319, 1, 3)
      GiveItem(UID, 514573474, 1, 3)
      GiveItem(UID, 514573474, 1, 3)
      GiveItem(UID, 810179840, 1, 3)
	 else
		SelectMsg(UID, 2, -1, 7111, NPC, 10, 50);
	end
   else
      SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);
    end
end
   
--Exit Box
if (EVENT == 151) then
	Ret = 1;
end

--______________________________________________________

--Yellow Treasure

if (EVENT == 103) then
	UserClass = CheckClass(UID);
	ITEMB = HowmuchItem(UID, 379150000);
	if (UserClass == 6) then
		if (ITEMB >= 1) then 
		RobItem(UID, 379150000)
		GiveItem(UID, 1110531581, 1, 1)
		GiveItem(UID, 910248763, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 8) then
		if (ITEMB >= 1) then 
		RobItem(UID, 379150000)
		GiveItem(UID, 1110529581, 1, 1)
      	GiveItem(UID, 1110530581, 1, 1)
		GiveItem(UID, 1110532581, 1, 1)
		GiveItem(UID, 910248763, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 10) then
		if (ITEMB >= 1) then 
		RobItem(UID, 379150000)
		GiveItem(UID, 1110533641, 1, 1)
      	GiveItem(UID, 1110533671, 1, 1)
		GiveItem(UID, 1110533701, 1, 1)
		GiveItem(UID, 910248763, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 12) then
		if (ITEMB >= 1) then 
		RobItem(UID, 379150000)
		GiveItem(UID, 1110534581, 1, 1)
      	GiveItem(UID, 1110535581, 1, 1)
		GiveItem(UID, 910248763, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);
		end
	end
	
end

--_______________________________________________________
--White Treasure

if (EVENT == 104) then
	UserClass = CheckClass(UID);
	ITEMC = HowmuchItem(UID, 379149000);
	if (UserClass == 6) then
		if (ITEMC >= 1) then 
		RobItem(UID, 379149000)
		GiveItem(UID, 1110592881, 1, 1)
      	GiveItem(UID, 1110593881, 1, 1)
      		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 8) then
		if (ITEMC >= 1) then 
		RobItem(UID, 379149000)
		GiveItem(UID, 1110591881, 1, 1)
      	GiveItem(UID, 1110594881, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 10) then
		if (ITEMC >= 1) then 
		RobItem(UID, 379149000)
		GiveItem(UID, 1110595521, 1, 1)
      	GiveItem(UID, 1110595551, 1, 1)
		GiveItem(UID, 1110595581, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 12) then
		if (ITEMC >= 1) then 
		RobItem(UID, 379149000)
		GiveItem(UID, 1110596881, 1, 1)
      	GiveItem(UID, 1110597881, 1, 1)
		GiveItem(UID, 1110592881, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);
		end
	end
end	
--_______________________________________________________

--Black Treasure

if (EVENT == 102) then
	UserClass = CheckClass(UID);
	ITEMC = HowmuchItem(UID, 379148000);
	if (UserClass == 6) then
		if (ITEMC >= 1) then 
		RobItem(UID, 379148000)
		GiveItem(UID, 1110542791, 1, 1)
      	GiveItem(UID, 1110543791, 1, 1)
      		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 8) then
		if (ITEMC >= 1) then 
		RobItem(UID, 379148000)
		GiveItem(UID, 1110548791, 1, 1)
      	GiveItem(UID, 1110544791, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 10) then
		if (ITEMC >= 1) then 
		RobItem(UID, 379148000)
		GiveItem(UID, 1110545311, 1, 1)
      	GiveItem(UID, 1110545341, 1, 1)
		GiveItem(UID, 1110545371, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 12) then
		if (ITEMC >= 1) then 
		RobItem(UID, 379148000)
		GiveItem(UID, 1110546791, 1, 1)
      	GiveItem(UID, 1110547791, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);
		end
	end
	
end

--______________________________________________________

--Blue Treasure

if (EVENT == 105) then
	ITEMD = HowmuchItem(UID, 379156000);
	if (ITEMD >= 1) then
	RobItem(UID, 379156000)
	GiveLoyalty(UID, 500)
	else
	SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);
	end
end
--______________________________________________________
--Green Treasure

if (EVENT == 106) then
	UserClass = CheckClass(UID);
	ITEME = HowmuchItem(UID, 379155000);
	if (UserClass == 6) then
		if (ITEME >= 1) then 
		RobItem(UID, 379155000)
		GiveItem(UID, 1110952311, 1, 1)
      	GiveItem(UID, 1110953521, 1, 1)
		GiveItem(UID, 900177664, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 8) then
		if (ITEME >= 1) then 
		RobItem(UID, 379155000)
		GiveItem(UID, 1110951611, 1, 1)
      	GiveItem(UID, 1110954611, 1, 1)
		GiveItem(UID, 900177664, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 10) then
		if (ITEME >= 1) then 
		RobItem(UID, 379155000)
		GiveItem(UID, 1110955731, 1, 1)
		GiveItem(UID, 900177664, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);	
		end

	elseif (UserClass == 12) then
		if (ITEME >= 1) then 
		RobItem(UID, 379155000)
		GiveItem(UID, 1110956611, 1, 1)
      	GiveItem(UID, 1110957611, 1, 1)
		GiveItem(UID, 1110953521, 1, 1)
		GiveItem(UID, 900177664, 1, 1)
		else
		SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);
		end
	end
	
end