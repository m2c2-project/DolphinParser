


#include "DataReader.h"

#include "Data.h"

#include "KWriter.h"

#include "DataFile.h"



using namespace std;

  void DataReader::CalculateExtraData()
  {

   for (int i = 0; i < dataFileList.GetSize(); i++)
   {
    ExtraData* extraData = NULL;
    // find out if extra data with id already exists
    for (int j = 0; j < extraDataList.GetSize(); j++)
    {
     if (extraDataList[j]->ID == dataFileList[i]->ID)
     {
      extraData = extraDataList[j];
      break;
     }
    }

    // no extra data found. create new and add to list
    if (extraData == NULL)
    {
     extraData = new ExtraData(dataFileList[i]->ID);
     extraDataList.Add(extraData);
    }

    // add all info
    extraData->AddSurvey(dataFileList[i]->surveyComplete, dataFileList[i]->sessionID, dataFileList[i]->packName);



   }

   std::cout << " calc extra data complete" << std::endl;

   KWriter writer;

   KString date = KWriter::GetDate();

   KString outDir = GetOutDir();


   KString sCommand = KString("mkdir %s", outDir.c_str());

   system(sCommand.c_str());



    writer.OpenWriteFile(KString("%s\\extraInfo_%s.txt", outDir.c_str(),  date.c_str()), false);

    cout << "write extra files" << endl;


    for (int i = 0; i < extraDataList.GetSize(); i++)
    {
     //cout << "write extra: " << i << endl;
     writer.WriteFile(KString("%s, complete surveys: %d,", extraDataList[i]->ID.c_str(), extraDataList[i]->surveysComplete));

     GMap<KString, int>* packMap = &(extraDataList[i]->completePackCount);
     for (int j = 0; j < packMap->keyList.GetSize(); j++)
     {
      KString key = packMap->keyList[j];
      writer.WriteFile(KString("%s: %d", key.c_str(), packMap->Get(key)));

      if (j < packMap->keyList.GetSize()-1){writer.WriteFile(",");}

     }



     if (i < extraDataList.GetSize()-1){ writer.WriteFile(KWriter::GetEndLine());}

    }


    writer.CloseWriteFile();








  }
