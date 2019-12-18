#include "PrevoyantePersonality.h"
#include "ConcreteBestiole.h"

#include <iostream>

void PrevoyantePersonality::newAction(ConcreteBestiole * b)
{

    std::vector<ConcreteBestiole> VoisinsOmni = b->getVoisinsOmni();
    std::vector<int> detected = b->detectVoisins();

    for (std::vector<int>::iterator it = detected.begin() ; it != detected.end(); ++it)
    {

        std::vector<int> prevoyanteFC = b->simuleBouge();  //FC = FutureCoord
        std::vector<int> voisinFC = VoisinsOmni[*it].simuleBouge();

        // Check future collision
        double minRadius = VoisinsOmni[*it].getAffSize() + b->getAffSize()-4;
        double dist = std::sqrt( (voisinFC[0]-prevoyanteFC[0])*(voisinFC[0]-prevoyanteFC[0]) + (voisinFC[1]-prevoyanteFC[1])*(voisinFC[1]-prevoyanteFC[1]) );

        if ( dist <= minRadius)   // si vrai, il y aura collision
        {
            double newOrientation = M_PI + atan2( b->getY()-voisinFC[1], voisinFC[0]-b->getX() );
            b->setOrientation(newOrientation);
            break;
        }
    }
}
