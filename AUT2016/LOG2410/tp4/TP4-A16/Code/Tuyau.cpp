///////////////////////////////////////////////////////////
//  Tuyau.cpp
//  Implementation of the Class Tuyau
//  Created on:      27-oct.-2016 15:19:37
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Tuyau.h"


Tuyau::Tuyau( float r, float l )
: m_rayon(r), m_longueur(l)
{
}

Tuyau::~Tuyau(){
}

void Tuyau::operer( float duree ){
	float tartre = calculerAccumulationTartre(duree, m_longueur, float(M_PI*m_rayon*m_rayon));
	addTartre(tartre);
}

void Tuyau::nettoyer(){
	removeTartre();
}