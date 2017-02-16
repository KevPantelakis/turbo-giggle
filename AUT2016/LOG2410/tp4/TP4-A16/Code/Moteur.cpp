///////////////////////////////////////////////////////////
//  Moteur.cpp
//  Implementation of the Class Moteur
//  Created on:      27-oct.-2016 15:12:31
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>

#include "Moteur.h"


Moteur::Moteur( float p )
: m_puissance(p)
{

}



Moteur::~Moteur(){

}


void Moteur::operer( float duree ){
	// Pas d'accumulation de debris dans le moteur
}


void Moteur::nettoyer(){
	removeDebris();
}