#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "ConcreteBestiole.h"

#include <iostream>
#include <vector>

using namespace std;


class Milieu : public UImg
{

private :
   static const T          white[];

   int                     width, height;
   std::vector<ConcreteBestiole>   listeBestioles;

public :
   Milieu( int _width, int _height );
   ~Milieu( void );

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );

   void addMember( const ConcreteBestiole & b ) { listeBestioles.push_back(b); listeBestioles.back().initCoords(width, height); }
   int nbVoisins( const ConcreteBestiole & b );
   void detection ();

};


#endif
