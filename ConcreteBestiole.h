#ifndef _CONCRETEBESTIOLES_H_
#define _CONCRETEBESTIOLES_H_


#include "UImg.h"
#include "Bestiole.h"
#include <iostream>

using namespace std;


class Milieu;


class ConcreteBestiole : public Bestiole
{

private :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;

   static int              next;

private :
   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;

   T               * couleur;

private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   ConcreteBestiole( void );                               // Constructeur par defaut
   ConcreteBestiole( const ConcreteBestiole & b );                 // Constructeur de copies
   ~ConcreteBestiole( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const ConcreteBestiole & b ) const;

   void initCoords( int xLim, int yLim );

   friend bool operator==( const ConcreteBestiole & b1, const ConcreteBestiole & b2 );

};


#endif
