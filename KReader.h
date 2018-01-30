
#ifndef KREADER_FH
#define KREADER_FH 1

#include "GList.h"

#define READ_FILE_MAX 10

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#include "dirent.h"



class KReader
{
 public:

   std::ifstream readFile[READ_FILE_MAX]; // read file stack for reading multiple files at the same time
   int curReadFile;
   char readFileDelimeter;





   KReader()
  {
   curReadFile = -1;
   readFileDelimeter = ',';
  }



bool OpenReadFile(KString filename)
{


/*
    if (resourceFile)
    {
     filename = mainDir + "/" + filename;
    }
    else
    {
        filename = outDir + "/" + filename;
    }*/
    if (curReadFile+1 >= READ_FILE_MAX)
    {
   //  MessageBox(KString("Could not open read file: %s! Too many files already open!",filename.c_str()));
     return false;
    }
    curReadFile++;
    readFile[curReadFile].open(filename.c_str(), std::ios::in);

    if (!readFile[curReadFile].is_open())
    {
        curReadFile--;
        //MessageBox(KString("Could not open read file: %s!",filename.c_str()));
       // ForceClose();
        return false;
    }

    return true;

}

void CloseReadFile()
{
    if (curReadFile < 0){return;}
    readFile[curReadFile].close();
    curReadFile--;
    if (curReadFile < 0){curReadFile = 0;}
}

KString ReadNextString()
{
    if (curReadFile < 0){return "";}
    std::string out;
    readFile[curReadFile] >> out;
    return KString(out.c_str());
}

KString ReadNextLine()
{
    if (curReadFile < 0){return "";}
    std::string ret = "";

    while (ret.size() == 0 && !readFile[curReadFile].eof())
    {
        ret = std::string("");
        if (!std::getline(readFile[curReadFile], ret)){break;}

    if (ret.size() > 0 && ret[ret.size()-1] == '\r')
    {
        ret.erase(ret.begin()+ret.size()-1);
    }


    }
    return KString(ret.c_str());
}

GList<KString> ReadNextLineSplit(char splitChar)
{
 KString line = ReadNextLine();
 GList<KString> retList = line.Split(splitChar);


 return retList;
}




int ReadNextInt()
{
    if (curReadFile < 0){return 0;}
    int out;
    readFile[curReadFile] >> out;
    return out;
}


bool HasNextLine()
{
    if (curReadFile < 0){return false;}
    return !readFile[curReadFile].eof();
}
























 static int IsDirectory(KString dir)
 {
   struct stat statbuf;
    if (stat(dir.c_str(), &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);

 }




 static GList<KString>* GetDirFiles(KString dirGet)
 {
   GList<KString>* outList = new GList<KString>();

   DIR *dir;
     struct dirent *ent;
      //c:\\
      // http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    if ((dir = opendir (dirGet.c_str())) != NULL) {
   /* print all the files and directories within directory */
   while ((ent = readdir (dir)) != NULL)
    {
     outList->Add(KString(ent->d_name));
   }
   closedir (dir);
    }


    return outList;


 }


};


  /*  std::ifstream KReader::readFile[READ_FILE_MAX]; // read file stack for reading multiple files at the same time
   int KReader::curReadFile = 0;
    char KReader::readFileDelimeter = ',';*/



#endif
