#include <iostream>

#include "main.h"

using namespace std;


#include "DataReader.h"


#include "DataSettings.h"

#ifdef WIN32
void my_mkdir(const char* path)
{
 // WILL NOT MAKE SUB DIRS!
 _mkdir(path);
}
#endif

#ifndef WIN32
void my_mkdir(const char* path)
{
	mkdir(path, 0777);
}
#endif


int main(int argc, char* argv[])
{








  //   cout << "test:" << c << " " << upper.c_str() << " " << lower.c_str() << endl;

     cout << "Welcome to the Survey Dolphin Data Parser!" << endl;


     KString setOutDir = "out";

     int paramDirFound = 0; // true when the directory to read was set in the command line params


      KString parserSettingsFile = "parser_settings.txt";

     GList<KString> readDirList;

     // get current working directory
     char cwd_s[1024];
     getcwd(cwd_s, sizeof(cwd_s));
     KString cwd = KString(cwd_s);


    // scan through params for settings
    for (int i = 2; i < argc; i = i + 2)
    {

       KString command = KString(argv[i-1]);
       KString val = KString(argv[i]);

       if (command == "dir" || command == "-d")
       {
        /*if (!(val == "") && change_directory(val.c_str()) != 0)
        {
         cout << endl << "Cannot find directory:" << val.c_str() << "!" << endl;
         system("pause");
         return 0;
        }*/


         readDirList.Add(val);
         paramDirFound = 1;
       }
       else if (command == "out" || command == "-o")
       {
         setOutDir = val;
       }
       else if (command == "settings" || command == "-s")
       {
          parserSettingsFile = val;
       }

    }



        DataReader::ReadSettingsFile(parserSettingsFile);




    if (!paramDirFound)
    {
     cout << "Please enter the directory of the data you want to parse: (enter nothing to use this directory)" << endl;


     std::string sDir;

     getline(std::cin, sDir);

     KString selectDir = KString(sDir);


       readDirList.Add(selectDir);

/*
       if (!(selectDir == "") && change_directory(selectDir.c_str()) != 0)
     {
      cout << endl << "Cannot find directory!" << endl;
      system("pause");
      return 0;
     }*/

    }









      //system("mkdir out");

      make_directory(setOutDir.c_str());



//   GList<KString>* fileList = KReader::GetDirFiles(".");


   DataReader* dataReader = new DataReader();

   if (!(setOutDir == ""))
   {

    cout << "setting out dir" << setOutDir.c_str() << endl;

    dataReader->SetOutDir(setOutDir);
   }


   for (int i = 0; i < readDirList.GetSize(); i++)
   {
     dataReader->Read(readDirList.Get(i));
   }
   dataReader->FinishRead();

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

 #ifdef WIN32
     //system("PAUSE");
 #endif






    return 0;
}
