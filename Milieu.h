#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include <iostream>
#include <vector>
#include "ConcreteBestiole.h"

using namespace std;


class Milieu : public UImg
{

private :
    static const T          white[];
    int                     nbBestiolesMax=50;
    float            ratiosCherches[5] = {0.1,0.1,0.7,0.1,0.};
    float            ratiosPresents[5] = {0.,0.,0.,0.,0.};
    int                     width, height;
    std::vector<ConcreteBestiole>   listeBestioles;

public :
    Milieu( int _width, int _height );
    ~Milieu( void );

    int getWidth( void ) const
    {
        return width;
    };
    int getHeight( void ) const
    {
        return height;
    };

    void step( void );
    std::vector<ConcreteBestiole> getBestioles( void ) const { return listeBestioles; };

    void addMember( const ConcreteBestiole & b )
    {
        if (listeBestioles.size()<nbBestiolesMax){
          
          listeBestioles.push_back(b);
          listeBestioles.back().initCoords(width, height);
          //listeBestioles.back().initPersonality();
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

    int nbVoisins( const ConcreteBestiole & b );
    void detection ();
    void updateVoisins(ConcreteBestiole & b);
    void collisionsAll();
    float RandomFloat(float a, float b);

public:

    //Accesoires

        // Camouflage
    void setCamouflageLimits(float max_cam, float min_cam);
    float getMaxCam(){return MAX_CAMO;};
    float getMinCam(){return MIN_CAMO;};

        // Nageoire
    void setNageoireLimits(float max_nage, float min_nage);
    float getMaxNage(){return MAX_NAGE;};
    float getMinNage(){return MIN_NAGE;};

        // Carapace - Dommage
    void setCaraDomLimits(float max_cara_dom, float min_cara_dom);
    float getMaxCaraDom(){return MAX_CARA_DOM;};
    float getMinCaraDom(){return MIN_CARA_DOM;};

        // Carapace - Vitesse
    void setCaraVitLimits(float max_cara_vit, float min_cara_vit);
    float getMaxCaraVit(){return MAX_CARA_VIT;};
    float getMinCaraVit(){return MIN_CARA_VIT;};

    // Capteurs

    void setEarRadiusLimits(float max_radius, float min_radius);
    float getMaxEarRadius(){return MAX_EAR_RADIUS;};
    float getMinEarRadius(){return MIN_EAR_RADIUS;};

    void setEarProbabilityLimits(float max_probability, float min_probability);
    float getMaxEarProbability(){return MAX_EAR_PROBABILITY;};
    float getMinEarProbability(){return MIN_EAR_PROBABILITY;};

    void setEyeAngleLimits(float max_angle, float min_angle);
    float getMaxEyeAngle(){return MAX_EYE_ANGLE;};
    float getMinEyeAngle(){return MIN_EYE_ANGLE;};

    void setEyeRadiusLimits(float max_radius, float min_radius);
    float getMaxEyeRadius(){return MAX_EYE_RADIUS;};
    float getMinEyeRadius(){return MIN_EYE_RADIUS;};

    void setEyeProbabilityLimits(float max_probability, float min_probability);
    float getMaxEyeProbability(){return MAX_EYE_PROBABILITY;};
    float getMinEyeProbability(){return MIN_EYE_PROBABILITY;};
    
    // Ratios de bestioles
    float* getRatiosCherches(){return ratiosCherches;};
    float* getRatiosPresents(){return ratiosPresents;};
    void updateRatiosPresents();
  

private:
    // Camouflage
    float MAX_CAMO = 1.0;
    float MIN_CAMO = 0.0;

    // Nageoire
    float MAX_NAGE = 2.0;
    float MIN_NAGE = 1.0;

    // Carapace
        // Reduction Dommages subit / chances de mourir à l'impact
    float MAX_CARA_DOM = 4.0;
    float MIN_CARA_DOM = 1.0;

            // Reduction Vitesse
    float MAX_CARA_VIT = 3.0;
    float MIN_CARA_VIT = 1.0;

    // Oreille
    float MIN_EAR_RADIUS = 100;
    float MAX_EAR_RADIUS = 200;

    float MIN_EAR_PROBABILITY = 0;
    float MAX_EAR_PROBABILITY = 1;

    // Yeux
    float MIN_EYE_ANGLE = 0;
    float MAX_EYE_ANGLE = M_PI;

    float MIN_EYE_RADIUS = 50;
    float MAX_EYE_RADIUS = 100;

    float MIN_EYE_PROBABILITY = 0;
    float MAX_EYE_PROBABILITY = 1;


};


#endif
