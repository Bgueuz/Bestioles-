#include "KamikazePersonality.h"
#include "ConcreteBestiole.h"

#include <iostream>

void KamikazePersonality::newAction(ConcreteBestiole * b)
{
    std::vector<ConcreteBestiole> VoisinsOmni = b->getVoisinsOmni();

    double minDistance = std::numeric_limits<double>::infinity();
    int currIndex = 0;
    int minIndex = -1;

    std::vector<int> detected = b->detectVoisins();

    for (std::vector<int>::iterator it = detected.begin() ; it != detected.end(); ++it)
        {

        double dist = std::sqrt( (VoisinsOmni[*it].getX()-b->getX())*(VoisinsOmni[*it].getX()-b->getX()) + (VoisinsOmni[*it].getY()-b->getY())*(VoisinsOmni[*it].getY()-b->getY()) );
        if (dist < minDistance)
        {
            minDistance = dist;
            minIndex = currIndex;
        }
    }

    if (minIndex !=-1)   // if there's at least one candidate, we turn towards them
    {
        double newOrientation = atan2(-VoisinsOmni[minIndex].getY() + b->getY(), VoisinsOmni[minIndex].getX()-b->getX() );
        b->setOrientation(newOrientation);
    }
}
