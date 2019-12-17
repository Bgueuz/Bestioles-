#ifndef PREVOYANTEPERSONALITY_H_INCLUDED
#define PREVOYANTEPERSONALITY_H_INCLUDED

#include "Personality.h"

class PrevoyantePersonality: public Personality
{
public:
    virtual void newAction();
    void newAction(int x, int y){}
    void newAction(ConcreteBestiole * b);
};

#endif // PREVOYANTEPERSONALITY_H_INCLUDED
