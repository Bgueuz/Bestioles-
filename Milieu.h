#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include <iostream>
#include <vector>
#include "ConcreteBestiole.h"

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

    int getWidth( void ) const
    {
        return width;
    };
    int getHeight( void ) const
    {
        return height;
    };

    void step( void );
    std::vector<ConcreteBestiole> getBestioles( void ) const { return listeBestioles; };

    void addMember( const ConcreteBestiole & b )
    {
        listeBestioles.push_back(b);
        listeBestioles.back().initCoords(width, height);
        listeBestioles.back().initPersonality();

        // Ajout d'une oreille
        listeBestioles.back().initOreilles();

        // Accessoires
        listeBestioles.back().setAccesories(this);

        cout << "bestiole :" << listeBestioles.back().getIdentite() << endl;
        cout << "   cette bestiole à un camouflage de " << listeBestioles.back().getCamouflage() << endl;
        cout << "   cette bestiole à des nageoires de " << listeBestioles.back().getNageoire() << endl;
        cout << "   cette bestiole à une carapace " << endl;
        cout << "       qui réduit les dommages de  " << listeBestioles.back().getCarapaceDom() << endl;
        cout << "       qui réduit la vitesse de  " << listeBestioles.back().getCarapaceVit() << endl;

    }

    int nbVoisins( const ConcreteBestiole & b );
    void detection ();
    void updateVoisins(ConcreteBestiole & b);
    void collisionsAll();

    //Accesoires
public:
        // Camouflage
    void setCamouflageLimits(float max_cam, float min_cam);
    float getMaxCam(){return MAX_CAMO;};
    float getMinCam(){return MIN_CAMO;};

        // Nageoire
    void setNageoireLimits(float max_nage, float min_nage);
    float getMaxNage(){return MAX_NAGE;};
    float getMinNage(){return MIN_NAGE;};

        // Carapace - Dommage
    void setCaraDomLimits(float max_cara_dom, float min_cara_dom);
    float getMaxCaraDom(){return MAX_CARA_DOM;};
    float getMinCaraDom(){return MIN_CARA_DOM;};

        // Carapace - Vitesse
    void setCaraVitLimits(float max_cara_vit, float min_cara_vit);
    float getMaxCaraVit(){return MAX_CARA_VIT;};
    float getMinCaraVit(){return MIN_CARA_VIT;};

private:
    // Camouflage
    float MAX_CAMO = 1.0;
    float MIN_CAMO = 0.0;

    // Nageoire
    float MAX_NAGE = 2.0;
    float MIN_NAGE = 1.0;

    // Carapace
        // Reduction Dommages subit / chances de mourir à l'impact
    float MAX_CARA_DOM = 4.0;
    float MIN_CARA_DOM = 1.0;

            // Reduction Vitesse
    float MAX_CARA_VIT = 3.0;
    float MIN_CARA_VIT = 1.0;

};


#endif
