#include "Milieu.h"
#include <cstdlib>
#include <ctime>


const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height ) : UImg( _width, _height, 1, 3 ),
    width(_width), height(_height)
{

    cout << "const Milieu" << endl;

    std::srand( time(NULL) );

}


Milieu::~Milieu( void )
{

    cout << "dest Milieu" << endl;

}


void Milieu::step( void )
{

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

void Milieu::detection ()
{
//A modifier après ajout Decorator
    /*for ( std::list<ConcreteBestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
    {
        se = (*it).getSensors();
        if (se != []) {
                Voisins = (*it).getVoisins()
                Detectes = (*it).getDetectes()
                if (Voisins.empty=false){
                        for ( std::list<ConcreteBestiole>::iterator ut = Voisins.begin() ; ut != listeVoisins.end() ; ++ut ) {
                            if(((*it).vu(*ut)) ||((*it).entendu(*ut))) {
                                Detectes.push_front(*ut);
                                Voisins.remove(*ut);
                            }
                        }
                }
        }



    }*/


}

void Milieu::updateVoisins(ConcreteBestiole & b)
{
  std::vector<ConcreteBestiole>   newListeVoisinsOmni;
  for ( std::vector<ConcreteBestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
  {
    if ( !(b== *it) && b.inRadiusVoisin(*it) )
    {
      newListeVoisinsOmni.push_back(*it);
    }
  }

  b.setVoisins(newListeVoisinsOmni);
}

void Milieu::collisionsAll()
{
    for ( std::vector<ConcreteBestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
    {
        updateVoisins(*it);
        for(std::vector<ConcreteBestiole>::iterator it2 = (it->getVoisins()).begin() ; it2 != (it->getVoisins()).end() ; ++it2 )
        {
            if(!(*it == *it2) && (*it).checkCollision(*it2))
             {
                double collisionVector1_x= (*it).getX() - (*it2).getX();
                double collisionVector1_y= (*it).getY() - (*it2).getY();
                if(collisionVector1_x !=0 && collisionVector1_y!=0)
                {
                    double collisionVector2_x= 1;
                    double collisionVector2_y= -collisionVector1_x/collisionVector1_y;

                    double v_x= (*it).getVitesse()*std::cos((*it).getOrientation());
                    double v_y= (*it).getVitesse()*std::sin((*it).getOrientation());
                    double phi = std::atan((collisionVector1_y/collisionVector1_x));
                    double phi2 = std::atan((collisionVector2_y/collisionVector2_x));

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
      //cout << "TESTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT" << endl;
    }
}
