#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include <iostream>
#if defined(__MINGW32__)
#define __MSVCRT_VERSION__ 0x800
#define _WIN32_WINNT 0x0500
#endif
#include "CImg.h"

using namespace std;
using namespace cimg_library;

class Milieu;

class Aquarium : public CImgDisplay
{

private :
    Milieu       * flotte;

    int            delay;

public :
    Aquarium( int width, int height, int _delay );
    ~Aquarium( void );

    Milieu & getMilieu( void )
    {
        return *flotte;
    }

    void run( void );

};


#endif
