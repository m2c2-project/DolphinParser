
#ifndef MAIN_FH
#define MAIN_FH 1

#include "KString.h"
#include "GList.h"
#include "GMap.h"
#include "KReader.h"
#include "KWriter.h"


#ifdef WIN32
#include <Direct.h>
#define change_directory _chdir
#define make_directory _mkdir
#else
#include "unistd.h"
#define change_directory chdir
#define make_directory mkdir
#endif

#endif
