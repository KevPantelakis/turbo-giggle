///////////////////////////////////////////////////////////
//  Pompe.cpp
//  Implementation of the Class Pompe
//  Created on:      27-oct.-2016 15:21:34
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>

#include "Pompe.h"


Pompe::Pompe( float d )
: m_debit(d)
{
}

Pompe::~Pompe(){
}

void Pompe::operer( float duree ){
	// Pas d'accumulation de tartre dans la pompe
}

void Pompe::nettoyer(){
	removeTartre();
}