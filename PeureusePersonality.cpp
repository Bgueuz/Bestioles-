#include "PeureusePersonality.h"
#include <iostream>
#include "ConcreteBestiole.h"


void PeureusePersonality::newAction()
{

}

void PeureusePersonality::newAction(ConcreteBestiole * b)
{
        std::vector<ConcreteBestiole> VoisinsOmni = b->getVoisinsOmni();

    double minDistance = std::numeric_limits<double>::infinity();
    int currIndex = 0;
    int minIndex = -1;

    for ( std::vector<ConcreteBestiole>::iterator it2 = VoisinsOmni.begin() ; it2 != VoisinsOmni.end() ; ++it2 )
    {
        double dist = std::sqrt( (it2->getX()-b->getX())*(it2->getX()-b->getX()) + (it2->getY()-b->getY())*(it2->getY()-b->getY()) );

        bool isInHearingDistance = ( dist <= b->getOreilles()[0] ) ;

        if (isInHearingDistance)   // on ignore le camouflage
        {

            if (dist < minDistance)
            {
                minDistance = dist;
                minIndex = currIndex;
            }
        }
        currIndex++;
    }

    if (minIndex !=-1)   // if there's at least one candidate, we turn towards them
    {
        double newOrientation = M_PI + atan2( b->getY()-VoisinsOmni[minIndex].getY(), VoisinsOmni[minIndex].getX()-b->getX() );
        b->setOrientation(newOrientation);
    }
}
