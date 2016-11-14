///////////////////////////////////////////////////////////
//  MachineBase.cpp
//  Implementation of the Class MachineBase
//  Created on:      27-oct.-2016 15:12:17
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>

#include "MachineBase.h"

#include "CircuitLiqComposite.h"
#include "Bouilloire.h"
#include "Pompe.h"
#include "Reservoir.h"
#include "Tuyau.h"

#include "CircuitSolComposite.h"
#include "Transmission.h"
#include "Moteur.h"
#include "Receptacle.h"

#include "Filtre.h"

MachineBase::MachineBase()
: MachineAbs(FiltrePtr(new Filtre)), m_CircuitEauChaude(new CircuitLiqComposite), m_CircuitThe(new CircuitSolComposite)
{
	// Construire toutes les composantes d'une machine de base

	// Constuire les elements du circuit d'eau chaude
	m_CircuitEauChaude->addSousElement( new Reservoir(4.5, 25.0, 20.0, 100.0) );
	m_CircuitEauChaude->addSousElement(new Tuyau(0.25, 5.0));
	m_CircuitEauChaude->addSousElement(new Pompe(0.05f));
	m_CircuitEauChaude->addSousElement(new Tuyau(0.25, 5.0));
	m_CircuitEauChaude->addSousElement(new Bouilloire(5.5, 20.0));
	m_CircuitEauChaude->addSousElement(new Tuyau(0.25, 5.0));

	// Constuire les elements du circuit de the
	m_CircuitThe->addSousElement(new Receptacle(12.5, 15.0, 100));
	m_CircuitThe->addSousElement(new Moteur(0.5));
	m_CircuitThe->addSousElement(new Transmission(0.75, 5.0));
}



MachineBase::~MachineBase(){

}


void MachineBase::infuserThe(float duree){
	m_CircuitThe->operer(duree);
	m_CircuitEauChaude->operer(duree);
}



bool MachineBase::opACircuitLait(){

	return false;
}


bool MachineBase::opACircuitSucre(){

	return false;
}


void MachineBase::opNettoyerCircuitEau(){
	m_CircuitEauChaude->nettoyer();
}


void MachineBase::opNettoyerCircuitLait(){

}


void MachineBase::opNettoyerCircuitSucre(){

}


void MachineBase::opNettoyerCircuitThe(){
	m_CircuitThe->nettoyer();
}


void MachineBase::opNettoyerFiltre(){
	m_filtre->nettoyer();
}

resultat_test MachineBase::opDiagnostiquerCircuitEau(){
	auto tartre = m_CircuitEauChaude->getTartre();
	return (tartre < SEUIL_TARTRE_MAX_EAU) ? resultat_test::succes : resultat_test::echec;
}


resultat_test MachineBase::opDiagnostiquerCircuitLait(){
	return resultat_test::succes;
}


resultat_test MachineBase::opDiagnostiquerCircuitSucre(){
	return resultat_test::succes;
}


resultat_test MachineBase::opDiagnostiquerCircuitThe(){
	auto debris = m_CircuitThe->getDebris();
	return (debris < SEUIL_DEBRIS_MAX_THE) ? resultat_test::succes : resultat_test::echec;
}


resultat_test MachineBase::opDiagnostiquerFiltre(){
	return resultat_test::succes;
}
