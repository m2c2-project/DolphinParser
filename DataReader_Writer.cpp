
#include "DataReader.h"

#include "Data.h"

#include "DataFile.h"

#include "DataSettings.h"


using namespace std;

  void DataReader::WriteAll()
  {


      // write headers

      KWriter writer;

      KString outFile = GetOutDir();

      outFile.Add("/out_");

      outFile.Add(KWriter::GetDate());
      outFile.Add(".txt");

      writer.OpenWriteFile(outFile, false);



      WriteDataFileList(&headerList, &dataFileList, &writer);


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

      // write game data. cycle through game names and keep them together

      for (int g = 0; g < gameTitleList.GetSize(); g++)
      {
       writer.WriteFile(gameTitleList[g]);
       writer.WriteFile(KWriter::GetEndLine());

       // find all game datas that match up to this name
       for (int i = 0; i < dataFileList.GetSize(); i++)
       {
        for (int j = 0; j < dataFileList[i]->gameDataList.GetSize(); j++)
        {
         GameData* gameData = dataFileList[i]->gameDataList[j];
         if (gameData->name == gameTitleList[g])
         {
          for (int k = 0; k < gameData->dataLine.GetSize(); k++)
          {
           writer.WriteFile(gameData->dataLine[k]);
           writer.WriteFile(KWriter::GetEndLine());
          }
         }
        }
       }

       writer.WriteFile(KWriter::GetEndLine());

      }



      writer.CloseWriteFile();


  }






  void DataReader::WriteDataFileList(GList<KString>* headerList, GList<DataFile*>* dataFileList, KWriter* writer)
  {

      // write header line
      KString del = DataSettings::DELIMETER;

      for (int i = 0; i < headerList->GetSize(); i++)
      {
       writer->WriteFile(headerList->Get(i));
       if (i < headerList->GetSize()-1){writer->WriteFile(del);}
      }

      writer->WriteFile(KWriter::GetEndLine());

      // write regular data

      for (int i = 0; i < dataFileList->GetSize(); i++)
      {
       for (int j = 0; j < dataFileList->Get(i)->tableLine.GetSize(); j++)
       {
        writer->WriteFile(dataFileList->Get(i)->tableLine[j].c_str());

        if (j < dataFileList->Get(i)->tableLine.GetSize() - 1){writer->WriteFile(del.c_str());}

       }
       writer->WriteFile(KWriter::GetEndLine());

      }

      writer->WriteFile(KWriter::GetEndLine());



  }









