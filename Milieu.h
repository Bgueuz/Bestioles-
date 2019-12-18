#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "ConcreteBestiole.h"
#include "GregairePersonality.h"
#include "PeureusePersonality.h"
#include "KamikazePersonality.h"
#include "PrevoyantePersonality.h"

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

        // Determining the bestiole's behavior at random

        int random_int = std::rand() % 100; // between 0 and 99
        int random_behavior;
        if (random_int < 20)
            random_behavior = 1;
        else if (random_int < 40)
            random_behavior = 2;
        else if (random_int < 60)
            random_behavior = 3;
        else if (random_int < 80)
            random_behavior = 4;
        else
            random_behavior = 5;

        switch (random_behavior)
        {
        case 1: // grégaire
        {
            listeBestioles.back().setSchizophrene(false);
            listeBestioles.back().setPersonality(new GregairePersonality());
        }
        break;
        case 2: // peureuse
        {
            listeBestioles.back().setSchizophrene(false);
            listeBestioles.back().setPersonality(new PeureusePersonality());
        }
        break;
        case 3: // kamikaze
        {
            listeBestioles.back().setSchizophrene(false);
            listeBestioles.back().setPersonality(new KamikazePersonality());
        }
        break;
        case 4: // prévoyante
        {
            listeBestioles.back().setSchizophrene(false);
            listeBestioles.back().setPersonality(new PrevoyantePersonality());
        }
        break;
        case 5: // personnalités multiples
        {
            listeBestioles.back().setSchizophrene(true);
            listeBestioles.back().setPersonality(NULL);
        }
        break;

        default:
            listeBestioles.back().setSchizophrene(false);
            listeBestioles.back().setPersonality(new GregairePersonality());
        }

        // Accesoires

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
