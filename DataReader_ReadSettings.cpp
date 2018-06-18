
#include "DataReader.h"
#include "KReader.h"

#include "DataSettings.h"


void DataReader::ReadSettingsFile(KString filename)
{
 KReader reader;


 reader.OpenReadFile(filename);

 while(reader.HasNextLine())
 {
  KString line = reader.ReadNextLine();

  GList<KString> split = line.Split('=', 2);

  if (split.GetSize() == 2)
  {
   KString varName = split[0];
   KString val = split[1];

   if (varName == "blankdata")
   {
     DataSettings::NO_DATA = val;
   }
   else if (varName == "delimiter")
   {
     DataSettings::DELIMETER = val;
   }
   else if (varName == "endscreen")
   {
     GList<KString> splitScreen = val.Split(",");

     for (int i = 0; i < splitScreen.GetSize(); i++)
     {
      std::cout << "endscreen:" << splitScreen[i].c_str() << std::endl;
      DataSettings::lastScreenList.Add(splitScreen[i]);
     }

   }
   else if (varName == "combinefiles")
   {
    DataSettings::combineFiles = val.GetInt();
   }


  }

 }

 reader.CloseReadFile();









}
