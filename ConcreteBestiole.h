#ifndef _CONCRETEBESTIOLES_H_
#define _CONCRETEBESTIOLES_H_


#include "UImg.h"
#include <vector>
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
    bool                    schizophrene;
    Personality*            personality;
    int                dureedevie;
    int                      vecu;
    bool                      tue;

private :
    int               identite;
    int               x, y;
    double            cumulX, cumulY;
    double            orientation;
    double            vitesse;
    bool              yeux;
    bool              oreilles;

    T               * couleur;
    std::vector<ConcreteBestiole>   listeVoisinsOmni;
    list<ConcreteBestiole *>  Voisins;
    list<ConcreteBestiole *> Detectes;


private :
    void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
    ConcreteBestiole( void );                           // Constructeur par defaut
    ConcreteBestiole( const ConcreteBestiole & b );                 // Constructeur de copies
    ~ConcreteBestiole( void );  
                            // Destructeur
    // Operateur d'affectation binaire par defaut
    void Clonage1(const ConcreteBestiole & b, int xLim);
    void Clonage2(const ConcreteBestiole & b, int yLim);
    void action( Milieu & monMilieu );
    void draw( UImg & support );
    list<ConcreteBestiole *> getVoisins();
    list<ConcreteBestiole *> getDetectes();


    bool jeTeVois( const ConcreteBestiole & b ) const;
    bool vu (const ConcreteBestiole & b);
    bool entendu (const ConcreteBestiole & b);

    Personality* getPersonality();
    void setPersonality(Personality* newPersonality);
    void setSchizophrene(bool s);

    bool inRadiusVoisin(const ConcreteBestiole & b) const;
    bool checkCollision(const ConcreteBestiole & b) const;

    int getX( void ) const { return x; };
    int getY( void ) const { return y; };
    double getVitesse( void ) const { return vitesse; };
    double getOrientation( void ) const { return orientation; };;
    std::vector<ConcreteBestiole> getVoisinsOmni( void ) const { return listeVoisinsOmni; };
    bool getTue( void ) const { return tue; };
    int getID( void ) const { return identite; };
    int getVecu( void ) const { return vecu; };
    int getDureeDeVie( void ) const { return dureedevie; };

    void Kill(void);
  
    void setVoisins(std::vector<ConcreteBestiole> listeVoisins){listeVoisinsOmni = listeVoisins;};
    void setOrientation(double newOrientation){orientation = newOrientation;};
    void vie();
    void initCoords( int xLim, int yLim );

    friend bool operator==( const ConcreteBestiole & b1, const ConcreteBestiole & b2 );

};


#endif
