///////////////////////////////////////////////////////////
//  Transmission.cpp
//  Implementation of the Class Transmission
//  Created on:      27-oct.-2016 15:12:32
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>

#include "Transmission.h"


Transmission::Transmission( float la, float lo )
: m_largeur(la), m_longueur(lo)
{

}



Transmission::~Transmission(){

}



void Transmission::operer( float duree ){
	float debris = calculerAccumulationDebris(duree, m_largeur*m_longueur);
	addDebris(debris);
}

void Transmission::nettoyer(){
	removeDebris();
}