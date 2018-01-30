
#ifndef KTIME_FH
#define KTIME_FH 1

#include <ctime>


class KTime
{
 public:


  static std::ifstream readFile[GAMEENGINE_READ_FILE_MAX]; // read file stack for reading multiple files at the same time
  static int curReadFile;
  static char readFileDelimeter;

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


           return outDate;

  }


  static KString GetTime()
  {
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
            KString outDate = "";

           outDate.Add(((now->tm_hour)));
           outDate.Add("_");
           outDate.Add(((now->tm_min)));

           return outDate;

  }


};




#endif

