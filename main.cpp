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

    // Limites de la simulation
    ecosysteme.getMilieu().setCamouflageLimits(0.3,0.95);
    ecosysteme.getMilieu().setNageoireLimits(1.0,3.0);
    ecosysteme.getMilieu().setCaraDomLimits(1.0,6.0);
    ecosysteme.getMilieu().setCaraVitLimits(1.0,2.0);

    for ( int i = 1; i <= 20; ++i )
    {

        ecosysteme.getMilieu().addMember(ConcreteBestiole());

    }

    ecosysteme.run();

    return 0;

}
