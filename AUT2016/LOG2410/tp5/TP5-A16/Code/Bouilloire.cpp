///////////////////////////////////////////////////////////
//  Bouilloire.cpp
//  Implementation of the Class Bouilloire
//  Created on:      27-oct.-2016 15:18:24
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Bouilloire.h"


Bouilloire::Bouilloire( float _r, float _h, float _p)
: m_rayon(_r), m_hauteur(_h), m_temperature(20), m_niveau(0), m_puissance(_p)
{

}



Bouilloire::~Bouilloire(){

}


void Bouilloire::operer( float duree ){
	float tartre = calculerAccumulationTartre(duree, m_hauteur, float(M_PI*m_rayon*m_rayon));
	addTartre(tartre);
}


void Bouilloire::nettoyer(){
	removeTartre();
}