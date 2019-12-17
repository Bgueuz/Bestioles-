
#include "KamikazePersonality.h"
#include "ConcreteBestiole.h"
#include <iostream>

void KamikazePersonality::newAction()
{
}


void KamikazePersonality::newAction(ConcreteBestiole * b)
{
    std::cout << "JE SUIS K AVEC VITESSE " << b->getVitesse() << std::endl;
}
