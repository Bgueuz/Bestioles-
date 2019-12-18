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
const double      ConcreteBestiole::MAX_VITESSE = 7.;
const double      ConcreteBestiole::LIMITE_VUE = 30.;
int               ConcreteBestiole::next = 0;

// Constructeur
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

// Constructeur par copie
ConcreteBestiole::ConcreteBestiole( const ConcreteBestiole & b ) // Accessoires à copier aussi
{

    identite = ++next;

    //cout << "const ConcreteBestiole (" << identite << ") par copie" << endl;

    x = b.x;
    y = b.y;
    type=b.type;
    personality=b.personality;
    Detectes=b.Detectes;
    cumulX = cumulY = 0.;
    normal_vit = b.normal_vit;
    orientation = b.orientation;
    vitesse = b.vitesse;
    oreilles = b.oreilles;
    yeux = b.yeux;
    vecu = b.vecu;
    dureedevie = b.dureedevie;
    camouflage = b.camouflage;
    nageoire = b.nageoire;
    carapaceDommage = b.carapaceDommage;
    carapaceVitesse = b.carapaceVitesse;

    couleur = new T[ 3 ];
    memcpy( couleur, b.couleur, 3*sizeof(T) );
}

// Destructeur
ConcreteBestiole::~ConcreteBestiole( void )
{
    delete[] couleur;
    //cout << "dest ConcreteBestiole" << endl;
}

// Initialise les coordonnées de la bestiole
void ConcreteBestiole::initCoords( int xLim, int yLim )
{
    x = rand() % xLim;
    y = rand() % yLim;
}

// Déplace physiquement la bestiole dans l'aquarium selon sa vitesse, son orientation, et sa vitesse actuelle
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

// Renvoie les coordonnées futures d'une bestiole bougeant simplement. Utile pour prédire le mouvement des autres bestioles
std::vector<int> ConcreteBestiole::simuleBouge()
{
    double         nx, ny;
    double         dx = cos( orientation )*vitesse;
    double         dy = -sin( orientation )*vitesse;
    int            cx, cy;

    int futureX, futureY;

    cx = static_cast<int>( cumulX );
    cy = static_cast<int>( cumulY );

    nx = x + dx + cx;
    ny = y + dy + cy;

    futureX = static_cast<int>( nx );
    futureY = static_cast<int>( ny );

    std::vector<int> newCoords;
    newCoords.push_back(futureX);
    newCoords.push_back(futureY);
    return newCoords;

}

// Action supplémentaire pour les bestioles dotées de personnalités
void ConcreteBestiole::action( Milieu & monMilieu )  /////////// ACTION ////////////
{
        if (type==4)        // bestiole à personnalités multiples
    {
        if (personality==nullptr)
        {
            this->randPersonality();
        }
        else
        {
            if((std::rand() % 11) >5)
            {
                this->randPersonality();
            }
        }
    }
    personality->newAction(this);

    bouge( monMilieu.getWidth(), monMilieu.getHeight() );
}

// Dessine la bestiole dans l'interface graphique
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

    if ((this->getCamouflage() > 0.0))
    {
        unsigned char purple[] = { 255,0,255 };
        support.draw_text((x+xt)/2, (y+yt)/2, "Ninja",purple,20);
    }

}

// Attribue à chaque bestiole une couleur suivant son type
void ConcreteBestiole::changeColorToType()
{
    T* couleur2 = new T[ 3 ];
    if(type==0)
    {
        couleur2[0]=0;    //Grégaire -> Noir
        couleur2[1]=0;
        couleur2[2]=0;
    }
    else if(type==1)
    {
        couleur2[0]=0;    //Peureuse -> Bleu
        couleur2[1]=0;
        couleur2[2]=255;
    }
    else if(type==2)
    {
        couleur2[0]=255;    // Kamikaze -> Rouge
        couleur2[1]=0;
        couleur2[2]=0;
    }
    else if(type==3)
    {
        couleur2[0]=0;    // Prévoyante -> Vert
        couleur2[1]=255;
        couleur2[2]=0;
    }
    else
    {
        couleur2[0]=255;    // Personnalités multiples -> Magenta
        couleur2[1]=0;
        couleur2[2]=255;
    }

    memcpy( couleur, couleur2, 3*sizeof(T) );
    delete couleur2;
}

// Surchage de l'opérateur ==
bool operator==( const ConcreteBestiole & b1, const ConcreteBestiole & b2 )
{
    return ( b1.identite == b2.identite );
}

// Renvoie true si la bestiole courante voit la bestiole passée en entrée
bool ConcreteBestiole::jeTeVois( const ConcreteBestiole & b ) const
{
    double dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
    return ( dist <= LIMITE_VUE );
}

// Renvoie true si la bestiole passée en entrée est dans le rayon voisin de la bestiole courante
bool ConcreteBestiole::inRadiusVoisin(const ConcreteBestiole & b) const
{
    double radius(1000);
    double dist;
    dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
    return ( dist <= radius );
}

