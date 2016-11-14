///////////////////////////////////////////////////////////
//  Receptacle.cpp
//  Implementation of the Class Receptacle
//  Created on:      27-oct.-2016 15:20:09
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>

#include "Receptacle.h"
#define _USE_MATH_DEFINES
#include <math.h>


Receptacle::Receptacle( float r, float h, float n )
: m_rayon(r), m_hauteur(h), m_niveau(n)
{

}



Receptacle::~Receptacle(){

}


void Receptacle::operer( float duree ){
	float debris = calculerAccumulationDebris(duree, float(M_PI*m_rayon*m_rayon));
	addDebris(debris);
}


void Receptacle::nettoyer(){
	removeDebris();
}