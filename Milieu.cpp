#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height ) : UImg( _width, _height, 1, 3 ),
    width(_width), height(_height)
{

    // cout << "const Milieu" << endl;

    std::srand( time(NULL) );

}
Milieu::~Milieu( void )
{

    // cout << "dest Milieu" << endl;

}

void Milieu::naissance(){
    int proba_naissance = 50;
    int tirage = std::rand() % 100 +1 ;
    if (tirage <= proba_naissance)
    {
        cout << "NAISSANCE" << endl;
        addMember(ConcreteBestiole());
    }
}

void Milieu::step( void )
{
    naissance();
    collisionsAll();
    updateRatiosPresents();
    //cout << ratiosPresents[0] << ";" << ratiosPresents[1] << ";" <<ratiosPresents[2] << ";" <<ratiosPresents[3] << ";" <<ratiosPresents[4] << endl;
    //addMember(ConcreteBestiole());
    cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );

    for ( std::vector<ConcreteBestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
    {
        it->action( *this );
        it->draw( *this );

    } // for
}


int Milieu::nbVoisins( const ConcreteBestiole & b )
{
    int         nb = 0;
    for ( std::vector<ConcreteBestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
        if ( !(b == *it) && b.jeTeVois(*it) )
            ++nb;

    return nb;

}


void Milieu::updateVoisins(ConcreteBestiole & b)
{
    std::vector<ConcreteBestiole>   newListeVoisinsOmni ;
    for ( std::vector<ConcreteBestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
    {
        if ( !(b== *it) && b.inRadiusVoisin(*it) )
        {
            newListeVoisinsOmni.push_back(*it);
        }
    }
    b.setVoisins(newListeVoisinsOmni);
    newListeVoisinsOmni.clear();
}

void Milieu::collisionsAll()
{
  float seuil_mort = 0.9;
  for ( std::vector<ConcreteBestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
  {
    updateVoisins(*it);
    std::vector<ConcreteBestiole> VoisinsOmni = it->getVoisinsOmni();
    for ( std::vector<ConcreteBestiole>::iterator it2 = VoisinsOmni.begin() ; it2 != VoisinsOmni.end() ; ++it2 )
    {
      if(!(*it == *it2) && (*it).checkCollision(*it2))
      {
        //On vérifie si la bestiole a une carapace.
        if (float p_mort = RandomFloat(0.0,1.0)/it->getCarapaceDom() >= seuil_mort)
        {
          cout << "la bestiole meurt par collision" << endl; //la bestiole meurt
          (*it).Kill();
        }
        else
        {
          double collisionVector1_x= (*it).getX() - (*it2).getX();
          double collisionVector1_y= (*it).getY() - (*it2).getY();
          if (collisionVector1_x !=0 && collisionVector1_y!=0)
          {
            double v_x= (*it).getVitesse()*std::cos((*it).getOrientation());
            double v_y= (*it).getVitesse()*std::sin((*it).getOrientation());
            double phi = std::atan((collisionVector1_y/collisionVector1_x));

            double v_1= v_x*std::cos(phi)+v_y*std::sin(phi);
            double v_2= -v_x*std::sin(phi)+v_y*std::cos(phi);
            v_2=-v_2;

            double new_orientation=std::atan((v_2/v_1));
            (*it).setOrientation( new_orientation - phi);
          }
          else if ((*it).getOrientation()==0)
          {
            (*it).setOrientation(M_PI*180/M_PI);
          }
          else if ((*it).getOrientation()==M_PI /2*180/M_PI)
          {
            (*it).setOrientation(3*M_PI /2*180/M_PI);
          }
          else if ((*it).getOrientation()==M_PI *180/M_PI)
          {
            (*it).setOrientation(0);
          }
          else if ((*it).getOrientation()==3*M_PI /2*180/M_PI)
          {
            (*it).setOrientation(M_PI /2*180/M_PI);
          }
        }
      }
    }
  }
}

void Milieu::updateRatiosPresents()
{
  float nbByBehaviors[5]={0.,0.,0.,0.,0.};
  for ( std::vector<ConcreteBestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it ){
    ++nbByBehaviors[it->getType()];
  }
  for(int i=0;i<5;i++){
    ratiosPresents[i]=nbByBehaviors[i]/static_cast<float>(listeBestioles.size());
  }
}

// Setters

void Milieu::setCamouflageLimits(float max_cam, float min_cam)
{
    this->MAX_CAMO = max_cam;
    this->MIN_CAMO = min_cam;
}

void Milieu::setNageoireLimits(float max_nage, float min_nage)
{
    this->MAX_NAGE = max_nage;
    this->MIN_NAGE = min_nage;
}

void Milieu::setCaraDomLimits(float max_cara_dom, float min_cara_dom)
{
    this->MAX_CARA_DOM = max_cara_dom;
    this->MIN_CARA_DOM = min_cara_dom;
}

void Milieu::setCaraVitLimits(float max_cara_vit, float min_cara_vit)
{
    this->MAX_CARA_VIT = max_cara_vit;
    this->MIN_CARA_VIT = min_cara_vit;
}

void Milieu::setEarRadiusLimits(float max_radius, float min_radius)
{
    this->MAX_EAR_RADIUS = max_radius;
    this->MIN_EAR_RADIUS = min_radius;
}

void Milieu::setEarProbabilityLimits(float max_probability, float min_probability)
{
    this->MAX_EAR_PROBABILITY = max_probability;
    this->MIN_EAR_PROBABILITY = min_probability;
}

void Milieu::setEyeAngleLimits(float max_angle, float min_angle)
{
    this->MAX_EYE_ANGLE = max_angle;
    this->MIN_EYE_ANGLE = min_angle;
}

void Milieu::setEyeRadiusLimits(float max_radius, float min_radius)
{
    this->MAX_EYE_RADIUS = max_radius;
    this->MIN_EYE_RADIUS = min_radius;
}

void Milieu::setEyeProbabilityLimits(float max_probability, float min_probability)
{
    this->MAX_EYE_PROBABILITY = max_probability;
    this->MIN_EYE_PROBABILITY = min_probability;
}

float Milieu::RandomFloat(float a, float b)
{
  float random = ((float) std::rand()) / (float) RAND_MAX;
  float diff = b - a;
  float r = random * diff;
  return a + r;
}

void Milieu::gestionvie()
{
    std::vector<ConcreteBestiole> listeBestioles2 {};
    for (std::vector<ConcreteBestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it)
    {
        (*it).vie();
        if ((*it).getTue()==false)
        {
            listeBestioles2.push_back(*it);
        }
    }
    listeBestioles.swap(listeBestioles2);
}

  void Milieu::addMember( const ConcreteBestiole & b )
  {
    if (listeBestioles.size()<nbBestiolesMax){

      listeBestioles.push_back(b);
      listeBestioles.back().initCoords(width, height);
      listeBestioles.back().initPersonality(this,ratiosCherches,ratiosPresents);

      // Ajout de capteurs
      listeBestioles.back().initOreilles(this);
      listeBestioles.back().initYeux(this);

      // Accessoires
      listeBestioles.back().setAccesories(this);

      cout << "bestiole :" << listeBestioles.back().getIdentite() << endl;
      cout << "   cette bestiole à un camouflage de " << listeBestioles.back().getCamouflage() << endl;
      cout << "   cette bestiole à des nageoires de " << listeBestioles.back().getNageoire() << endl;
      cout << "   cette bestiole à une carapace " << endl;
      cout << "       qui réduit les dommages de  " << listeBestioles.back().getCarapaceDom() << endl;
      cout << "       qui réduit la vitesse de  " << listeBestioles.back().getCarapaceVit() << endl;
    }
    else{
      cout << "Capacité max atteinte" << endl;
    }
  }
