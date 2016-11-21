///////////////////////////////////////////////////////////
//  Filtre.cpp
//  Implementation of the Class Filtre
//  Created on:      27-oct.-2016 15:21:34
//  Original author: francois
///////////////////////////////////////////////////////////

#include "Filtre.h"

#include <iostream>

Filtre::Filtre()
: m_debris(0), m_tartre(0)
{
}



Filtre::~Filtre(){

}

int Filtre::getTartre() {
	return m_tartre;
};


void Filtre::addTartre(int tartreAjoute) {
	m_tartre += tartreAjoute;
}

int Filtre::getDebris() {
	return m_debris;
};


void Filtre::addDebris(int debrisAjoute) {
	m_debris += debrisAjoute;
}


void Filtre::operer( float duree ){

}


void Filtre::nettoyer(){
	removeTartre();
	removeDebris();
}