#ifndef _UIMG_H_
#define _UIMG_H_


#if defined(__MINGW32__)
#define __MSVCRT_VERSION__ 0x800
#define _WIN32_WINNT 0x0500
#endif
#include "CImg.h"

using namespace cimg_library;


typedef unsigned char      T;
typedef CImg<T>            UImg;

#endif
