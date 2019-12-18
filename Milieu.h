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
    int             nbBestiolesMax=50;
    float            ratiosCherches[5] = {0.1, 0.1, 0.1, 0.1, 0.6};
    float            ratiosPresents[5] = {0.,0.,0.,0.,0.};
    int                     width, height;
    std::vector<ConcreteBestiole>   listeBestioles;

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
    float MAX_EAR_RADIUS = 300;
    float MIN_EAR_PROBABILITY = 0.4;
    float MAX_EAR_PROBABILITY = 1;
    // Yeux
    float MIN_EYE_ANGLE = 0.4;
    float MAX_EYE_ANGLE = M_PI;
    float MIN_EYE_RADIUS = 50;
    float MAX_EYE_RADIUS = 200;
    float MIN_EYE_PROBABILITY = 0.4;
    float MAX_EYE_PROBABILITY = 1;


public :
    Milieu( int _width, int _height );
    ~Milieu( void );


    //Methods
    void step( void );
    void naissance();
    void updateRatiosPresents();
    void detection ();
    void updateVoisins(ConcreteBestiole & b);
    void collisionsAll();
    void addMember( const ConcreteBestiole & b );
    void gestionvie();
    int nbVoisins( const ConcreteBestiole & b );
    float RandomFloat(float a, float b);

public :
        // CLONAGE

    void gestionClonage();
    void addMemberClone( const ConcreteBestiole & b );

public:

    // Getters
    int getWidth( void ) const{return width;};
    int getHeight( void ) const{return height;};
    std::vector<ConcreteBestiole> getBestioles( void ) const { return listeBestioles; };
        //Accessoires
    float getMaxCam(){return MAX_CAMO;};
    float getMinCam(){return MIN_CAMO;};
    float getMaxCaraDom(){return MAX_CARA_DOM;};
    float getMinCaraDom(){return MIN_CARA_DOM;};
    float getMaxCaraVit(){return MAX_CARA_VIT;};
    float getMinCaraVit(){return MIN_CARA_VIT;};
    float getMaxNage(){return MAX_NAGE;};
    float getMinNage(){return MIN_NAGE;};
        // Capteurs
    float getMaxEarRadius(){return MAX_EAR_RADIUS;};
    float getMinEarRadius(){return MIN_EAR_RADIUS;};
    float getMaxEarProbability(){return MAX_EAR_PROBABILITY;};
    float getMinEarProbability(){return MIN_EAR_PROBABILITY;};
    float getMaxEyeAngle(){return MAX_EYE_ANGLE;};
    float getMinEyeAngle(){return MIN_EYE_ANGLE;};
    float getMaxEyeRadius(){return MAX_EYE_RADIUS;};
    float getMinEyeRadius(){return MIN_EYE_RADIUS;};
    float getMaxEyeProbability(){return MAX_EYE_PROBABILITY;};
    float getMinEyeProbability(){return MIN_EYE_PROBABILITY;};
        //Ratios populations
    float* getRatiosCherches(){return ratiosCherches;};
    float* getRatiosPresents(){return ratiosPresents;};

    //Setters
        //Accessoires
    void setCamouflageLimits(float max_cam, float min_cam);
    void setNageoireLimits(float max_nage, float min_nage);
    void setCaraDomLimits(float max_cara_dom, float min_cara_dom);
    void setCaraVitLimits(float max_cara_vit, float min_cara_vit);
        //Capteurs
    void setEarRadiusLimits(float max_radius, float min_radius);
    void setEarProbabilityLimits(float max_probability, float min_probability);
    void setEyeAngleLimits(float max_angle, float min_angle);
    void setEyeRadiusLimits(float max_radius, float min_radius);
    void setEyeProbabilityLimits(float max_probability, float min_probability);

};


#endif
