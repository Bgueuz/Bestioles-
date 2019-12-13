// if needed
// #define _fileno fileno

#include "CImg.h"

#include "Aquarium.h"
#include "Milieu.h"
#include "ConcreteBestiole.h"
#include <iostream>

using namespace std;


int main()
{

    Aquarium       ecosysteme( 640, 480, 30 );

    for ( int i = 1; i <= 20; ++i )
    {

        // Determining the bestiole's behavior at random

        int random_int = rand() % 100; // between 0 and 99
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

        // Determining whether or not the bestiole has a fin

        // Determining whether or not the bestiole has an eye

        // Determining whether or not the bestiole has an ear

        // Determining whether or not the bestiole has camouflage

        // Determining whether or not the bestiole has a shell

        ecosysteme.getMilieu().addMember( ConcreteBestiole(random_behavior) );
    }

    ecosysteme.run();

    return 0;

}
