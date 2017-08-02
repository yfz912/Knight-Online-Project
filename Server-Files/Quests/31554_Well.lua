local Ret = 0;
local NPC = 31552;

if (EVENT == 100) then
	QuestStatus = GetQuestStatus(UID, 633)
	
	if(QuestStatus == 1) then
		EVENT = 101
	end
end

if(EVENT == 101) then
	COUNTA = HowmuchItem(UID, 900165000) 
	if(COUNTA < 1) then
		GiveItem(UID, 900165000)
		RobItem(UID, 900202000)
	end
end
