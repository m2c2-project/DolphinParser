
  #include "DataReader.h"

  #include "Data.h"

  #include "DataFile.h"

  #include "DataSettings.h"

  #include "GameData.h"


  // writes all data in separate files separated by pack/game)
  void DataReader::WriteSeparate()
  {
      // this function is only used when DataSettings::combineFiles == 0
      // it writes all the parsed data into separate files for each pack and game


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



       // go through all the titles in the game list
       // each title will be its own file
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






       writer.OpenWriteFile(KString("%s\\gamedata_%s_%s.txt", outDir.c_str(), gameTitle.c_str(), date.c_str()), false);
      // writer.WriteFile("s");

    //   system("PAUSE");

       if (gameDataMatchList.GetSize() > 0)
       {
         bool hasHeaders = false;
         for (int i = 0; i < gameDataMatchList.GetSize(); i++)
         {
          if (gameDataMatchList[i]->headerList.GetSize() > 0){hasHeaders = true; break;}
         }

         if (hasHeaders)
         {
            // deal with GameData that has a header (ie data includes variable names)


            GList<KString> completeHeaderList; // list of all variable names

            // go through each game data entry (for this title) and find all the possible variable names to create the complete header list
            for (int i = 0; i < gameDataMatchList.GetSize(); i++)
            {


              for (int j = 0; j < gameDataMatchList[i]->headerList.GetSize(); j++)
              {
               if (!completeHeaderList.Contains(gameDataMatchList[i]->headerList[j]))
               {
                completeHeaderList.Add(gameDataMatchList[i]->headerList[j]);
               }
              }

            }

            // create complete header line
            KString completeHeaderLine = "";
            for (int i = 0; i < completeHeaderList.GetSize(); i++)
            {
             completeHeaderLine.Add(completeHeaderList.Get(i));

             if (i < completeHeaderList.GetSize()){completeHeaderLine.Add(DataSettings::DELIMETER);}
            }

            // write complete header line
            writer.WriteFile(completeHeaderLine);
            writer.WriteFile(KWriter::GetEndLine());


            // go through each matching game data and export the lines based to match up with the header titles
            for (int i = 0; i < gameDataMatchList.GetSize(); i++)
            {
              GameData* gameData = gameDataMatchList[i];
              // go through each line of the game data and export the values that match up to the header list
              for (int j = 0; j < gameData->dataLineMap.GetSize(); j++)
              {

                 // go through the complete header list and find the values in the map one by one
                 for (int k = 0; k < completeHeaderList.GetSize(); k++)
                 {
                   // std::cout << completeHeaderList[k].c_str() << "\n";
                 //  system("PAUSE");

                   KString writeval = gameData->dataLineMap[j]->Get2(completeHeaderList[k]);
                   writer.WriteFile(writeval);
                   if (k < completeHeaderList.GetSize()-1){writer.WriteFile(DataSettings::DELIMETER);}

                 }

                  writer.WriteFile(KWriter::GetEndLine());


              }


            }




         }
         else
         {
           // no headers given (ie data was not saved with variable names)
           // just list out each line

           writer.WriteFile(gameDataMatchList[0]->GetHeaderLine());
           writer.WriteFile(KWriter::GetEndLine());


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

         }

       }

       writer.CloseWriteFile();
      }












  }
