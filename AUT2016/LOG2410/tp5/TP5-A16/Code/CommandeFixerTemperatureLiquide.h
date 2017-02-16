///////////////////////////////////////////////////////////
//  CommandeFixerTemperatureLiquide.h
//  Implementation of the Class CommandeFixerTemperatureLiquide
//  Created on:      10-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_CommandeFixerTemperatureLiquide__INCLUDED_)
#define class_CommandeFixerTemperatureLiquide__INCLUDED_

#include "ElmCircuitLiquide.h"
#include "VisiteurSansEffet.h"
#include "CommandeAbs.h"

#include <iostream>

class CommandeFixerTemperatureLiquide : public CommandeAbs
{
private:
	class VisiteurFixerTemperatureLiquide : public VisiteurSansEffet
	{
		float _temperature;
	public:
		// Construire un visiteur qui conserve la temperature de consigne
		VisiteurFixerTemperatureLiquide(float _temper) : _temperature(_temper) {}
		
		// Surcharger la fonction du visiteur pour changer la temperature de la bouilloire
		virtual void traiterBouilloire(Bouilloire* _bouil);
	};

	// Instancier le visiteur qui n'agit que sur la bouilloire
	VisiteurFixerTemperatureLiquide vis;

public:
	CommandeFixerTemperatureLiquide( float _temper ) : vis(_temper) {};
	virtual ~CommandeFixerTemperatureLiquide() {};

	// Methode d'execution de la commande
	virtual void executer(class ElmVisitable* _elm) { _elm->accepter(&vis); };
};
#endif // class_CommandeFixerTemperatureLiquide__INCLUDED_#pragma once
