///////////////////////////////////////////////////////////
//  VisiteurCalculerPuissance.cpp
//  Implementation of the Class VisiteurCalculerPuissance
//  Created on:      15-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#include "VisiteurCalculerPuissance.h"

VisiteurCalculerPuissance::VisiteurCalculerPuissance()
	: m_puissanceTotale(0.0)
{
}

void VisiteurCalculerPuissance::traiterBouilloire(Bouilloire* _bouil)
{
	m_puissanceTotale += _bouil->getPuissance();
}

void VisiteurCalculerPuissance::traiterPompe(Pompe * _pomp)
{
	m_puissanceTotale += _pomp->getPuissance();
}

void VisiteurCalculerPuissance::traiterMoteur(Moteur * _mot)
{
	m_puissanceTotale += _mot->getPuissance();
}
