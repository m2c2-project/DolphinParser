
#include "DataReader.h"

#include "Data.h"

#include "DataFile.h"

#include "GameData.h"

using namespace std;

void DataReader::ReadDirectory(KString dirPath)
{
  GList<KString>* fileList = KReader::GetDirFiles(dirPath);

   for (int i = 0; i < fileList->GetSize(); i++)
   {
    bool isDir = !fileList->Get(i).Contains(".");

    if (!isDir && fileList->Get(i).Contains("game_"))
    {
     // - found game read game file

     GList<KString> split = fileList->Get(i).Split('_');

     if (split.GetSize() > 4)
     {
      KString gameName = split[4];

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

      // add the gamedata to the first data file (which stores all game data)
      dataFileList.Get(0)->gameDataList.Add(gameData);

      reader.CloseReadFile();






     }

    }
    else if (!isDir && fileList->Get(i).Contains("data_"))
    {
      cout << "found data file: " << fileList->Get(i).c_str() << endl;

      // found data, add to data file
      KString setFileName = KString(dirPath);
      setFileName.Add("/");
      setFileName.Add(fileList->Get(i));
      AddDataFile(setFileName);
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
