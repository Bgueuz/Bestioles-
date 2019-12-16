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

    for ( int i = 1; i <= 10; ++i )
    {

        // Determining the bestiole's behavior at random



        // Determining whether or not the bestiole has a fin

        // Determining whether or not the bestiole has an eye

        // Determining whether or not the bestiole has an ear

        // Determining whether or not the bestiole has camouflage

        // Determining whether or not the bestiole has a shell

        ecosysteme.getMilieu().addMember( ConcreteBestiole() );

        std::vector<ConcreteBestiole>   listeBestiolesimportante = ecosysteme.getMilieu().getListeBestioles();

        //ConcreteBestiole c = ConcreteBestiole();
        //cout << "HELLO" << c.getPersonality() <<endl;

    }

    ecosysteme.run();

    return 0;

}
