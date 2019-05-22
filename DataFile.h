
#ifndef DATA_FILE_FH
#define DATA_FILE_FH 1


#include "main.h"

class DataElement;
class GameData;
class ExtraData;


// this class is for each individual file read

// each individual file is from one session
// so it contains:
// 1 pack
// 1 user
// 1 session id
// a list of game data (a pack can contain multiple games)
// a list of survey data

// it saves


class DataFile
{
 public:





  DataFile(KString sfilename);
  ~DataFile();

  KString filename;

  // extra info
  KString ID;
  bool surveyComplete;
  int sessionID;
  KString packName;
  KString exitStatus;
  KString exitScreen;

  void HandleExtraInfo(DataElement* data);


  void Read();

  GList<DataElement*> elementList;

  GList<GameData*> gameDataList;


  GList<KString> tableLine;

  void MakeTableLine(GList<KString>* headerList);





};




#endif
