#include "PrevoyantePersonality.h"
#include <iostream>
#include "ConcreteBestiole.h"


void PrevoyantePersonality::newAction()
{
}

void PrevoyantePersonality::newAction(ConcreteBestiole * b)
{
    std::cout << "JE SUIS PR AVEC VITESSE " << b->getVitesse() << std::endl;
}

