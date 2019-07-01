
#ifndef DATAREADER_FH
#define DATAREADER_FH 1

#include "main.h"

class DataFile;
class ExtraData;
class DataElement;


// data reader
// general class for reading in the data
// misc functions for reading/writing of all the data
// holds all info about read files within contents
// typically, only one of these needed for each program
// reads all survey data in path and sub directories

// holds a list of all data files found (dataFileList)
// the FIRST DataFile in dataFileList is a fake dataFile dedicated to holding all gameData's found outside individual survey data files
//     (game data can be combined with survey data or not)

// will output multiple files (one for each pack) with WriteSeparate()



class DataReader
{
 private:
  KString outputDir;
 public:
  DataReader(KString startPath);
  ~DataReader();

  KString path;


  void AddDataFile(KString filename);


  GList<DataFile*> dataFileList;

  GList<ExtraData*> extraDataList;







  GList<KString> headerList;


  static KString GetEndLine();

  

  KString GetOutDir();
  void SetOutDir(KString dir);



  void Read();

  void CalculateExtraData();

  void WriteAll();






  void WriteSeparate();




  void ReadDirectory(KString dirPath);



  static GList<KString> GetHeaderList(GList<DataFile*>* dataFileList);

  static void WriteDataFileList(GList<KString>* headerList, GList<DataFile*>* dataFileList, KWriter* writer);




  static void ReadSettingsFile(KString filename);


};



#endif
