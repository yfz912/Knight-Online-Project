local UserClass;
local QuestNum;
local Ret = 0;
local NPC = 27100;


if EVENT == 100 then
    SelectMsg(UID, 3, -1, 7100, NPC, 9100, 150, 9112, 152);
end

--Start Items Voucher
if EVENT == 150 then
   ITEMA = HowmuchItem(UID, 700021000);
   nCount = GetCountEmptySlot(UID);
   UserClass = CheckClass(UID);
   UserNation = CheckNation(UID);
   if (ITEMA >= 1) then
		if (nCount >= 5) then
			if (UserClass == 1 or UserClass == 5 or UserClass == 6) then
				RobItem(UID, 700021000)
				GiveItem(UID, 508013319, 1, 3)
				GiveItem(UID, 508011442, 1, 3)
				GiveItem(UID, 511573471, 1, 3)
				GiveItem(UID, 511573471, 1, 3)
				if (UserNation == 1) then
					GiveItem(UID, 810179840, 1, 3)
				else
					GiveItem(UID, 810178836, 1, 3)
				end				
			elseif (UserClass == 2 or UserClass == 7 or UserClass == 8) then
				RobItem(UID, 700021000)
				GiveItem(UID, 508013319, 1, 3)
				GiveItem(UID, 508011442, 1, 3)
				GiveItem(UID, 512573472, 1, 3)
				GiveItem(UID, 512573472, 1, 3)
				if (UserNation == 1) then
					GiveItem(UID, 810179840, 1, 3)
				else
					GiveItem(UID, 810178836, 1, 3)
				end	
			elseif (UserClass == 3 or UserClass == 9 or UserClass == 10) then
				RobItem(UID, 700021000)
				GiveItem(UID, 508013319, 1, 3)
				GiveItem(UID, 508011442, 1, 3)
				GiveItem(UID, 513573473, 1, 3)
				GiveItem(UID, 513573473, 1, 3)
				if (UserNation == 1) then
					GiveItem(UID, 810179840, 1, 3)
				else
					GiveItem(UID, 810178836, 1, 3)
				end				
			elseif (UserClass == 4 or UserClass == 11 or UserClass == 12) then
				RobItem(UID, 700021000)
				GiveItem(UID, 508013319, 1, 3)
				GiveItem(UID, 508011442, 1, 3)
				GiveItem(UID, 514573474, 1, 3)
				GiveItem(UID, 514573474, 1, 3)
				if (UserNation == 1) then
					GiveItem(UID, 810179840, 1, 3)
				else
					GiveItem(UID, 810178836, 1, 3)
				end	
			elseif (UserClass == 13 or UserClass == 14 or UserClass == 15) then
				RobItem(UID, 700021000)
				GiveItem(UID, 508013319, 1, 3)
				GiveItem(UID, 508011442, 1, 3)
				GiveItem(UID, 511573471, 1, 3)
				GiveItem(UID, 511573471, 1, 3)
				if (UserNation == 1) then
					GiveItem(UID, 810179840, 1, 3)
				else
					GiveItem(UID, 810178836, 1, 3)
				end
			end
		else
			SelectMsg(UID, 2, -1, 7111, NPC, 10, 50);
		end
   else
      SelectMsg(UID, 3, -1, 7101, NPC, 9101, 151);
    end
end
   
if (EVENT == 152) then
	nCount = GetCountEmptySlot(UID);
	UserClass = CheckClass(UID);
	if (nCount >= 6) then
		if (UserClass == 1 or UserClass == 5 or UserClass == 6) then
			GiveItem(UID, 910154112)
			GiveItem(UID, 910154112)
			GiveItem(UID, 910157137)
			GiveItem(UID, 910160118)
			GiveItem(UID, 910162272)
			GiveItem(UID, 910162272)
		elseif (UserClass == 2 or UserClass == 7 or UserClass == 8) then
			GiveItem(UID, 910155113)
			GiveItem(UID, 910155113)
			GiveItem(UID, 910157137)
			GiveItem(UID, 910160118)
			GiveItem(UID, 910163273)
			GiveItem(UID, 910163273)
		elseif (UserClass == 3 or UserClass == 9 or UserClass == 10) then
			GiveItem(UID, 910153111)
			GiveItem(UID, 910153111)
			GiveItem(UID, 910158138)
			GiveItem(UID, 910160118)
			GiveItem(UID, 910161271)
			GiveItem(UID, 910161271)
		elseif (UserClass == 4 or UserClass == 11 or UserClass == 12) then
			GiveItem(UID, 910156114)
			GiveItem(UID, 910156114)
			GiveItem(UID, 910159139)
			GiveItem(UID, 910160118)
			GiveItem(UID, 910164274)
			GiveItem(UID, 910164274)
		elseif (UserClass == 13 or UserClass == 14 or UserClass == 15) then
			GiveItem(UID, 910154112)
			GiveItem(UID, 910154112)
			GiveItem(UID, 910157137)
			GiveItem(UID, 910160118)
			GiveItem(UID, 910162272)
			GiveItem(UID, 910162272)
		end
	else
		SelectMsg(UID, 2, -1, 7111, NPC, 10, 50);
	end
end

--Exit Box
if (EVENT == 151) then
	Ret = 1;
end