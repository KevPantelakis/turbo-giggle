///////////////////////////////////////////////////////////
//  VisiteurSansEffet.h
//  Implementation of the Class VisiteurSansEffet
//  Created on:      10-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_VisiteurSansEffet__INCLUDED_)
#define class_VisiteurSansEffet__INCLUDED_

#include "MachineBase.h"
#include "MachineLuxe.h"

#include "Bouilloire.h"
#include "CircuitLiqComposite.h"
#include "Pompe.h"
#include "Reservoir.h"
#include "Tuyau.h"

#include "CircuitSolComposite.h"
#include "Moteur.h"
#include "Receptacle.h"
#include "Transmission.h"

class VisiteurSansEffet : public VisiteurAbs
{
protected:
	virtual void traiterElmVisitable(ElmVisitable* _elm) {};
public:
	VisiteurSansEffet() {};
	virtual ~VisiteurSansEffet() = 0;

	// Methode de traitement du filtre
	virtual void traiterFiltre(Filtre* _fil) { traiterElmVisitable(_fil); };

	// Methode de traitement des elements concrets des circuits liquides
	virtual void traiterBouilloire(Bouilloire* _bouil) { traiterElmVisitable(_bouil); };
	virtual void traiterPompe(Pompe* _pomp) { traiterElmVisitable(_pomp); };
	virtual void traiterReservoir(Reservoir* _reserv) { traiterElmVisitable(_reserv); };
	virtual void traiterTuyau(Tuyau* _tuy) { traiterElmVisitable(_tuy); };
	// Surcharger la fonction du visiteur pour traiter les composites liquide en iterant sur les sous-elements
	virtual void traiterCircuitLiqComposite(CircuitLiqComposite* circ);

	// Methode de traitement des elements concrets des circuits solides
	// Surcharger la fonction du visiteur pour traiter les composites liquide en iterant sur les sous-elements
	virtual void traiterCircuitSolComposite(CircuitSolComposite* circ);
	virtual void traiterMoteur(class Moteur* _mot) { traiterElmVisitable(_mot); };
	virtual void traiterReceptacle(class Receptacle* _recept) { traiterElmVisitable(_recept); };
	virtual void traiterTransmission(class Transmission* _trans) { traiterElmVisitable(_trans); };
};
#endif // class_VisiteurSansEffet__INCLUDED_#pragma once
