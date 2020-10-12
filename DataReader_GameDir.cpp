
#include "DataReader.h"

#include "Data.h"

#include "DataFile.h"

#include "GameData.h"
#include "LogData.h"

#include "DataSettings.h"

using namespace std;

void DataReader::ReadDirectory(KString dirPath)
{
  GList<KString>* fileList = KReader::GetDirFiles(dirPath);

   for (int i = 0; i < fileList->GetSize(); i++)
   {
    bool isDir = !fileList->Get(i).Contains(".");


    GList<KString> fileSplit = fileList->Get(i).Split('_');

    if (fileSplit.GetSize() < 1){continue;}

    KString first = fileSplit[0];

    if (!isDir && (first == "game" ||  first == "cogtask"))
    {
     // - found game read game file

     GList<KString> split = fileList->Get(i).Split('_');

     if (split.GetSize() > DataSettings::gameNameSplitIndex)
     {
      KString gameName = split[DataSettings::gameNameSplitIndex];

      cout << "found file: " << fileList->Get(i).c_str() << endl;
      //system("PAUSE");

      KString filePath = KString(dirPath);
      filePath.Add("/");
      filePath.Add(fileList->Get(i));


      KReader reader;
      reader.OpenReadFile(filePath);


      GameData* gameData = new GameData(gameName);



      while (reader.HasNextLine())
      {
       KString line = reader.ReadNextLine();
       if (!(line == ""))
       {
        gameData->AddDataLine(line);
       }
      }

     // int cogtaskNameI = gameData->headerList.FindElement("cogtask_name");
     // if (cogtaskNameI > -1)
      {
        if (gameData->dataLineMap.GetSize() > 0)
        {
          gameData->name = (gameData->dataLineMap.Get(0))->Get2("cogtask_name");
          gameData->name.Replace(" ", "-");
        }
      }

      // add the gamedata to the first data file (which stores all game data)
      dataFileList.Get(0)->gameDataList.Add(gameData);

      reader.CloseReadFile();






     }

    }
    else if (!isDir && first == "data")
    {
      cout << "found data file: " << fileList->Get(i).c_str() << endl;

      // found data, add to data file
      KString setFileName = KString(dirPath);
      setFileName.Add("/");
      setFileName.Add(fileList->Get(i));
      AddDataFile(setFileName);
    }
    else if (!isDir && fileSplit.GetSize() >= 2 && fileSplit.GetLast().Contains("log.txt") && !(fileSplit[0] == "beep"))
    {
      //read log files

      cout << "found log file" << fileList->Get(i).c_str() << endl;

     // system("PAUSE");

      KString filePath = KString(dirPath);
      filePath.Add("/");
      filePath.Add(fileList->Get(i));


      KReader reader;
      reader.OpenReadFile(filePath);


      LogData* logData = new LogData(fileSplit[0]);

      while (reader.HasNextLine())
      {
       KString line = reader.ReadNextLine();
       if (!(line == ""))
       {
        logData->AddDataLine(line);
       }
      }

      // add the logdata to the first data file (which stores all game data)
      dataFileList.Get(0)->gameDataList.Add(logData);

      reader.CloseReadFile();


    }
    else if (isDir)
    {


      if ( !(fileList->Get(i) == ".") && !(fileList->Get(i) == "..") && !(fileList->Get(i) == "out"))
      {

       KString dirPathCheck = KString(dirPath);
       dirPathCheck.Add("/");
       dirPathCheck.Add(fileList->Get(i));

       cout << "read dir path: " << dirPathCheck.c_str() << endl;


       ReadDirectory(dirPathCheck);
      }

    }


   }

}
