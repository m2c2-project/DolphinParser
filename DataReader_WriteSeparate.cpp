
  #include "DataReader.h"

  #include "Data.h"

  #include "DataFile.h"

  #include "DataSettings.h"


  // writes all data in separate files separated by pack/game)
  void DataReader::WriteSeparate()
  {
      KString del = DataSettings::DELIMETER;

      // write headers



      KWriter writer;

      KString date = KWriter::GetDate();

      KString outDir = GetOutDir();



      KString sCommand = KString("mkdir %s", outDir.c_str());

      system(sCommand.c_str());


      // find all different pack names

      KString varMatch = "Pack";

      GList<KString> matchList;


      // ------------------------------
      // REGULAR SURVEY QUESTION OUTPUT
      // ------------------------------

      { // step 1: - cycle through each data file and make a list of pack names (matchList)

             for (int i = 0; i < dataFileList.GetSize(); i++)
             {
              DataFile* dataFile = dataFileList[i];

              for (int j = 0; j < dataFile->elementList.GetSize(); j++)
              {
               if (dataFile->elementList[j]->name == varMatch)
               {
                if (!matchList.Contains(dataFile->elementList[j]->val))
                {
                 matchList.Add(dataFile->elementList[j]->val);
                }
                break;
               }
              }
             }

      }

      GList<DataFile*> dataFileListX;

      dataFileListX.AddAll(&dataFileList); // make a new list so we can remove data files after they are transfered to another list

      // step 2: cycle through match list and make a list of matching data files to that specific pack value (matchFileList)
      for (int k = 0; k < matchList.GetSize(); k++)
      {
       KString packName = matchList[k];


       GList<DataFile*> matchFileList;


       // write files separately for each pack name

       writer.OpenWriteFile(KString("%s\\%s_%s.txt", outDir.c_str(), packName.c_str(), date.c_str()), false);

       for (int i = 0; i < dataFileListX.GetSize(); i++)
       {
        DataFile* dataFile = dataFileListX[i];

         // keep repeating until a file with that pack name is not found

        bool found = false;
        for (int j = 0; j < dataFile->elementList.GetSize(); j++)
        {
         if (dataFile->elementList[j]->name == varMatch && dataFile->elementList[j]->val == packName )
         {
          matchFileList.Add(dataFile);
          dataFileListX.Remove(i);
          i--;
          found = true;
          break;
         }
        }

       }


       // step 3: create header list for matchFileList (GetHeaderList also creates data lines)

       GList<KString> matchHeaderList = GetHeaderList(&matchFileList);




       // step 4: write data to file

       WriteDataFileList(&matchHeaderList, &matchFileList, &writer);











       writer.CloseWriteFile();


      }











      // -------------------
      // GAME OUTPUT
      // -------------------



      // create game title list
      GList<KString> gameTitleList;
      for (int i = 0; i < dataFileList.GetSize(); i++)
      {
       for (int j = 0; j < dataFileList[i]->gameDataList.GetSize(); j++)
       {
        GameData* gameData = dataFileList[i]->gameDataList[j];
        if (!gameTitleList.Contains(gameData->name))
        {
         gameTitleList.Add(gameData->name);
        }
       }
      }




      for (int g = 0; g < gameTitleList.GetSize(); g++)
      {
       GList<GameData*> gameDataMatchList;
       KString gameTitle = gameTitleList[g];

       // find all game datas that match up to this name
       for (int i = 0; i < dataFileList.GetSize(); i++)
       {
        for (int j = 0; j < dataFileList[i]->gameDataList.GetSize(); j++)
        {
         GameData* gameData = dataFileList[i]->gameDataList[j];
         if (gameData->name == gameTitleList[g])
         {
          gameDataMatchList.Add(gameData);
         }
        }
       }






       writer.OpenWriteFile(KString("%s\\game_%s_%s.txt", outDir.c_str(), gameTitle.c_str(), date.c_str()), false);

       // write header line from the first matched gamedata (all the headers for a game should be the same)
       if (gameDataMatchList.GetSize() > 0)
       {
          writer.WriteFile(gameDataMatchList[0]->GetHeaderLine());

           writer.WriteFile(KWriter::GetEndLine());
       }


       // cycle through all game datas that matched and output in one file
       for (int i = 0; i < gameDataMatchList.GetSize(); i++)
       {
          GameData* gameData = gameDataMatchList[i];

          for (int k = 0; k < gameData->dataLine.GetSize(); k++)
          {

           writer.WriteFile(gameData->dataLine[k]);
           writer.WriteFile(KWriter::GetEndLine());
          }


       }

       writer.CloseWriteFile();
      }












  }
