
#ifndef GAMEDATA_FH
#define GAMEDATA_FH 1

#include "main.h"


// data to keep about one game within a pack
// a DataFile can contain many GameDatas. Depends on the number the user answered in a pack



class GameData
{
 public:
  GameData(KString sname);

  KString name;
  GList<KString> dataLine;



  GList<KString> headerList;

  GList<GMap<KString, KString>* > dataLineMap; // contains a map for each data line read (each trial)

  void AddDataLine(KString line);

  KString GetHeaderLine();



};



#endif
