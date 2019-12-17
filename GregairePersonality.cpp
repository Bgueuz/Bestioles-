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
    cout << "HELLO" << endl;
    std::cout << "JE SUIS GREGAIRE AVEC VITESSE " << b->getVitesse() << std::endl;
    std::vector<ConcreteBestiole> VoisinsOmni = b->getVoisinsOmni();
    double vitesse = 0;
    int i=0;

    for ( std::vector<ConcreteBestiole>::iterator it2 = VoisinsOmni.begin() ; it2 != VoisinsOmni.end() ; ++it2 )
    {
        i+=1;
        vitesse += it2->getVitesse();
        std::cout << "VITESSE SOMME VOISIN " << vitesse << std::endl;

    }
    if(i>0)
    {
        vitesse=vitesse/i;
        //b->setVitesse(2*vitesse);
        cout <<"greta2" << endl;
    }
    else
    {
        vitesse=b->getVitesse();
        //b->setVitesse(vitesse);
        cout <<"greta" << endl;
    }
}

