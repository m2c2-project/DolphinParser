

#include "GameData.h"


#include "DataSettings.h"

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
         else
         {
          // if the header list is already created, only add the non duplicate headers of this line
          // (each line my have different headers)
          for (int hA = 0; hA < hList.GetSize(); hA++)
          {
           if (!headerList.Contains(hList[hA]))
           {
            headerList.Add(hList[hA]);
           }
          }


         }

         // change line to remove all variable headers

         line = "";

         for (int i = 0; i < valList.GetSize(); i++)
         {
          line.Add(valList[i]);
          if (i < valList.GetSize()-1){line.Add(DataSettings::DELIMETER);}
         }


         // add all hList and valList to a new dataLineMap
         dataLineMap.Add(new GMap<KString, KString>());
         GMap<KString, KString>* dmap = dataLineMap.GetLast();
         for (int i = 0; i < hList.GetSize(); i++)
         {
          dmap->Put(hList[i], valList[i]);
        //  std::cout << hList[i].c_str() << " " << valList[i].c_str() << "\n";
        //  if (dmap->Contains(hList[i])){std::cout << hList[i].c_str() << " " << dmap->Get2(hList[i]).c_str() << "\n";}
     //     system("PAUSE");
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
           if (i < headerList.GetSize()-1){headerLine.Add(DataSettings::DELIMETER);}
          }



          return headerLine;


  }
