
#include "Bestiole.h"

#include "Milieu.h"

#include "GregairePersonality.h"
#include "PeureusePersonality.h"
#include "KamikazePersonality.h"
#include "PrevoyantePersonality.h"

#include "ConcreteBestiole.h"
#include <cstdlib>
#include <cmath>

const double      ConcreteBestiole::AFF_SIZE = 8.;
const double      ConcreteBestiole::MAX_VITESSE = 10.;
const double      ConcreteBestiole::LIMITE_VUE = 30.;

int               ConcreteBestiole::next = 0;


ConcreteBestiole::ConcreteBestiole( void )
{

    identite = ++next;

    //cout << "const Bestiole (" << identite << ") par defaut" << endl;

    x = y = type = 0;
    cumulX = cumulY = 0.;
    orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
    vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;

    couleur = new T[ 3 ];
    couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
    couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
    couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
}


ConcreteBestiole::ConcreteBestiole( const ConcreteBestiole & b )
{

    identite = ++next;

    //cout << "const ConcreteBestiole (" << identite << ") par copie" << endl;

    x = b.x;
    y = b.y;
    type=b.type;
    personality=b.personality;
    schizophrene = b.schizophrene;
    //listeVoisinsOmni= b.listeVoisinsOmni;
    //Voisins= b.Voisins;
    Detectes=b.Detectes;

    cumulX = cumulY = 0.;
    orientation = b.orientation;
    vitesse = b.vitesse;
    couleur = new T[ 3 ];
    memcpy( couleur, b.couleur, 3*sizeof(T) );

}


ConcreteBestiole::~ConcreteBestiole( void )
{

    delete[] couleur;

    //cout << "dest ConcreteBestiole" << endl;

}


void ConcreteBestiole::initCoords( int xLim, int yLim )
{

    x = rand() % xLim;
    y = rand() % yLim;
}


void ConcreteBestiole::bouge( int xLim, int yLim )
{
    cout << "JE BOUGE " << endl;
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
    cout << "FINI DE BOUGER" << endl;

}


list<ConcreteBestiole *> ConcreteBestiole::getVoisins()
{
    return Voisins;
}


list<ConcreteBestiole *> ConcreteBestiole::getDetectes()
{
    return Detectes;
}

void ConcreteBestiole::setPersonality(Personality* newPersonality) {
    personality = newPersonality;
}

void ConcreteBestiole::setType(int i) {
    type = i;
}

int ConcreteBestiole::getType() {
    return type;
}

void ConcreteBestiole::setSchizophrene(bool s) {
    schizophrene = s;
}





void ConcreteBestiole::action( Milieu & monMilieu )  /////////// ACTION ////////////
{

    if(type==0)
    {
        cout << personality << endl;
        personality->newAction(this);
    }
    if (!schizophrene)
    {
        //cout << "NOT SCHIZOPHRENE" << endl;
        //personality->newAction(&this);

    }
    else   // bestiole à personnalités multiples
    {
        //cout << "JE SUIS SCHIZOPHRENEEEEEEEEEEEEEEEEEEEEEEEEE" << endl;
        //this->randPersonality();
        //personality->newAction();
    }

    cout << "JE VAIS BOUGER" << endl;
    bouge( monMilieu.getWidth(), monMilieu.getHeight() );

}

Personality* ConcreteBestiole::getPersonality()
{
    return this->personality;
}

void ConcreteBestiole::draw( UImg & support )
{
    cout << "JE DESSINE" << endl;
    double         xt = x + cos( orientation )*AFF_SIZE/2.1;
    double         yt = y - sin( orientation )*AFF_SIZE/2.1;

    support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
    support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

    cout << "FINI DE DESSINER" << endl;
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


bool ConcreteBestiole::inRadiusVoisin(const ConcreteBestiole & b) const
{
   double radius(1000);
   double dist;
   dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   return ( dist <= radius );

}


bool ConcreteBestiole::checkCollision(const ConcreteBestiole & b) const
{
   double minRadius = AFF_SIZE + b.AFF_SIZE-4;
   double dist;
   dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   return ( dist <= minRadius);
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


void ConcreteBestiole::initPersonality()
{

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

        //listeBestioles.back().setType(random_behavior);
        switch (random_behavior)
        {
        case 1: // grégaire
        {
            schizophrene=false;
            personality = new GregairePersonality();
            type = 0;
            cout << "G" << endl;
        }
        break;
        case 2: // peureuse
        {
            schizophrene=false;
            personality = new PeureusePersonality();
            type = 1;
            cout << "PE" << endl;
        }
        break;
        case 3: // kamikaze
        {
            schizophrene=false;
            personality = new KamikazePersonality();
            type = 2;
            cout << "K" << endl;
        }
        break;
        case 4: // prévoyante
        {
            schizophrene=false;
            personality = new PrevoyantePersonality();
            type = 3;
            cout << "PR" << endl;
        }
        break;
        case 5: // personnalités multiples
        {
            schizophrene=true;
            personality = NULL;
            type = 4;
            cout << "S" << endl;
        }
        break;

        default:
            schizophrene=false;
            personality = new GregairePersonality();
            type = 0;
        }
}

void ConcreteBestiole::randPersonality()
{

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

        //listeBestioles.back().setType(random_behavior);
        switch (random_behavior)
        {
        case 1: // grégaire
        {
            personality = new GregairePersonality();
        }
        break;
        case 2: // peureuse
        {
            personality = new PeureusePersonality();
        }
        break;
        case 3: // kamikaze
        {
            personality = new KamikazePersonality();
        }
        break;
        case 4: // prévoyante
        {
            personality = new PrevoyantePersonality();
        }
    }
}
