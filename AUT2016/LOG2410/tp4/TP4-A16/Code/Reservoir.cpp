///////////////////////////////////////////////////////////
//  Reservoir.cpp
//  Implementation of the Class Reservoir
//  Created on:      27-oct.-2016 15:12:25
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>

#include "Reservoir.h"


Reservoir::Reservoir( float p, float l, float h, float n )
: m_profondeur(p), m_largeur(l), m_hauteur(h), m_niveau(n)
{
}



Reservoir::~Reservoir(){
}


void Reservoir::operer( float duree ){
	float tartre = calculerAccumulationTartre(duree, m_hauteur, m_profondeur*m_largeur);
	addTartre(tartre);
}


void Reservoir::nettoyer(){
	removeTartre();
}