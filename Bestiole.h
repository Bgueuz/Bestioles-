#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"

#include <iostream>
#include <vector>

using namespace std;


class Milieu;


class Bestiole
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

   std::vector<Bestiole>   listeVoisinsOmni;

   T               * couleur;

private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const Bestiole & b ) const;

   bool inRadiusVoisin( const Bestiole & b ) const;
   bool checkCollision( const Bestiole & b ) const;
   int getX();
   int getY();
   double getVitesse();
   double getOrientation();

   std::vector<Bestiole> getVoisins();

   void setVoisins(std::vector<Bestiole> listeVoisins);
   void setOrientation(double orient);
   void initCoords( int xLim, int yLim );
   bool collision();
   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );

};


#endif
