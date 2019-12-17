#ifndef GREGAIREPERSONALITY_H_INCLUDED
#define GREGAIREPERSONALITY_H_INCLUDED

#include "Personality.h"
#include <iostream>


class GregairePersonality: public Personality
{
public:
    void newAction();
    void newAction(int x, int y);
    void newAction(ConcreteBestiole * b);
};

#endif // GREGAIREPERSONALITY_H_INCLUDED
