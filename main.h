
#ifndef MAIN_FH
#define MAIN_FH 1

#include "KString.h"
#include "GList.h"
#include "GMap.h"
#include "KReader.h"
#include "KWriter.h"

#ifndef MAKEDIR_FH
#define MAKEDIR_FH 1
void my_mkdir(const char* path);
#endif


#ifdef WIN32
#include <Direct.h>
#define change_directory _chdir
#define make_directory my_mkdir
#else
#include "unistd.h"

#define change_directory chdir
#define make_directory my_mkdir



#endif

#endif
