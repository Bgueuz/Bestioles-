#ifndef PREVOYANTEPERSONALITY_H_INCLUDED
#define PREVOYANTEPERSONALITY_H_INCLUDED

#include "Personality.h"

class PrevoyantePersonality: public Personality
{
public:
    virtual void newAction();
    virtual void newAction(ConcreteBestiole * b);
};

#endif // PREVOYANTEPERSONALITY_H_INCLUDED
