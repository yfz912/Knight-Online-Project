
local UserClass;
local QuestNum;
local Ret = 0;
local NPC = 27100;


if EVENT == 100 then
    SelectMsg(UID, 3, -1, 6038, NPC, 7200, 150,7201,151);
end


local ITEMA = 0;


--Bahamut Set
if EVENT == 150 then
   ITEMA = HowmuchItem(UID, 910453000);
   if ITEMA >= 1 then
      RobItem(UID, 910453000, 1)
      GiveItem(UID, 508051467, 1,3)
	  GiveItem(UID, 508053467, 1,3)




  
       
   end
end


-- Wing 3 day
if EVENT == 151 then
   ITEMA = HowmuchItem(UID, 910464000);
   if ITEMA >= 1 then
      RobItem(UID, 910464000, 1)
      GiveItem(UID, 810179840, 1,3)

   end
end





