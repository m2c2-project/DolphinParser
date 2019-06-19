
#include "DataReader.h"
#include "KReader.h"

#include "DataSettings.h"


void DataReader::ReadSettingsFile(KString filename)
{


 size_t mynpos = -1;
 std::cout << "mynpos:" << mynpos << std::endl;

 std::cout << "npos:" << std::string::npos << std::endl;
 std::cout << "reading settings file 1\n";
 
 std::cout << "size of npos:" << sizeof(std::string::npos) << std::endl;
std::cout << "size of mynpos:" << sizeof(mynpos) << std::endl;

 KReader reader;
std::cout << "reading settings file 2\n";

 reader.OpenReadFile(filename);
 std::cout << "reading settings file 3\n";
 

 while(reader.HasNextLine())
 {
 
 std::cout << "reading settings file 3.5\n";
  KString line = reader.ReadNextLine();
  
  std::cout << "reading settings file 4:" << line.c_str() << "\n";
  
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
   
    std::cout << "end screen 1:" << val.c_str() << "\n";
     GList<KString> splitScreen = val.Split(",");
std::cout << "end screen 1.5\n";
     for (int i = 0; i < splitScreen.GetSize(); i++)
     {
      std::cout << "endscreen 2\n";
      //std::cout << "endscreen:" << splitScreen[i].c_str() << std::endl;
      DataSettings::lastScreenList.Add(splitScreen[i]);
     }

   }
   else if (varName == "combinefiles")
   {
    DataSettings::combineFiles = val.GetInt();
   }
   else if (varName == "gamenamesplit") // index in the raw game data file that the parser pulls the game name. typically 3.
   {
     //sometimes 4 was used in the newer files but that was changed back

     DataSettings::gameNameSplitIndex = val.GetInt();
   }
   else if (varName == "packid_varname") // the variable name in the raw session/survey data files that has the pack ID
   {
     // originally was "Pack" in the newer files it is now "Pack_ID"

     DataSettings::packidVarName = KString(val);
   }


  }

 }
 
  std::cout << "reading settings file 10";

 reader.CloseReadFile();





 std::cout << "reading settings file 2\n";



}
