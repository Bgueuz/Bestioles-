#ifndef _PERSONALITY_H_INCLUDED
#define _PERSONALITY_H_INCLUDED

#include <iostream>

class ConcreteBestiole;

class Personality
{
public:
    virtual void newAction(ConcreteBestiole* b)=0;
};

#endif // _PERSONALITY_H_

