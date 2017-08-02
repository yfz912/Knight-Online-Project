local Ret = 0;
local NPC = 31553;

if (EVENT == 100) then
	QuestStatus = GetQuestStatus(UID, 633)
	
	if(QuestStatus == 1) then
		EVENT = 101
	end
end

if(EVENT == 101) then
	COUNTA = HowmuchItem(UID, 900156000) 
	if(COUNTA < 1) then
		GiveItem(UID, 900156000)
		RobItem(UID, 900201000)
	end
end
