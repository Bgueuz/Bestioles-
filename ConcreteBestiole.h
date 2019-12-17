#ifndef _CONCRETEBESTIOLES_H_
#define _CONCRETEBESTIOLES_H_

#include "Personality.h"
#include "Bestiole.h"


#include "UImg.h"
#include <vector>
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

private :
    int               identite;
    int               x, y;
    double            cumulX, cumulY;
    double            orientation;
    double            vitesse;
    bool              schizophrene;
    Personality*      personality;
    int               type;
    std::vector<float>      oreilles; // tableau : rayon du cercle de détection, probabilité de détection
    std::vector<float>      yeux; // tableau : angle de vision, distance, probabilité

    T               * couleur;
    std::vector<ConcreteBestiole>   listeVoisinsOmni;
    list<ConcreteBestiole *>  Voisins;
    list<ConcreteBestiole *> Detectes;


private :
    void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
    ConcreteBestiole( void );                           // Constructeur par defaut
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

    Personality* getPersonality();
    void setPersonality(Personality* newPersonality);
    void setSchizophrene(bool s);
    void setType(int i);
    int getType();
    void setOreilles(float radius, float probability);
    void setYeux(float angle, float radius, float probability);

    bool inRadiusVoisin(const ConcreteBestiole & b) const;
    bool checkCollision(const ConcreteBestiole & b) const;

    int getX( void ) const { return x; };
    int getY( void ) const { return y; };
    double getVitesse( void ) const { return vitesse; };
    double getOrientation( void ) const { return orientation; };;
    std::vector<ConcreteBestiole> getVoisinsOmni( void ) const { return listeVoisinsOmni; };
    std::vector<float> getOreilles() {return oreilles;};
    std::vector<float> getYeux() {return yeux;};

    void setVoisins(std::vector<ConcreteBestiole> listeVoisins){listeVoisinsOmni = listeVoisins;};
    void setOrientation(double newOrientation){orientation = newOrientation;};
    void setVitesse(double newVitesse){vitesse = newVitesse;};
    void initCoords( int xLim, int yLim );
    void initPersonality();
    void randPersonality();

    friend bool operator==( const ConcreteBestiole & b1, const ConcreteBestiole & b2 );

};


#endif
