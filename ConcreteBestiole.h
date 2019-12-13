#ifndef _CONCRETEBESTIOLES_H_
#define _CONCRETEBESTIOLES_H_


#include "UImg.h"
#include "Bestiole.h"
#include "Personality.h"
#include <iostream>
#include <list>

using namespace std;


class Milieu;


class ConcreteBestiole : public Bestiole
{

private :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;
   static const double     LIMITE_OUIE;
   static int              next;
   bool                    schizophrene; // static ?
   Personality*            personality;


private :
   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   bool              yeux;
   bool              oreilles;


   T               * couleur;
   list<ConcreteBestiole *>  Voisins;
   list<ConcreteBestiole *> Detectes;


private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   ConcreteBestiole( void );                               // Constructeur par defaut
   ConcreteBestiole( const ConcreteBestiole & b );                 // Constructeur de copies
   ~ConcreteBestiole( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );
   list<ConcreteBestiole *> getVoisins();
   list<ConcreteBestiole *> getDetectes();


   bool jeTeVois( const ConcreteBestiole & b ) const;
   bool vu (const ConcreteBestiole & b);
   bool entendu (const ConcreteBestiole & b);

   void initCoords( int xLim, int yLim );

   friend bool operator==( const ConcreteBestiole & b1, const ConcreteBestiole & b2 );

};


#endif
