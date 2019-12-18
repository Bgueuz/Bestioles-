#include "GregairePersonality.h"
#include "ConcreteBestiole.h"

#include <iostream>

void GregairePersonality::newAction(ConcreteBestiole * b)
{
    std::vector<ConcreteBestiole> VoisinsOmni = b->getVoisinsOmni();
    double sumOrientation = 0;
    int i=0;
    std::vector<int> detected = b->detectVoisins();

    for (std::vector<int>::iterator it = detected.begin() ; it != detected.end(); ++it)
    {
        sumOrientation += VoisinsOmni[*it].getOrientation();
        i++;
    }

    if (i != 0)   // if there's at least one candidate
    {
        b->setOrientation(sumOrientation/i);
    }
}
