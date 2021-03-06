///////////////////////////////////////////////////////////
//  CommandeTranfertLiqReservBouil.cpp
//  Implementation of the Class CommandeTranfertLiqReservBouil
//  Created on:      15-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>

#include "CommandeTransfertLiqReservBouil.h"

void CommandeTransfertLiqReservBouil::VisiteurTransfertLiqReservBouil::traiterReservoir(Reservoir * _reserv)
{
	// Verifier s'il y a suffisamment de liquide dans le reservoire
	// Si oui, reduire le niveau du reservoir d'une quantite equivalente au volume transfere
	float niveauLiquide = _reserv->getNiveau();
	if (m_volume <= niveauLiquide) {
		_reserv->setNiveau(niveauLiquide - m_volume);
	} else {
		throw std::range_error("Erreur d'operation: il ne reste pas assez de liquide dans le r�servoir.");
	}
}

void CommandeTransfertLiqReservBouil::VisiteurTransfertLiqReservBouil::traiterPompe(Pompe * _pomp)
{
	// Operer la pompe pour une duree correspondant au temps necessaire pour transferer le volume de liquide
	// La duree d'operation est le volume a transferer divise par le debit de la pompe
	_pomp->operer(m_volume / _pomp->getDebit());

}

void CommandeTransfertLiqReservBouil::VisiteurTransfertLiqReservBouil::traiterBouilloire(Bouilloire * _bouil)
{
	// Verifier si le volume restant de la bouilloire peut contenir la quantite de liquide transferee
	// Si oui, augmenter le niveau de la bouilloire d'une quantite equivalente au volume transfere
	float niveauLiqide = _bouil->getNiveau() + m_volume;
	if (niveauLiqide <= _bouil->getVolume()) {
		_bouil->setNiveau(niveauLiqide);
	} else {
		throw std::range_error("Erreur d'op�ration: la bouilloire ne peut pas contenir autant de liquide.");
	}
}
