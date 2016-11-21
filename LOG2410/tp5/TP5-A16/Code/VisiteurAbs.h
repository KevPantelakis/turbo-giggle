///////////////////////////////////////////////////////////
//  VisiteurAbs.h
//  Implementation of the Class VisiteurAbs
//  Created on:      10-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_VisiteurAbs__INCLUDED_)
#define class_VisiteurAbs__INCLUDED_

class VisiteurAbs
{
public:
	VisiteurAbs() {};
	virtual ~VisiteurAbs() {};

	// Methode de traitement du filtre
	virtual void traiterFiltre(class Filtre* _fil) = 0;

	// Methode de traitement des elements concrets des circuits liquides
	virtual void traiterBouilloire(class Bouilloire* _bouil) = 0;
	virtual void traiterPompe(class Pompe* _pomp) = 0;
	virtual void traiterReservoir(class Reservoir* _reserv) = 0;
	virtual void traiterTuyau(class Tuyau* _tuy) = 0;
	virtual void traiterCircuitLiqComposite(class CircuitLiqComposite* _circ) = 0;

	// Methode de traitement des elements concrets des circuits solides
	virtual void traiterCircuitSolComposite(class CircuitSolComposite* _circ) = 0;
	virtual void traiterMoteur(class Moteur* _mot) = 0;
	virtual void traiterReceptacle(class Receptacle* _recept) = 0;
	virtual void traiterTransmission(class Transmission* _recept) = 0;
};
#endif // class_VisiteurAbs__INCLUDED_