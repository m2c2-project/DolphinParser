

#include "Data.h"

DataElement::DataElement(KString sname, KString sval)
{
  name = KString(sname);
  val = KString(sval);
}









  GameData::GameData(KString sname)
  {
   name = sname;
  }



  void GameData::AddDataLine(KString line)
  {

    // all this is to check for data in the format (varName:value) and remove the varName and save them in a list of headers

    // only check into this if it is the first pass through (no header and no data lines) or it is after the first pass through (more than 0 data lines) and headers were found (header list size > 0)
    if (headerList.GetSize() == 0 && dataLine.GetSize() == 0 || headerList.GetSize() > 0 && dataLine.GetSize() > 0)
    {
     // first line being entered, see if there are variable names

     GList<KString> entrySplit = line.Split(',');
     if (entrySplit.GetSize() > 0)
     {
      if (entrySplit[0].Contains(':'))
      {

       GList<KString> hList;
       GList<KString> valList;

       // found header names, now go through each entry and get the header name. reform line to remove header names
       for (int i = 0; i < entrySplit.GetSize(); i++)
       {

        // split into varname and value
        GList<KString> valSplit = entrySplit[i].Split(':',2);
        if (valSplit.GetSize() >= 2)
        {
          // if the correct number is found (2, var name and value) add to the lists
         hList.Add(valSplit[0]);
         valList.Add(valSplit[1]);
        }
        else if (valSplit.GetSize() > 0)
        {
         // else, add the whole line
         valList.Add(entrySplit[i]);
        }

       }

       // now the line is split into hList (header list) and valList


       // if the header list wasn't made yet, copy hList to the header list
         if (headerList.GetSize() == 0)
         {
          headerList.AddAll(&hList);
/*
          // now that we have the header list, add the headers as the first data line
          KString headerLine = "";


           for (int i = 0; i < headerList.GetSize(); i++)
          {
           headerLine.Add(headerList[i]);
           if (i < headerList.GetSize()-1){headerLine.Add(",");}
          }

          dataLine.Add(headerLine);*/

         }

         // change line to remove all variable headers

         line = "";

         for (int i = 0; i < valList.GetSize(); i++)
         {
          line.Add(valList[i]);
          if (i < valList.GetSize()-1){line.Add(",");}
         }




      }
     }


    }


    dataLine.Add(line);
  }


  KString GameData::GetHeaderLine()
  {
          KString headerLine = "";


           for (int i = 0; i < headerList.GetSize(); i++)
          {
           headerLine.Add(headerList[i]);
           if (i < headerList.GetSize()-1){headerLine.Add(",");}
          }



          return headerLine;


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


