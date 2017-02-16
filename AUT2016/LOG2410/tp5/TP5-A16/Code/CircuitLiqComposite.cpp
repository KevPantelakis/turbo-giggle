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

	if (index < 0 || index >= m_CircuitLiquide.size())
		throw std::range_error( "CircuitLiqComposite::getSousElement: indexation a l'exterieur du vecteur d'element" );
	return  m_CircuitLiquide[index];
}

const ElmCircuitLiquide::ElmCircuitLiqPtr CircuitLiqComposite::getSousElement(size_t index) const {

	if (index < 0 || index >= m_CircuitLiquide.size())
		throw std::range_error("CircuitLiqComposite::getSousElement: indexation a l'exterieur du vecteur d'element");
	return  m_CircuitLiquide[index];
}

int CircuitLiqComposite::nombreSousElements() const {

	return m_CircuitLiquide.size();
}

void CircuitLiqComposite::addSousElement(const ElmCircuitLiqPtr& sousElm){
	m_CircuitLiquide.push_back(sousElm);
}


void CircuitLiqComposite::addSousElement(ElmCircuitLiquide* sousElm){
	m_CircuitLiquide.push_back(ElmCircuitLiqPtr(sousElm));
}

float CircuitLiqComposite::getTartre(void) const {
	int nse = nombreSousElements();
	float tartreMax = 0;
	for (int ise = 0; ise < nse; ++ise)
	{
		ElmCircuitLiqPtr sep = getSousElement(ise);
		auto tartre = sep->getTartre();
		tartreMax = (tartre>tartreMax) ? tartre : tartreMax;
	}
	return tartreMax;
}

void CircuitLiqComposite::operer(float duree){
	int nse = nombreSousElements();
	for (int ise = 0; ise < nse; ++ise)
	{
		ElmCircuitLiqPtr sep = getSousElement(ise);
		sep->operer(duree);
	}
}

void CircuitLiqComposite::nettoyer(){
	int nse = nombreSousElements();
	for (int ise = 0; ise < nse; ++ise)
	{
		ElmCircuitLiqPtr sep = getSousElement(ise);
		sep->nettoyer();
	}
}


