
#ifndef KSTRING_H
#define KSTRING_H 1

#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include "GList.h"
#include <cctype>

#define MAX_KSTRING_CHAR 4096*10


class KString
{
  public:

    KString()
    {
      str = "";
    }

    KString(std::string sstr)
    {
      str = std::string(sstr);
    }

    KString(char sstr[MAX_KSTRING_CHAR])
    {
      str = std::string(sstr);
    }

    KString(const  KString& sstr)
    {
     str = std::string(sstr.str.c_str());
    }

    KString(const char *fmt, ...)
    {

        char text[MAX_KSTRING_CHAR];
     va_list	ap;

     if (fmt == NULL)
      {return;}

     va_start(ap, fmt);
         vsprintf(text, fmt, ap);
     va_end(ap);


     str = std::string(text);


    }


    const char* c_str()
    {
     return str.c_str();
    }


    std::string str;

    void Set(std::string set)
    {
     str = set;
    }

    void Add(KString otherStr)
    {
        char addStr[MAX_KSTRING_CHAR];
        sprintf(addStr, "%s%s", str.c_str(), otherStr.str.c_str());
        str = std::string(addStr);
    }

    void Add(char c)
    {
       char addStr[MAX_KSTRING_CHAR];
       sprintf(addStr, "%s%c", str.c_str(), c);
       str = addStr;
    }

    void Add(int i)
    {
       char addStr[MAX_KSTRING_CHAR];
       sprintf(addStr, "%s%d", str.c_str(), i);
       str = addStr;
    }

    void Add(float f)
    {
       char addStr[MAX_KSTRING_CHAR];
       sprintf(addStr, "%s%f", str.c_str(), f);
       str = addStr;
    }

    KString SubString(int start, int end)
    {
      KString sub = str.substr(start, end-start);
      return sub;
    }

    bool Contains(char c)
    {
     return str.find(c) != std::string::npos;
    }

    bool Contains(KString oStr)
    {
     return str.find(oStr.c_str()) != std::string::npos;
    }

    int GetInt()
    {
     return std::atoi(str.c_str());
    }

    bool IsInt()
    {
     for (int i = 0; i < GetSize(); i++)
     {
      if (!std::isdigit(str[i])){return false;}
     }
     return true;
    }




    int GetSize()
    {
     return str.size();
    }

    void Remove(int i)
    {
     str.erase(str.begin()+i);
    }

    void RemoveAllChar(char c)
    {
   //  str.erase(std::remove(str.begin(), str.end(), c), str.end());
     for (int i = 0; i < GetSize(); i++)
     {
      if (str[i] == c)
      {
       Remove(i);
       i--;
      }
     }
    }

    bool Equals(KString str)
    {
     if (strcmp(c_str(), str.c_str()) == 0){return true;}
     else {return false;}
    }

    GList<KString> Split(char splitChar, int maxSplit = 0, char ignoreOpen = '{', char ignoreClose = '}')
    {
      return Split(KString("%c", splitChar), maxSplit, ignoreOpen, ignoreClose);

    }

    GList<KString> Split(KString splitStr, int maxSplit = 0, char ignoreOpen = '{', char ignoreClose = '}')
    {
     GList<KString> retList;

     std::string str = std::string(c_str());


     int lastC = 0;
     unsigned int c = 0;

     int ignoreLayer = 0;
     int nextMatch = str.find(splitStr.c_str());

     while (c != std::string::npos && c != -1 && c < str.length())
     {
      if (c > nextMatch)
      {
         nextMatch = str.find(splitStr.c_str(), c);
      }

      if (str.c_str()[c] == ignoreOpen)
      {
       ignoreLayer++;
      }
      else if (str.c_str()[c] == ignoreClose)
      {
       ignoreLayer--;
      }

      if (ignoreLayer > 0)
      {
        c++;
        continue;
      }

      if (c == nextMatch)
      {

       if (maxSplit > 0 && retList.GetSize() >= maxSplit-1)
       {
        // if the max number of split groups is met, break and return the remaining values in the last element of the list
        // ex: a string "1:2:3" split at character ':' with maxSplit=2 should return list: {"1","2:3"}
        break;
       }

       retList.Add(KString(str.substr(lastC, c-lastC).c_str()));
       lastC = c + splitStr.GetSize();
       c = lastC;
       nextMatch = str.find(splitStr.c_str(),lastC);

      }
      else
      {
       c++;
      }

     }
     retList.Add(KString(str.substr(lastC, str.size()-lastC).c_str()));


     return retList;

    }




    int Find(char c, int start = 0)
    {
     int pos = str.find_first_of(c, start);
     // returns -1 if not found
     return pos;
    }

    // replaces every instance of src in the string with rep
    bool Replace(KString src, KString rep) // returns true when a replacement was made
    {
     bool ret = false;
     size_t loc = str.find(src.c_str());
     while (loc != std::string::npos)
     {
      ret = true;
      str.replace(loc, src.GetSize(), rep.c_str());

      loc = str.find(src.c_str(), loc+1);
     }

     return ret;
    }














     char operator[]( int i )
     {
       return str.c_str()[i];
     }

     bool operator== (KString other)
     {
      return  (std::strcmp(str.c_str(), other.str.c_str()) == 0);
     }

     bool operator!= (KString other)
     {
      return  (std::strcmp(str.c_str(), other.str.c_str()) != 0);
     }





     static bool IsLetter(char c)
     {
      if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
      {
       return true;
      }
      return false;
     }


     static bool IsNumber(char c)
     {
      if (c >= '0' && c <= '9')
      {
       return true;
      }
      return false;
     }


     static KString ToLower(KString kstr)
     {
       KString outStr = "";
       std::string* str = &kstr.str;
       for (int i = 0; i < str->size(); i++)
       {
        outStr.Add(((char)tolower((*str)[i])));
       }

       return outStr;
     }
















     static KString GetLineBreak()
     {
       KString r = "";
       //r.Add(((char) (0x0d)));
       r.Add((char) (0x0a));

       return  r;

     }







};









#endif // KSTRING_H


