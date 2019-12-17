#ifndef PEUREUSEPERSONALITY_H_INCLUDED
#define PEUREUSEPERSONALITY_H_INCLUDED

#include "Personality.h"

class PeureusePersonality: public Personality
{
public:
    virtual void newAction();
    void newAction(int x, int y){}
    void newAction(ConcreteBestiole * b);
};

#endif // PEUREUSEPERSONALITY_H_INCLUDED
