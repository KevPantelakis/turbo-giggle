///////////////////////////////////////////////////////////
//  CircuitLiqComposite.cpp
//  Implementation of the Class CircuitLiqComposite
//  Created on:      27-oct.-2016 15:19:51
//  Original author: francois
///////////////////////////////////////////////////////////

#include <stdexcept>

#include "CircuitLiqComposite.h"


CircuitLiqComposite::CircuitLiqComposite(){

}

CircuitLiqComposite::~CircuitLiqComposite(){

}

ElmCircuitLiquide::ElmCircuitLiqPtr CircuitLiqComposite::getSousElement( size_t index ){
	return  m_CircuitLiquide.at(index);
}

const ElmCircuitLiquide::ElmCircuitLiqPtr CircuitLiqComposite::getSousElement(size_t index) const {
	return m_CircuitLiquide.at(index);
}

int CircuitLiqComposite::nombreSousElements() const {

	return m_CircuitLiquide.size();
}

void CircuitLiqComposite::addSousElement(const ElmCircuitLiqPtr& sousElm){
	m_CircuitLiquide.push_back(sousElm);
}


void CircuitLiqComposite::addSousElement(ElmCircuitLiquide* sousElm){
	std::shared_ptr<ElmCircuitLiquide> my_ptr(sousElm);
	m_CircuitLiquide.push_back(my_ptr);
}

float CircuitLiqComposite::getTartre(void) const {
	// Recuperer la quantite de tartre maximum parmi tous les enfants
	float tartreMax = 0;
	for each (ElmCircuitLiqPtr it in m_CircuitLiquide)
	{
		tartreMax = std::fmaxf(it.get()->getTartre(), tartreMax);
	}
	return tartreMax;
}

void CircuitLiqComposite::operer(float duree){
	for each (ElmCircuitLiqPtr it in m_CircuitLiquide)
	{
		it.get()->operer(duree);
	}
}

void CircuitLiqComposite::nettoyer(){
	for each (ElmCircuitLiqPtr it in m_CircuitLiquide)
	{
		it.get()->nettoyer();
	}
}


