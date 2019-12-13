#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_
#include "UImg.h"
#include "Personality.h"

#include <iostream>
#include <list>

using namespace std;


class Milieu;


class Bestiole
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
   bool       yeux;
   bool        oreilles;


   T               * couleur;
   list<Bestiole *>  Voisins;
   list<Bestiole *> Detectes;


private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );
   list<Bestiole *> getVoisins();
   list<Bestiole *> getDetectes();

   bool jeTeVois( const Bestiole & b ) const;
    bool vu (const Bestiole & b);
   bool entendu (const Bestiole & b);


   void initCoords( int xLim, int yLim );

   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );

};


#endif
