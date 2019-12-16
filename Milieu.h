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

    std::vector<ConcreteBestiole> getListeBestioles( void ) const
    {
        return listeBestioles;
    };

    void step( void );

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


    }
    int nbVoisins( const ConcreteBestiole & b );
    void detection ();

};


#endif
