
#include "LogData.h"


 LogData::LogData(KString participantID) : GameData("log")
 {
   this->participantID = participantID;

   readDelimiter = '|';
 }



 void LogData::AddDataLine(KString line)
 {
  GameData::AddDataLine( KString("participant_id:%s|%s", participantID.c_str(), line.c_str()));
 }
