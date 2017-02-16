///////////////////////////////////////////////////////////
//  CircuitSolComposite.cpp
//  Implementation of the Class CircuitSolComposite
//  Created on:      27-oct.-2016 15:12:34
//  Original author: francois
///////////////////////////////////////////////////////////

#include <stdexcept>

#include "CircuitSolComposite.h"


CircuitSolComposite::CircuitSolComposite(){

}



CircuitSolComposite::~CircuitSolComposite(){

}


CircuitSolComposite::ElmCircuitSolPtr CircuitSolComposite::getSousElement(size_t index){
	return  m_CircuitSolide.at(index);
}

const CircuitSolComposite::ElmCircuitSolPtr CircuitSolComposite::getSousElement(size_t index) const {
	return  m_CircuitSolide.at(index);
}

int CircuitSolComposite::nombreSousElements() const {
	return m_CircuitSolide.size();
}


void CircuitSolComposite::addSousElement(const ElmCircuitSolPtr& sousElem){
	m_CircuitSolide.push_back(sousElem);
}

void CircuitSolComposite::addSousElement(ElmCircuitSolide* sousElem){
	std::shared_ptr<ElmCircuitSolide> ptr(sousElem);
	m_CircuitSolide.push_back(ptr);
}

float CircuitSolComposite::getDebris(void) const {
	// Recuperer la quantite de debris maximum parmi tous les enfants
	float debrisMax = 0;
	for each (ElmCircuitSolPtr it in m_CircuitSolide)
	{
		debrisMax = std::fmaxf(it->getDebris(),debrisMax);
	}
	return debrisMax;
}

void CircuitSolComposite::operer( float duree ){
	for each (ElmCircuitSolPtr it in m_CircuitSolide)
	{
		it->operer(duree);
	}

}

void CircuitSolComposite::nettoyer(){

	for each (ElmCircuitSolPtr it in m_CircuitSolide)
	{
		it->nettoyer();
	}
}


