#ifndef OREILLES_H
#define OREILLES_H

#include "Decorateur.h"


class Oreilles : public Decorateur
{
public:
    Oreilles();
    virtual ~Oreilles();

    float GetdetectionOreilles()
    {
        return m_detectionOreilles;
    }
    void SetdetectionOreilles(float val)
    {
        m_detectionOreilles = val;
    }
    float GetporteeOreilles()
    {
        return m_porteeOreilles;
    }
    void SetporteeOreilles(float val)
    {
        m_porteeOreilles = val;
    }

protected:

private:
    float m_detectionOreilles;
    float m_porteeOreilles;
};

#endif // OREILLES_H
