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




private :
    int               identite;
    int               x, y;
    double            cumulX, cumulY;
    double            orientation;
    double            vitesse;
    bool              yeux;
    bool              oreilles;

private:

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

    bool inRadiusVoisin(const ConcreteBestiole & b) const;
    bool checkCollision(const ConcreteBestiole & b) const;

    int getX( void ) const { return x; };
    int getY( void ) const { return y; };
    double getVitesse( void ) const { return vitesse; };
    int getIdentite( void ) const { return identite; };
    double getOrientation( void ) const { return orientation; };;
    std::vector<ConcreteBestiole> getVoisinsOmni( void ) const { return listeVoisinsOmni; };

    void setVoisins(std::vector<ConcreteBestiole> listeVoisins){listeVoisinsOmni = listeVoisins;};
    void setOrientation(double newOrientation){orientation = newOrientation;};

    void initCoords( int xLim, int yLim );

    friend bool operator==( const ConcreteBestiole & b1, const ConcreteBestiole & b2 );

// Accesoires
private :
        // Camouflage
    static double     max_cam;
    static double     min_cam;
    float camouflage = 0;

        // Nageoire
    static double     max_nage;
    static double     min_nage;
    float nageoire = 1;

        // Carapace_dom
    static double     max_cara_dom;
    static double     min_cara_dom;
    float carapaceDommage = 1.0;

        // Carapce vitesse
    static double     max_cara_vit;
    static double     min_cara_vit;
    float carapaceVitesse = 1.0;

public :

    void setAccesories(Milieu* flotte);
        // Camouflage
    void setCamouflage(float min_cam,float max_cam);
    float getCamouflage(){return camouflage;};

        // Nageoire
    void setNageoire(float min_nage,float max_nage);
    float getNageoire(){return nageoire;};

        // Carapace Dommages
    void setCarapaceDom(float min_cara_dom,float max_cara_dom);
    float getCarapaceDom(){return carapaceDommage;};

            // Carapace Vitesse
    void setCarapaceVit(float min_cara_vit,float max_cara_vit);
    float getCarapaceVit(){return carapaceVitesse;};

    // Utile --> pourrait faire partie d'une interface
    float RandomFloat(float a, float b);

};


#endif
