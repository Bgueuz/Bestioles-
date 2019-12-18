#ifndef KAMIKAZEPERSONALITY_H_INCLUDED
#define KAMIKAZEPERSONALITY_H_INCLUDED

#include "Personality.h"

class KamikazePersonality: public Personality
{
public:
    virtual void newAction();
    void newAction(ConcreteBestiole * b);
};

#endif // KAMIKAZEPERSONALITY_H_INCLUDED
