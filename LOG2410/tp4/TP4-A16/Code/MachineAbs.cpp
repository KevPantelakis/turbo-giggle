///////////////////////////////////////////////////////////
//  MachineAbs.cpp
//  Implementation of the Class MachineAbs
//  Created on:      27-oct.-2016 15:12:15
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>

#include "MachineAbs.h"

MachineAbs::MachineAbs( FiltrePtr f )
: m_filtre(f)
{
}

MachineAbs::~MachineAbs(){
}

resultat_test MachineAbs::diagnostiquer(){
	// Methode servant a appeler les operations de diagnostique pour les differentes composantes de la machine

	auto res = resultat_test::succes;

	res = opDiagnostiquerFiltre();
	if (res == resultat_test::echec) return res;
	res = opDiagnostiquerCircuitEau();
	if (res == resultat_test::echec) return res;
	res = opDiagnostiquerCircuitThe();
	if (res == resultat_test::echec) return res;

	if (opACircuitLait()) {
		res = opDiagnostiquerCircuitLait();
		if (res == resultat_test::echec) return res;
	}
	if (opACircuitSucre()) {
		res = opDiagnostiquerCircuitSucre();
		if (res == resultat_test::echec) return res;
	}

	// Diagnostiquer le filtre
	// Diagnostiquer le circuit d'eau chaude
	// Diagnostiquer le circuit de the
	// Verifier si la machine a un circuit pour le lait, et si oui, le Diagnostiquer
	// Verifier si la machine a un circuit pour le sucre, et si oui, le Diagnostiquer

	return res;
}


void MachineAbs::nettoyer(){
	// Methode servant a appeler les operations de nettoyage pour les differentes composantes de la machine
	
	opNettoyerFiltre();
	opNettoyerCircuitEau();
	opNettoyerCircuitThe();

	if (opACircuitLait())
		opNettoyerCircuitLait();
	if (opACircuitSucre())
		opNettoyerCircuitSucre();
	// Nettoyer le filtre
	// Nettoyer le circuit d'eau chaude
	// Nettoyer le circuit de the
	// Verifier si la machine a un circuit pour le lait, et si oui, le nettoyer
	// Verifier si la machine a un circuit pour le sucre, et si oui, le nettoyer
}
