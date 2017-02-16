///////////////////////////////////////////////////////////
//  CommandeFixerTemperatureLiquide.cpp
//  Implementation of the Class CommandeFixerTemperatureLiquide
//  Created on:      15-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#include <stdexcept>

#include "CommandeFixerTemperatureLiquide.h"

void CommandeFixerTemperatureLiquide::VisiteurFixerTemperatureLiquide::traiterBouilloire(Bouilloire * _bouil)
{
	// Verifier que la bouilloire n'est pas vide
	if (_bouil->getNiveau() > _bouil->niveauMinimum)
		_bouil->setTemperature(_temperature);
	else
		throw std::range_error("Erreur d'operation: la bouilloire est vide");
}

