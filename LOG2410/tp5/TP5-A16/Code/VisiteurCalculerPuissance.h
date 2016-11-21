///////////////////////////////////////////////////////////
//  VisiteurCalculerPuissance.h
//  Implementation of the Class VisiteurCalculerPuissance
//  Created on:      15-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_VisiteurCalculerPuissance__INCLUDED_)
#define class_VisiteurCalculerPuissance__INCLUDED_

#include "VisiteurSansEffet.h"

class VisiteurCalculerPuissance : public VisiteurSansEffet
{
private:
	float m_puissanceTotale;
public:
	VisiteurCalculerPuissance();
	virtual ~VisiteurCalculerPuissance() {};

	// Methode de traitement des elements concrets qui ont une puissance
	virtual void traiterBouilloire(Bouilloire* _bouil);
	virtual void traiterPompe(Pompe* _pomp);
	virtual void traiterMoteur(Moteur* _mot);

	// Methode d'acces au volume total
	virtual float getPuissanceTotale() const { return m_puissanceTotale; };
	virtual void resetPuissanceTotale() { m_puissanceTotale = 0; }
};
#endif // class_VisiteurCalculerPuissance__INCLUDED_#pragma once
