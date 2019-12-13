#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include <Decorateur.h>


class Camouflage : public Decorateur
{
    public:
        Camouflage();
        virtual ~Camouflage();

        float Getinvisibilite() { return m_invisibilite; }
        void Setinvisibilite(float val) { m_invisibilite = val; }

    protected:

    private:
        float m_invisibilite;
};

#endif // CAMOUFLAGE_H
