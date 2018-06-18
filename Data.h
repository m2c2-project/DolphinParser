
#ifndef DATA_FH
#define DATA_FH 1

#include "main.h"

class GameData;

// data element
// data on one individual survey question
// a Data File contains many DataElements
// one created for each (data_var_name:data_var_value) pair contained in raw data file.

class DataElement
{
 public:

  DataElement(KString sname, KString sval);



  KString name;
  KString val;


};





// data to keep about information to display to user after reading all files
// each user id will get an "ExtraData" object
// contains info on:
// number of surveys completed
// number of survey completed for each pack (completePackCount map)
// a list of sessions that were read in (sessionList: in order to make sure they session isn't read twice)

class ExtraData
{
 public:

  ExtraData(KString setID);

  KString ID;
  int surveysRead;
  int surveysComplete;


  GList<int> sessionList;

  // < packName, num complete>
  GMap<KString, int> completePackCount;



  void AddSurvey(bool complete, int session, KString packName);


};


#endif
