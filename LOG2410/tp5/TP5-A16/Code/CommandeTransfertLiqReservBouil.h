///////////////////////////////////////////////////////////
//  CommandeTransfertLiqReservBouil.h
//  Implementation of the Class CommandeTransfertLiqReservBouil
//  Created on:      10-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_CommandeTransfertLiqReservBouil__INCLUDED_)
#define class_CommandeTransfertLiqReservBouil__INCLUDED_

#include "ElmCircuitLiquide.h"
#include "VisiteurSansEffet.h"
#include "CommandeAbs.h"

class CommandeTransfertLiqReservBouil : public CommandeAbs
{
private:
	class VisiteurTransfertLiqReservBouil : public VisiteurSansEffet
	{
		float m_volume;
	public:
		// Construire un visiteur qui transfert un volume de liquide du reservoir a la bouilloire
		VisiteurTransfertLiqReservBouil(float _vol) : m_volume(_vol) {}

		// Surcharger la fonction du visiteur pour changer le reservoir, la pompe et la bouilloire
		virtual void traiterReservoir(Reservoir* _reserv);
		virtual void traiterPompe(Pompe* _pomp);
		virtual void traiterBouilloire(Bouilloire* _bouil);
	};

	// Instancier le visiteur qui transfert le liquide du reservoir a la bouilloire
	VisiteurTransfertLiqReservBouil vis;

public:
	CommandeTransfertLiqReservBouil(float _vol) : vis(_vol) {};
	virtual ~CommandeTransfertLiqReservBouil() {};

	// Methode d'execution de la commande
	virtual void executer(class ElmVisitable* _elm) { _elm->accepter(&vis); };
};
#endif // class_CommandeTransfertLiqReservBouil__INCLUDED_#pragma once

