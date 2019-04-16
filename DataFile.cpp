



#include "DataFile.h"

#include "GameData.h"

#include "Data.h"

#include "DataSettings.h"



  DataFile::DataFile(KString sfilename)
  {
   elementList = GList<DataElement*>();
   filename = sfilename;

   ID = "no_id_set";
   surveyComplete = false;
   sessionID = -1;
   packName = "no_pack_name_found";

   exitStatus = "NO_EXIT_STATUS_FOUND";
   exitScreen = "NO_EXIT_SCREEN_FOUND";

  }

  DataFile::~DataFile()
  {


  }


  void DataFile::Read()
  {
    if (filename == ""){return;}




    KReader reader;

    reader.OpenReadFile(filename);

    GameData* gameData = NULL;

    while (reader.HasNextLine())
    {
     KString line = reader.ReadNextLine();
     std::cout << line.c_str() << KString::GetLineBreak().c_str();
     if (gameData != NULL)
     {
      if (line.Contains(":"))
      {
       // check for game ending
       GList<KString> split = line.Split(':');
       if (split.GetSize() == 2)
       {
        if (split[0] == "End_Game_Data")
        {
         // finish the game reading
         gameData = NULL;
         continue;
        }
       }
      }

      // regular game data line. read in.
       if (!(line == "")){gameData->AddDataLine(line);}
     }
     else if (line.Contains(":")) // contains a variable
     {
      GList<KString> split = line.Split(':');
      if (split.GetSize() > 1)
      {

        // combine the rest of the split in case data contained any ':'
        KString addVar = split[1];
        for (int i = 2; i < split.GetSize(); i++)
        {
          addVar.Add(":");
          addVar.Add(split[i]);
        }

       // start reading in game data
       if (split[0] == "Game_Data")
       {

        gameData = new GameData(addVar);
        gameDataList.Add(gameData);
        continue;
       }

       KString dataTitleName = split[0];



       // regular data element
       DataElement* element = new DataElement(dataTitleName, addVar);
       // handle extra info
       HandleExtraInfo(element);
       elementList.Add(element);


      }

     }

    }

    reader.CloseReadFile();
  }

  void DataFile::MakeTableLine(GList<KString>* headerList)
  {
   tableLine.RemoveAll();

   // take a header list and go through the variables to make a table line that matches it.
   // aka rearrange variables in the order of the variable names in the header list

   for (int i = 0; i < headerList->GetSize(); i++)
   {
    KString varName = headerList->Get(i);

    bool found = false;
    for (int j = 0; j < elementList.GetSize(); j++)
    {
     if (elementList[j]->name == varName)
     {
      found = true;
      tableLine.Add(elementList[j]->val);
      break;
     }

    }
    if (!found)
    {

     tableLine.Add(DataSettings::NO_DATA);
    }

   }

  }










  void DataFile::HandleExtraInfo(DataElement* data)
  {
     //std::cout << "*** extra info ****"  << std::endl;

     KString name = KString::ToLower(data->name);

    if (name == "user_id" || name == "id"){ID = data->val;}
    else if (name == "session_id" || name == "session"){sessionID = data->val.GetInt();}
    else if (name == "exit status")
    {

     exitStatus = data->val;
     //std::cout << "Reading exit status: " << exitStatus.c_str() << std::endl;
     // if the DataSettings::lastScreenList doesn't have any entries, any ending screen is considered finished

     // removed this (exitStatus == "NORMAL" &&) because any exit status can be complete if it reaches the end screen
     // DataReader_CalcExtraData will check to make sure the same session isn't read twice.
     if ((DataSettings::lastScreenList.GetSize() == 0 || DataSettings::lastScreenList.Contains(exitScreen)))
     {
      surveyComplete = true;
     }

    }
    else if (name == "exit screen")
    {
     exitScreen = data->val;
      //std::cout << "Reading exit screen: " << exitStatus.c_str() << std::endl;

     if ( (DataSettings::lastScreenList.GetSize() == 0 || DataSettings::lastScreenList.Contains(exitScreen)))
     {
      surveyComplete = true;
     }
    }
    else if (name == "pack")
    {
     packName = data->val;
    }

  }







