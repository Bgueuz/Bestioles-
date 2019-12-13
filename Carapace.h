#ifndef CARAPACE_H
#define CARAPACE_H

#include "Decorateur.h"


class Carapace : public Decorateur
{
public:
    Carapace();
    virtual ~Carapace();

    float GetreductionVitesse()
    {
        return m_reductionVitesse;
    }
    void SetreductionVitesse(float val)
    {
        m_reductionVitesse = val;
    }
    float GetreductionDommage()
    {
        return m_reductionDommage;
    }
    void SetreductionDommage(float val)
    {
        m_reductionDommage = val;
    }

protected:

private:
    float m_reductionVitesse;
    float m_reductionDommage;
};

#endif // CARAPACE_H
