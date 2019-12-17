#include "PeureusePersonality.h"
#include <iostream>
#include "ConcreteBestiole.h"


void PeureusePersonality::newAction()
{

}

void PeureusePersonality::newAction(ConcreteBestiole * b)
{
    std::cout << "JE SUIS PE AVEC VITESSE " << b->getVitesse() << std::endl;
}
