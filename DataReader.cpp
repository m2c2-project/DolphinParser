
#include "DataReader.h"

#include "Data.h"

#include "DataFile.h"


using namespace std;

  DataReader::DataReader()
  {

    outputDir = "out";

     DataFile* gameFile = new DataFile(""); // create file to store all game data from outside sources (separate folders)
   dataFileList.Add(gameFile);
  }

  DataReader::~DataReader()
  {

  }

  KString DataReader::GetEndLine()
{
  return KString::GetLineBreak();
}


 void DataReader::AddDataFile(KString filename)
 {
   // filename should be full path of data file
  dataFileList.Add(new DataFile(filename));

 }



  void DataReader::Read(KString path)
  {
   // read the files of the root path and add them to the file list
   ReadDirectory(path);
  }

  void DataReader::FinishRead()
  {
       // read all the files found

   for (int i = 0; i < dataFileList.GetSize(); i++)
   {
    dataFileList[i]->Read();
   }



   headerList = GetHeaderList(&dataFileList);




   for (int i = 0; i < headerList.GetSize(); i++)
   {
     cout << headerList[i].c_str() << KString::GetLineBreak().c_str();
   }

  }



  // gets the header list and creates the table lines for that list for each dataFile
  GList<KString> DataReader::GetHeaderList(GList<DataFile*>* dataFileList)
  {
   GList<KString> headerList;

   // go through and find all variable names for table headers
   for (int i = 0; i < dataFileList->GetSize(); i++)
   {
    for (int j = 0; j < dataFileList->Get(i)->elementList.GetSize(); j++)
    {
     KString varName = dataFileList->Get(i)->elementList[j]->name;
     if (!headerList.Contains(varName))
     {
      headerList.Add(varName);
     }
    }
   }

     // create table lines

   for (int i = 0; i < dataFileList->GetSize(); i++)
   {
    dataFileList->Get(i)->MakeTableLine(&headerList);
   }


   return headerList;


  }



  KString DataReader::GetOutDir()
  {
      KString date = KWriter::GetDate();

      KString rOutDir = outputDir;

      rOutDir.Add("/out_");

      rOutDir.Add(date);

      return rOutDir;
  }


  void DataReader::SetOutDir(KString dir)
  {
      outputDir = dir;

  }





