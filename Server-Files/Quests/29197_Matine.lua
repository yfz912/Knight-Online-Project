local Ret = 0;
local NPC = 29197;

if (EVENT == 100) then
	SelectMsg(UID, 3, -1, 10486, NPC, 7572, 200, 7582, 300);
end

if (EVENT == 200) then
	SelectMsg(UID, 2, -1, 10370, NPC, 20);
end

if (EVENT == 300) then
	SelectMsg(UID, 2, -1, 10499, NPC, 7585, 301, 27);
end

if EVENT == 301 then
	ItemA = HowmuchItem(UID, 508165000);
	  if  ItemA == 0 then
	   SelectMsg(UID, 2, savenum,8917, NPC, 10, 190);
	  else
		EVENT =  302
	  end
end

if EVENT == 302 then
SelectMsg(UID,2,-1,10501, NPC,10);
Check = CheckExchange(UID, 429)
 if  Check == true then   
   Roll = RollDice(UID, 19) 
   found = Roll + 410
   RunExchange(UID, found);	
      else
   Ret = 1; 
	   end  
end