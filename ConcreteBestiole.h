#ifndef _CONCRETEBESTIOLES_H_
#define _CONCRETEBESTIOLES_H_

#include "Personality.h"
#include "Bestiole.h"


#include "UImg.h"
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>

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
    Personality*      personality;
    int               type;  // 0,1,2,3,4  pour grégaire,peureuse,kamikaze,prévoyante,personnalités multiples
    std::vector<float>      oreilles; // tableau : rayon du cercle de détection, probabilité de détection
    std::vector<float>      yeux; // tableau : angle de vision, distance, probabilité

    // Camouflage
    static double     max_cam;
    static double     min_cam;
    float camouflage = 0;

    // Nageoire
    static double     max_nage;
    static double     min_nage;
    float nageoire = 1.0;

    // Carapace_dom
    static double     max_cara_dom;
    static double     min_cara_dom;
    float carapaceDommage = 1.0;

    // Carapace vitesse
    static double     max_cara_vit;
    static double     min_cara_vit;
    float carapaceVitesse = 1.0;

    int                dureedevie = std::rand() % 100;
    int                      vecu = 0;
    bool                      tue = false;
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

    bool inRadiusVoisin(const ConcreteBestiole & b) const;
    bool checkCollision(const ConcreteBestiole & b) const;
    void randPersonality();
    void changeColorToType();
    std::vector<int> detectVoisins();
    bool jeTeVois( const ConcreteBestiole & b ) const;
    std::vector<int> simuleBouge(  );
    void Kill(void);
    void vie();
    float RandomFloat(float a, float b);

    // Initialisations
    void initCoords( int xLim, int yLim );
    void initPersonality(Milieu* milieu,float ratiosCherches[5],float ratiosPresents[5]);
    void initOreilles(Milieu* flotte);
    void initYeux(Milieu* flotte);

    // Setters
    void setOreilles(float radius, float probability);
    void setYeux(float angle, float radius, float probability);
    void setPersonality(Personality* newPersonality);
    void setType(int i);
    void setVoisins(std::vector<ConcreteBestiole> listeVoisins)
    {
        listeVoisinsOmni = listeVoisins;
    };
    void setOrientation(double newOrientation)
    {
        orientation = newOrientation;
    };
    void setVitesse(double newVitesse)
    {
        vitesse = newVitesse;
    };
    void setCamouflage(float min_cam,float max_cam);
    void setAccesories(Milieu* flotte);
    void setNageoire(float min_nage,float max_nage);
    void setCarapaceDom(float min_cara_dom,float max_cara_dom);
    void setCarapaceVit(float min_cara_vit,float max_cara_vit);

    // Getters
    int getX( void ) const
    {
        return x;
    };
    int getY( void ) const
    {
        return y;
    };
    Personality* getPersonality();
    int getType();
    double getVitesse( void ) const
    {
        return vitesse;
    };
    int getIdentite( void ) const
    {
        return identite;
    };
    double getOrientation( void ) const
    {
        return orientation;
    };
    std::vector<ConcreteBestiole> getVoisinsOmni( void ) const
    {
        return listeVoisinsOmni;
    };
    std::vector<float> getOreilles()
    {
        return oreilles;
    };
    std::vector<float> getYeux()
    {
        return yeux;
    };
    const double getAffSize()
    {
        return AFF_SIZE;
    };
    float getCamouflage()
    {
        return camouflage;
    };
    float getNageoire()
    {
        return nageoire;
    };
    float getCarapaceDom()
    {
        return carapaceDommage;
    };
    float getCarapaceVit()
    {
        return carapaceVitesse;
    };
    bool getTue( void ) const
    {
        return tue;
    };
    int getID( void ) const
    {
        return identite;
    };
    int getVecu( void ) const
    {
        return vecu;
    };
    int getDureeDeVie( void ) const
    {
        return dureedevie;
    };

    //Operators
    friend bool operator==( const ConcreteBestiole & b1, const ConcreteBestiole & b2 );

};


#endif
