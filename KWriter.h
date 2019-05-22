
#ifndef KWRITER_FH
#define KWRITER_FH 1

#include <fstream>

#include <ctime>

class KWriter
{
 public:

  KWriter()
  {
   readFileDelimeter = ' ';
  }

  char readFileDelimeter;

  std::ofstream writeFile;


  void OpenWriteFile(KString filename, bool append)
{
  //  filename = KString("%s");

    std::ios_base::openmode flags = std::ios::out;

    if (append)
    {
        flags = flags | std::ios::app;
    }
    else
    {
        flags = flags | std::ios::trunc;
    }
    writeFile.open(filename.c_str(), flags);
  //  if (!writeFile.is_open()){Message(KString("Could not open write file: %s!",filename.c_str()));}

}



void WriteFile(int d, bool space)
{
    writeFile << d;
    if (space){writeFile << readFileDelimeter;}
}
void WriteFile(KString str, bool space = false)
{
    writeFile << str.c_str();
    if (space){writeFile << readFileDelimeter;}
}
void CloseWriteFile()
{
    writeFile.close();
}



static KString GetEndLine()
 {
     KString r = KString::GetLineBreak();//KString("%c", 0x0d);
     return r;
 }



static KString GetDate()
{
 time_t t = time(0);   // get time now
           struct tm * now = localtime( & t );
            KString outDate = "";

           outDate.Add((now->tm_year + 1900));
           outDate.Add("_");
           outDate.Add(((now->tm_mon + 1)));
           outDate.Add("_");
           outDate.Add(((now->tm_mday)));
           outDate.Add("_");
           outDate.Add(((now->tm_hour)));
           outDate.Add("_");
           outDate.Add(((now->tm_min)));


          return outDate;

}












};

#endif
