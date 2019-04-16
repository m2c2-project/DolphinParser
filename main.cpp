#include <iostream>

#include "main.h"

using namespace std;


#include "DataReader.h"

#include <Direct.h>

#include "DataSettings.h"


int main(int argc, char* argv[])
{

    DataReader::ReadSettingsFile("parser_settings.txt");

   KString upper = "UpPeR CaSe!";
   KString lower = KString::ToLower(upper);

   char c = tolower('C');

  //   cout << "test:" << c << " " << upper.c_str() << " " << lower.c_str() << endl;

     cout << "Welcome to the Survey Dolphin Data Parser!" << endl;


    if (argc >= 3)
    {
     KString command = KString(argv[1]);
     KString cdir = KString(argv[2]);

     if (command == "dir")
     {
      if (!(cdir == "") && _chdir(cdir.c_str()) != 0)
      {
       cout << endl << "Cannot find directory:" << cdir.c_str() << "!" << endl;
       system("pause");
       return 0;
      }
     }
    }
    else
    {
     cout << "Please enter the directory of the data you want to parse: (enter nothing to use this directory)" << endl;


     std::string sDir;

     getline(std::cin, sDir);

     KString selectDir = KString(sDir);

       if (!(selectDir == "") && _chdir(selectDir.c_str()) != 0)
     {
      cout << endl << "Cannot find directory!" << endl;
      system("pause");
      return 0;
     }

    }






   // _chdir("D:\\projects\\dolphin\\files\\test_data\\UploaderTrial_17_6_14");


      system("mkdir out");



   GList<KString>* fileList = KReader::GetDirFiles(".");


   DataReader* dataReader = new DataReader(".");


   dataReader->Read();

   dataReader->CalculateExtraData();

   if (DataSettings::combineFiles == 0)
   {
    dataReader->WriteSeparate();
   }
   else
   {
    dataReader->WriteAll();
   }

/*
   for (int i = 0; i < fileList->GetSize(); i++)
   {
  //  cout << fileList->Get(i).c_str() << endl;

    if (fileList->Get(i).Contains("data_"))
    {

      KString setFileName = "./";
      setFileName.Add(fileList->Get(i));
      dataReader->AddDataFile(setFileName);

      cout << "yes ";

    }*/

    //cout << fileList->Get(i).c_str() << endl;
/*
    KReader reader;

    reader.OpenReadFile("test_read.txt", false);


    cout << reader.ReadNextLine().c_str();
    cout << reader.ReadNextLine().c_str();
    cout << reader.ReadNextLine().c_str();
    cout << reader.ReadNextLine().c_str();*/










     /*int r;
     cout << "\nComplete! Press enter to exit.";
     cin >> r;*/


     system("PAUSE");






    return 0;
}
