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

	if (index < 0 || index >= m_CircuitSolide.size())
		throw std::range_error("CircuitSolComposite::getSousElement: indexation a l'exterieur du vecteur d'element");
	return  m_CircuitSolide[index];
}

const CircuitSolComposite::ElmCircuitSolPtr CircuitSolComposite::getSousElement(size_t index) const {

	if (index < 0 || index >= m_CircuitSolide.size())
		throw std::range_error("CircuitSolComposite::getSousElement: indexation a l'exterieur du vecteur d'element");
	return  m_CircuitSolide[index];
}

int CircuitSolComposite::nombreSousElements() const {
	return m_CircuitSolide.size();
}


void CircuitSolComposite::addSousElement(const ElmCircuitSolPtr& sousElem){
	m_CircuitSolide.push_back(sousElem);
}

void CircuitSolComposite::addSousElement(ElmCircuitSolide* sousElem){
	m_CircuitSolide.push_back(ElmCircuitSolPtr(sousElem));
}

float CircuitSolComposite::getDebris(void) const {
	int nse = nombreSousElements();
	float debrisMax = 0;
	for (int ise = 0; ise < nse; ++ise)
	{
		ElmCircuitSolPtr sep = getSousElement(ise);
		auto debris = sep->getDebris();
		debrisMax = (debris>debrisMax) ? debris : debrisMax;
	}
	return debrisMax;
}

void CircuitSolComposite::operer( float duree ){
	int nse = nombreSousElements();
	for (int ise = 0; ise < nse; ++ise)
	{
		ElmCircuitSolPtr sep = getSousElement(ise);
		sep->operer(duree);
	}
}

void CircuitSolComposite::nettoyer(){
	int nse = nombreSousElements();
	for (int ise = 0; ise < nse; ++ise)
	{
		ElmCircuitSolPtr sep = getSousElement(ise);
		sep->nettoyer();
	}
}


