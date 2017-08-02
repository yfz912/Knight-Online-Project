--Event NPC From KoprimeWorld Code By Melanor


local UserClass;
local QuestNum;
local Ret = 0;
local NPC = 27100;


if EVENT == 100 then
    SelectMsg(UID, 3, -1, 6038, NPC, 7203,152,7234,154,7235,155,7238,156);
end


local ITEMA = 0;




--Exper 


if EVENT == 152 then
   ITEMA = HowmuchItem(UID, 900132000);
   if ITEMA < 1 then
      GoldLose(UID, 50000)

--- Lvl Upper
ExpChange(UID, 1)

     
   end
end





-- Event Item Exchange


 if EVENT == 154 then
   ITEMA = HowmuchItem(UID, 379118000);
   if ITEMA < 1 then
     
     

      GiveItem(UID, 800132780, 1)





      


  end
end




-- scroll  (old clan match)


 if EVENT == 155 then
 ITEMA = HowmuchItem(UID, 379117000);
if ITEMA < 1 then
    
GoldLose(UID, 50000)
GiveItem(UID, 910139000, 30)
GiveItem(UID, 910140000, 30)
GiveItem(UID, 191600881, 30)
GiveItem(UID, 910141000, 30)
     


 end
end




-- Beginner Suprise


 if EVENT == 156 then
   ITEMA = HowmuchItem(UID, 379120000);
   if ITEMA < 1 then
     
      GoldLose(UID, 50000)
      GiveItem(UID, 389400000, 1)
      GiveItem(UID, 800014000, 1)
      GiveItem(UID, 800015000, 1)

      GiveItem(UID, 800013000, 1)
      GiveItem(UID, 800010000, 1)
     




   end
end


if EVENT == 155 then
   ITEMA = HowmuchItem(UID, 379117000);
   if ITEMA < 1 then
     GiveItem(UID, 910141000, 30)





   end
end