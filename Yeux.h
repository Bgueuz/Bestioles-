#ifndef YEUX_H
#define YEUX_H

#include <Decorateur.h>


class Yeux : public Decorateur
{
    public:
        Yeux();
        virtual ~Yeux();

        float GetangleYeux() { return m_angleYeux; }
        void SetangleYeux(float val) { m_angleYeux = val; }
        float GetporteeYeux() { return m_porteeYeux; }
        void SetporteeYeux(float val) { m_porteeYeux = val; }
        float GetdetectionYeux() { return m_detectionYeux; }
        void SetdetectionYeux(float val) { m_detectionYeux = val; }

    protected:

    private:
        float m_angleYeux;
        float m_porteeYeux;
        float m_detectionYeux;
};

#endif // YEUX_H
