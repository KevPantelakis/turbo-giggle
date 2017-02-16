///////////////////////////////////////////////////////////
//  ElmCircuitLiquide.cpp
//  Implementation of the Class ElmCircuitLiquide
//  Created on:      27-oct.-2016 15:12:20
//  Original author: francois
///////////////////////////////////////////////////////////

#include <stdexcept>

#include "ElmCircuitLiquide.h"


ElmCircuitLiquide::ElmCircuitLiquide()
   : m_tartre(0)
{

}


ElmCircuitLiquide::~ElmCircuitLiquide(){

}

float ElmCircuitLiquide::calculerAccumulationTartre(float duree, float longueur, float aireSection)
{
	// Formule sans le moindre fondement scientifique
	// pour simuler une accumulation de tartre en fonction du temps
	// Parametres:
	//    duree en seconde (s)
	//    longueur de la tuyauterie (m)
	//    aireSection aire de la section de tuyauterie (m^2)
	const double tauxAccumulation = 0.0001; // grammes par secondes (g/s)
	return float(duree*tauxAccumulation*longueur*longueur / aireSection);
}



ElmCircuitLiquide::ElmCircuitLiqPtr ElmCircuitLiquide::getSousElement(size_t index){

	return  nullptr;
}

const ElmCircuitLiquide::ElmCircuitLiqPtr ElmCircuitLiquide::getSousElement(size_t index) const {

	return  nullptr;
}

int ElmCircuitLiquide::nombreSousElements() const {

	return 0;
}


void ElmCircuitLiquide::addSousElement(const ElmCircuitLiqPtr& sousElm ){
	throw std::logic_error("ElmCircuitLiquide::addSousElement: l'element ne supporte pas l'ajout d'elements");
}

void ElmCircuitLiquide::addSousElement(ElmCircuitLiquide* sousElm){
	throw std::logic_error("ElmCircuitLiquide::addSousElement: l'element ne supporte pas l'ajout d'elements");
}


