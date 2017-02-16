///////////////////////////////////////////////////////////
//  ElmCircuitSolide.cpp
//  Implementation of the Class ElmCircuitSolide
//  Created on:      27-oct.-2016 15:12:27
//  Original author: francois
///////////////////////////////////////////////////////////

#include <stdexcept>

#include "ElmCircuitSolide.h"


ElmCircuitSolide::ElmCircuitSolide()
: m_debris(0)
{

}



ElmCircuitSolide::~ElmCircuitSolide(){

}


ElmCircuitSolide::ElmCircuitSolPtr ElmCircuitSolide::getSousElement(size_t index){

	return  nullptr;
}

const ElmCircuitSolide::ElmCircuitSolPtr ElmCircuitSolide::getSousElement(size_t index) const {

	return  nullptr;
}

int ElmCircuitSolide::nombreSousElements() const {

	return 0;
}

float ElmCircuitSolide::calculerAccumulationDebris(float duree, float aireSection)
{
	// Formule sans le moindre fondement scientifique
	// pour simuler une accumulation de debris en fonction du temps
	// Parametres:
	//    duree en seconde (s)
	//    aireSection aire de la section de la composante (m^2)
	const double tauxAccumulation = 0.005; // grammes par secondes*m^2 (g/s.m^2)
	return float(duree*tauxAccumulation*aireSection);
}

void ElmCircuitSolide::addSousElement(const ElmCircuitSolPtr& sousElm){
	throw std::logic_error("ElmCircuitSolide::addSousElement: l'element ne supporte pas l'ajout d'elements");
}

void ElmCircuitSolide::addSousElement(ElmCircuitSolide* sousElm){
	throw std::logic_error("ElmCircuitSolide::addSousElement: l'element ne supporte pas l'ajout d'elements");
}