// Renvoie true si la bestiole courante et la bestiole passée en entrée sont acttuellement en collision
bool ConcreteBestiole::checkCollision(const ConcreteBestiole & b) const
{
    double minRadius = AFF_SIZE + b.AFF_SIZE-4;
    double dist;
    dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
    return ( dist <= minRadius);
}

// A une chance de donner des oreilles de coefficients aléatoires à la bestiole courante
void ConcreteBestiole::initOreilles(Milieu* flotte)
{

    if (float p_oreilles = RandomFloat(0.0,1.0) > 0.10)  // 90 %
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

// A une chance de donner des yeux de coefficients aléatoires à la bestiole courante
void ConcreteBestiole::initYeux(Milieu* flotte)
{

    if (float p_yeux = RandomFloat(0.0,1.0) > 0.10)  // 90 %
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

// Donne une personnalité aléatoire à la bestiole courante, en s'assurant que les ratios de population soient respectés
void ConcreteBestiole::initPersonality(Milieu* milieu,float ratiosCherches[5],float ratiosPresents[5])
{
    int set_behavior;

    if (milieu->getBestioles().size()==1)
    {
        int n =5;
        set_behavior = distance(ratiosCherches, max_element(ratiosCherches, ratiosCherches + n));
    }
    else
    {
        float ratiosDifference[5];
        for(int i =0; i<5; i++)
        {
            ratiosDifference[i]=ratiosCherches[i]-ratiosPresents[i];
        }
        int m = 5;
        set_behavior = distance(ratiosDifference, max_element(ratiosDifference, ratiosDifference + m));
    }

    switch (set_behavior+1)
    {
    case 1: // grégaire
    {
        personality = new GregairePersonality();
        type = 0;
    }
    break;
    case 2: // peureuse
    {
        personality = new PeureusePersonality();
        type = 1;
    }
    break;
    case 3: // kamikaze
    {
        personality = new KamikazePersonality();
        type = 2;
    }
    break;
    case 4: // prévoyante
    {
        personality = new PrevoyantePersonality();
        type = 3;
    }
    break;
    case 5: // personnalités multiples
    {
        personality = new GregairePersonality(); // les bestioles PM commencent par être grégaires
        type = 4;
    }
    break;

    default:
        personality = new GregairePersonality();
        type = 0;
    }
}

// Attribue une personnalité aléatoire. Utile pour les bestioles à personnalités multiples
void ConcreteBestiole::randPersonality()
{
    int random_int = std::rand() % 100; // between 0 and 99
    int random_behavior;
    if (random_int < 40)
        random_behavior = 1;
    else if (random_int < 60)
        random_behavior = 2;
    else if (random_int < 80)
        random_behavior = 3;
    else
        random_behavior = 4;

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


// Incrémente l'âge d'une bestiole et vérifie si elle doit mourir
void ConcreteBestiole::vie ()
{
    vecu=vecu+1;
    if (vecu>=dureedevie*2)
    {
        tue=true;
    }
}

// Marque une bestiole comme devant mourir
void ConcreteBestiole::Kill(void)
{
    tue=true;
}

// Génère un nombre flottant aléatoire compris entre a et b
float ConcreteBestiole::RandomFloat(float a, float b) // code from stackoverflow
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

// Génère une liste de voisins détectés
std::vector<int> ConcreteBestiole::detectVoisins()
{
    std::vector<int> detected;
    int i=0;
    for ( std::vector<ConcreteBestiole>::iterator it2 = listeVoisinsOmni.begin() ; it2 != listeVoisinsOmni.end() ; ++it2 )
    {
        double dist = std::sqrt( (it2->getX()-x)*(it2->getX()-x) + (it2->getY()-y)*(it2->getY()-y) );
        bool isInHearingDistance = ( dist <= oreilles[0] );
        bool isInVisibleDistance = ( dist <= yeux[0] );

        float angleBiBj = atan2( y-it2->getY(), it2->getX()-x );

        bool isInVisibleRegion = (( orientation - yeux[1]/2 < angleBiBj) && (angleBiBj < orientation + yeux[1]/2 ));

        if (isInHearingDistance || (isInVisibleRegion && isInVisibleDistance))   // on ignore le camouflage
        {
            if( max(yeux[2],oreilles[1]) > it2->getCamouflage())
            {
                detected.push_back(i);
            }

        }
        i++;
    }
    return detected;
}

/* Clone */

// Initialise les coordonnées d'un clone
void ConcreteBestiole::InitCoordsClone(int xclone, int yclone)
{
    if (x>2)
    {
        x = xclone-2;
    }
    if (x<=2)
    {
        x= xclone+2;
    }
    if (y>2)
    {
        y = yclone+2;
    }

    if (y<=2)
    {
        y = yclone-2;
    }

}

// Initialise l'âge d'un clone à 0
void ConcreteBestiole::setVecu()
{
    vecu = 0;
}

// Getters and setters

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

int ConcreteBestiole::getType()
{
    return type;
}

void ConcreteBestiole::setType(int i)
{
    type = i;
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

Personality* ConcreteBestiole::getPersonality()
{
    return this->personality;
}

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

void ConcreteBestiole::setAccessories(Milieu* flotte)
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
