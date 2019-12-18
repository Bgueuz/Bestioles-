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
/*
max_cam = b.max_cam;
min_cam = b.min_cam;
max_nage = b.max_nage;
min_nage = b.min_nage;
max_cara_dom = b.max_cara_dom;
min_cara_dom = b.min_cara_dom;
max_cara_vit = b.max_cara_vit;
min_cara_vit = b.min_cara_vit;
*/
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


ConcreteBestiole::ConcreteBestiole( const ConcreteBestiole & b ) // Accesoires à copier aussi
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
    oreilles = b.oreilles;
    yeux = b.yeux;

    camouflage = b.camouflage;
    nageoire = b.nageoire;
    carapaceDommage = b.carapaceDommage;
    carapaceVitesse = b.carapaceVitesse;

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

void ConcreteBestiole::setPersonality(Personality* newPersonality)
{
    personality = newPersonality;
}

void ConcreteBestiole::setType(int i)
{
    type = i;
}

int ConcreteBestiole::getType()
{
    return type;
}

void ConcreteBestiole::setSchizophrene(bool s)
{
    schizophrene = s;
}

void ConcreteBestiole::setOreilles(float radius, float probability)
{
    oreilles.push_back(radius);
    oreilles.push_back(probability);

}

void ConcreteBestiole::setYeux(float angle, float radius, float probability)
{

    yeux.push_back(angle);
    yeux.push_back(radius);
    yeux.push_back(probability);
}

void ConcreteBestiole::action( Milieu & monMilieu )  /////////// ACTION ////////////
{

    if(type==2 or type==1)
    {
        personality->newAction(this);
    }
    if (!schizophrene)
    {
        //cout << "NOT SCHIZOPHRENE" << endl;
        //personality->newAction(this);

    }
    else   // bestiole à personnalités multiples
    {
        //cout << "JE SUIS SCHIZOPHRENEEEEEEEEEEEEEEEEEEEEEEEEE" << endl;
        //this->randPersonality();
        //personality->newAction();
    }

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

    double         xt2 = x + cos( orientation )*AFF_SIZE/2.0;
    double         yt2 = y - sin( orientation )*AFF_SIZE/2.0;

    support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
    support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

    if (this->getNageoire() - 1.0 > 0.0)
    {
        support.draw_ellipse( (x+xt2)/2, (y+yt2)/2, AFF_SIZE/6, AFF_SIZE*1.5, -orientation/M_PI*180, couleur );
    }
    if ((this->getCarapaceVit() - 1.0 > 0.0) && (this->getCarapaceDom() - 1.0 > 0.0))
    {
        support.draw_ellipse( (x+xt)/2, (y+yt)/2, AFF_SIZE/1.5, AFF_SIZE/1.5, -orientation, couleur );
    }

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

void ConcreteBestiole::initOreilles(Milieu* flotte)
{

    if (std::rand() % 2 == 0)   // 50% chance the bestiole has an ear
    {
        float radius = RandomFloat( flotte->getMinEarRadius(),flotte->getMaxEarRadius());
        float probability = RandomFloat( flotte->getMinEarProbability(),flotte->getMaxEarProbability());

        setOreilles(radius, probability);
    }
    else
    {
        setOreilles(-1, -1);
    }
}

void ConcreteBestiole::initYeux(Milieu* flotte)
{

    if (std::rand() % 2 == 0)   // 50% chance the bestiole has an eye
    {
        float angle = RandomFloat(flotte->getMinEyeAngle(), flotte->getMaxEyeAngle());
        float radius = RandomFloat(flotte->getMinEyeRadius(), flotte->getMaxEyeRadius());
        float probability = RandomFloat(flotte->getMinEyeProbability(), flotte->getMaxEyeProbability());
        setYeux(angle, radius, probability);
    }
    else
    {
        setYeux(-1, -1, -1);
    }
}

void ConcreteBestiole::initPersonality()
{

    int random_int = std::rand() % 100; // between 0 and 99
    int random_behavior;
    if (random_int < 20) // grégaire
        random_behavior = 1;
    else if (random_int < 40) // peureuse
        random_behavior = 2;
    else if (random_int < 60) // kamikaze
        random_behavior = 3;
    else if (random_int < 80) // prévoyante
        random_behavior = 4;
    else                      // personnalités multiples
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

// Accesoires - Implementation : Code Rouge

void ConcreteBestiole::setAccesories(Milieu* flotte)
{
    // Les limites doivent pouvoir être modifiées à la création du milieu

    // Camouflage --> Rare

    if (float p_cam = RandomFloat(0.0,1.0) > 0.8)
    {
        this->setCamouflage(flotte->getMinCam(),flotte->getMaxCam());
    }

    // Nageoire --> Commun

    if (float p_nag = RandomFloat(0.0,1.0) > 0.5)
    {
        this->setNageoire(flotte->getMinNage(),flotte->getMaxNage());
    }

    // Carapace --> Semi-Rare

    if (float p_car = RandomFloat(0.0,1.0) > 0.65)
    {
        this->setCarapaceDom(flotte->getMinCaraDom(),flotte->getMaxCaraDom());
        this->setCarapaceVit(flotte->getMinCaraVit(),flotte->getMaxCaraVit());
    }

}

/////////// SETTEURS ACCESOIRES

void ConcreteBestiole::setCamouflage(float min_cam,float max_cam)
{
    this->camouflage = RandomFloat(min_cam,max_cam);
}

void ConcreteBestiole::setNageoire(float min_nage,float max_nage)
{
    this->nageoire = RandomFloat(min_nage,max_nage);
    this->vitesse = (this->vitesse)*(this->nageoire);
}

void ConcreteBestiole::setCarapaceDom(float min_cara_dom,float max_cara_dom)
{
    this->carapaceDommage = RandomFloat(min_cara_dom,max_cara_dom);
}

void ConcreteBestiole::setCarapaceVit(float min_cara_vit,float max_cara_vit)
{
    this->carapaceVitesse = RandomFloat(min_cara_vit,max_cara_vit);
    this->vitesse = (this->vitesse)/(this->carapaceVitesse);
}

// Stack Overflow

float ConcreteBestiole::RandomFloat(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
