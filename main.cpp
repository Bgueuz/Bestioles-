

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
        ecosysteme.getMilieu().addMember( ConcreteBestiole() );
    ecosysteme.run();


    return 0;

}
