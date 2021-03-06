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
    ecosysteme.getMilieu().setCamouflageLimits(0.3,0.75);
    ecosysteme.getMilieu().setNageoireLimits(1.0,2.0);
    ecosysteme.getMilieu().setCaraDomLimits(1.0,2.0);
    ecosysteme.getMilieu().setCaraVitLimits(1.0,2.0);

    // Générations des bestioles initiales
    for ( int i = 1; i <= 25; ++i )
    {
        ecosysteme.getMilieu().addMember(ConcreteBestiole());
        ecosysteme.getMilieu().updateRatiosPresents();
    }

    ecosysteme.run();

    return 0;

}
