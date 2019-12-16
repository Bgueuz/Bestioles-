#include "ConcreteBestiole.h"
#include "Bestiole.h"
#include <cstdlib>
#include <cmath>
#include "Milieu.h"
#include "GregairePersonality.h"
#include "PeureusePersonality.h"
#include "KamikazePersonality.h"
#include "PrevoyantePersonality.h"

const double      ConcreteBestiole::AFF_SIZE = 8.;
const double      ConcreteBestiole::MAX_VITESSE = 10.;
const double      ConcreteBestiole::LIMITE_VUE = 30.;

int               ConcreteBestiole::next = 0;


ConcreteBestiole::ConcreteBestiole( void )
{

    identite = ++next;

    //cout << "const Bestiole (" << identite << ") par defaut" << endl;

    x = y = 0;
    cumulX = cumulY = 0.;
    orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
    vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;

    couleur = new T[ 3 ];
    couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
    couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
    couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );


    //cout << "CONCRETEBESTIOLE  NORMAL " << personality << "   WITH & " << &personality  << endl;

}


ConcreteBestiole::ConcreteBestiole( const ConcreteBestiole & b )
{

    identite = ++next;

    //cout << "const ConcreteBestiole (" << identite << ") par copie" << endl;

    x = b.x;
    y = b.y;
    cumulX = cumulY = 0.;
    orientation = b.orientation;
    vitesse = b.vitesse;
    couleur = new T[ 3 ];
    memcpy( couleur, b.couleur, 3*sizeof(T) );

}


ConcreteBestiole::~ConcreteBestiole( void )
{

    delete[] couleur;

    cout << "dest ConcreteBestiole:" << this << " of personality: " << this->personality << endl;

}


void ConcreteBestiole::initCoords( int xLim, int yLim )
{

    x = rand() % xLim;
    y = rand() % yLim;

}


void ConcreteBestiole::bouge( int xLim, int yLim )
{

    double         nx, ny;
    double         dx = cos( orientation )*vitesse;
    double         dy = -sin( orientation )*vitesse;
    int            cx, cy;


    cx = static_cast<int>( cumulX );
    cumulX -= cx;
    cy = static_cast<int>( cumulY );
    cumulY -= cy;

    nx = x + dx + cx;
    ny = y + dy + cy;

    if ( (nx < 0) || (nx > xLim - 1) )
    {
        orientation = M_PI - orientation;
        cumulX = 0.;
    }
    else
    {
        x = static_cast<int>( nx );
        cumulX += nx - x;
    }

    if ( (ny < 0) || (ny > yLim - 1) )
    {
        orientation = -orientation;
        cumulY = 0.;
    }
    else
    {
        y = static_cast<int>( ny );
        cumulY += ny - y;
    }

}


list<ConcreteBestiole *> ConcreteBestiole::getVoisins()
{
    return Voisins;
}

list<ConcreteBestiole *> ConcreteBestiole::getDetectes()
{
    return Detectes;
}

void ConcreteBestiole::action( Milieu & monMilieu )  /////////// ACTION ////////////
{
    if (personality!=nullptr)
    {
        cout << " ALORRRRRRRRRRRS"<< endl;
        personality->newAction();

    }
    else { // bestiole à personnalités multiples
        Personality* p;
        cout << "JE SUIS SCHIZO" <<endl;
        int random_int = std::rand() % 100; // between 0 and 99
        int random_behavior;
        if (random_int < 20)
            random_behavior = 1;
        else if (random_int < 40)
            random_behavior = 2;
        else if (random_int < 60)
            random_behavior = 3;
        else if (random_int < 80)
            random_behavior = 4;
        else
            random_behavior = 5;

        switch (random_behavior)
        {
        case 1: // grégaire
        {
            p= new GregairePersonality();
            p->newAction();
        }
        break;
        case 2: // peureuse
        {
            p = new PeureusePersonality();
            p->newAction();
        }
        break;
        case 3: // kamikaze
        {
            p= new KamikazePersonality();
            p->newAction();
        }
        break;
        case 4: // prévoyante
        {
            p = new PrevoyantePersonality();
            p->newAction();
            //personality->newAction();
        }

    }
    }


    //cout << "Vitesse " << vitesse << " Schizo " << schizophrene << endl;
    bouge( monMilieu.getWidth(), monMilieu.getHeight() );

}

Personality* ConcreteBestiole::getPersonality()
{
    return this->personality;
}

void ConcreteBestiole::draw( UImg & support )
{

    double         xt = x + cos( orientation )*AFF_SIZE/2.1;
    double         yt = y - sin( orientation )*AFF_SIZE/2.1;

    support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
    support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

}


bool operator==( const ConcreteBestiole & b1, const ConcreteBestiole & b2 )
{

    return ( b1.identite == b2.identite );

}


bool ConcreteBestiole::jeTeVois( const ConcreteBestiole & b ) const
{

    double         dist;


    dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
    return ( dist <= LIMITE_VUE );

}

bool ConcreteBestiole::vu (const ConcreteBestiole & b)
{
//A modifier après ajout Decorator
    /*
        bool v = false;
        double dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
        if (yeux = true) {
                if (abs(asin((x-b.x)/(dist)))<=alpha/2) {
                        //double cam = b.getCamouflage();
                        //v = (gammaY > cam);
                }
        }
    */
}

bool ConcreteBestiole::entendu (const ConcreteBestiole & b)
{
//A modifier après ajout Decorator
    /*
        bool e = false;
        double dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
        if (oreilles=true) {
            if (dist <= LIMITE_OUIE){
                //double cam = b.getCamouflage();
                //e = (gammaO > cam);
            }
        }
    */
}
