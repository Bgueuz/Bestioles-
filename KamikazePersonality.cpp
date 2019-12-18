#include "KamikazePersonality.h"
#include "ConcreteBestiole.h"
#include <iostream>

void KamikazePersonality::newAction()
{
}


void KamikazePersonality::newAction(ConcreteBestiole * b)
{
    std::vector<ConcreteBestiole> VoisinsOmni = b->getVoisinsOmni();

    double minDistance = std::numeric_limits<double>::infinity();
    int currIndex = 0;
    int minIndex = -1;

    std::vector<int> detected = b->detectVoisins();

    for (std::vector<int>::iterator it = detected.begin() ; it != detected.end(); ++it){

        double dist = std::sqrt( (VoisinsOmni[*it].getX()-b->getX())*(VoisinsOmni[*it].getX()-b->getX()) + (VoisinsOmni[*it].getY()-b->getY())*(VoisinsOmni[*it].getY()-b->getY()) );
        if (dist < minDistance)
        {
            minDistance = dist;
            minIndex = currIndex;
        }
    }


    if (minIndex !=-1)   // if there's at least one candidate, we turn towards them
    {
        double newOrientation = atan2( b->getY()-VoisinsOmni[minIndex].getY(), VoisinsOmni[minIndex].getX()-b->getX() );
        b->setOrientation(newOrientation);
    }

}

    /*

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
    */
