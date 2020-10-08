
#ifndef LOGDATA_FH
#define LOGDATA_FH 1

#include "GameData.h"


class LogData : public GameData
{

 public:
  LogData(KString participantID);

  KString participantID;

  void AddDataLine(KString line);


};















#endif
