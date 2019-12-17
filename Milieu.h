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

        // Ajout d'une oreille à factoriser

        if (true) {//std::rand() % 2 == 0) { // 50% chance the bestiole has an ear

            float radius = 200.0;
            float probability = 0.6;

            listeBestioles.back().setOreilles(radius, probability);


            std::cout << listeBestioles.back().getOreilles()[0] << endl;


            //cout << "wesh " << *listeBestioles.back().getOreilles()[0] << endl;
            //listeBestioles.back().setYeux(rand() )/RAND_MAX*2.*M_PI, 30, 0.6);

        }

    }


    int nbVoisins( const ConcreteBestiole & b );
    void detection ();
    void updateVoisins(ConcreteBestiole & b);
    void collisionsAll();

};


#endif
