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

    for ( std::vector<ConcreteBestiole>::iterator it2 = VoisinsOmni.begin() ; it2 != VoisinsOmni.end() ; ++it2 )
    {

        double dist = std::sqrt( (it2->getX()-b->getX())*(it2->getX()-b->getX()) + (it2->getY()-b->getY())*(it2->getY()-b->getY()) );

        bool isInHearingDistance = ( dist <= b->getOreilles()[0] ) ;

        //cout << dist << " / " << b->getOreilles()[1] << " / " << isInHearingDistance << endl;

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

    if (minIndex !=-1) { // if there's at least one candidate, we turn towards them

            cout <<"voisin x" <<  VoisinsOmni[minIndex].getX() << endl;

    cout << "voisin y" << VoisinsOmni[minIndex].getY() << endl;
        cout<< "kamikaze x" <<  b->getX() << endl;
    cout<<"kamikaze y" <<   b->getY() << endl;

        double newOrientation = atan2( - VoisinsOmni[minIndex].getY() + b->getY(),-  b->getX()+VoisinsOmni[minIndex].getX() );

        cout << "je suis passé de " << b->getOrientation() << "à " << newOrientation << endl;
        b->setOrientation(newOrientation);





    }

}
