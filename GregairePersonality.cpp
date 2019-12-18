#include "GregairePersonality.h"

#include "ConcreteBestiole.h"
#include <iostream>

void GregairePersonality::newAction()
{
}

void GregairePersonality::newAction(int x, int y)
{

    std::cout << "JE SUIS GREGAIRE AUX COORD " << x << " " << y << std::endl;

}


void GregairePersonality::newAction(ConcreteBestiole * b)
{


    std::vector<ConcreteBestiole> VoisinsOmni = b->getVoisinsOmni();
    double newOrientation = 0;
    int i=0;
    std::vector<int> detected = b->detectVoisins();

    for (std::vector<int>::iterator it = detected.begin() ; it != detected.end(); ++it){
        newOrientation += VoisinsOmni[*it].getOrientation();
        i++;
    }

    if (i != 0){// if there's at least one candidate, we turn towards them
        b->setOrientation(newOrientation/i);
    }
}


    /*
    for ( std::vector<ConcreteBestiole>::iterator it2 = VoisinsOmni.begin() ; it2 != VoisinsOmni.end() ; ++it2 )
    {
        double dist = std::sqrt( (it2->getX()-b->getX())*(it2->getX()-b->getX()) + (it2->getY()-b->getY())*(it2->getY()-b->getY()) );
        bool isInHearingDistance = ( dist <= b->getOreilles()[0] );
        bool isInVisibleDistance = ( dist <= b->getYeux()[0] );

        float angleBiBj = atan2( b->getY()-it2->getY(), it2->getX()-b->getX() );

        bool isInVisibleRegion = (( b->getOrientation() - b->getYeux()[1]/2 < angleBiBj) && (angleBiBj < b->getOrientation()+b->getYeux()[1]/2 ));

        if(isInVisibleRegion)

        if (isInHearingDistance || (isInVisibleRegion && isInVisibleDistance))   // on ignore le camouflage
        {
            if( max(b->getYeux()[2],b->getOreilles()[1]) > it2->getCamouflage()  ){
            newOrientation +=it2->getOrientation();
            i++;
            }
        }
    }
    */

