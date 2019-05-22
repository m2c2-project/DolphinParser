

#include "Data.h"

DataElement::DataElement(KString sname, KString sval)
{
  name = KString(sname);
  val = KString(sval);
}















































  ExtraData::ExtraData(KString setID)
  {
   ID = setID;
   surveysRead = 0;
   surveysComplete = 0;
  }




  void ExtraData::AddSurvey(bool complete, int session, KString packName)
  {


   surveysRead++;

   if (complete)
   {
       // if we've already looked at this session (and it's complete) don't count it again
     if (sessionList.Contains(session)){return;}

     sessionList.Add(session);

     surveysComplete++;
     // add to complete pack count

     if (completePackCount.Contains(packName))
     {
      int val = completePackCount.Get(packName);
      completePackCount.Set(packName, val+1);
     }
     else
     {
      completePackCount.Put(packName, 1);
     }

   }
  }


