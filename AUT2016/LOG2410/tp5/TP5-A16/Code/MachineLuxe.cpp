///////////////////////////////////////////////////////////
//  MachineLuxe.cpp
//  Implementation of the Class MachineLuxe
//  Created on:      27-oct.-2016 15:12:24
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>

#include "MachineLuxe.h"

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

MachineLuxe::MachineLuxe()
: MachineAbs(FiltrePtr(new Filtre)), m_CircuitEauChaude(new CircuitLiqComposite), m_CircuitLait(new CircuitLiqComposite),
m_CircuitSucre(new CircuitSolComposite), m_CircuitThe(new CircuitSolComposite)
{
	// Constuire les elements du circuit d'eau chaude
	m_CircuitEauChaude->addSousElement(new Reservoir(4.5, 25.0, 20.0, 100.0));
	m_CircuitEauChaude->addSousElement(new Tuyau(0.25, 5.0));
	m_CircuitEauChaude->addSousElement(new Pompe(0.05f, 7.5));
    // Construire un sous-circuit pour le chauffage de l'eau
	CircuitLiqComposite* circuitChauffagePtr = new CircuitLiqComposite;
	circuitChauffagePtr->addSousElement(new Tuyau(0.25, 5.0));
	circuitChauffagePtr->addSousElement(new Bouilloire(5.5, 25.0, 550.0));
	circuitChauffagePtr->addSousElement(new Tuyau(0.25, 5.0));
	m_CircuitEauChaude->addSousElement(circuitChauffagePtr);
	m_CircuitEauChaude->addSousElement(new Tuyau(0.25, 5.0));

	// Constuire les elements du circuit pour le lait
	m_CircuitLait->addSousElement(new Reservoir(3.25, 15.0, 10.0, 100.0));
	m_CircuitLait->addSousElement(new Tuyau(0.25, 5.0));
	m_CircuitLait->addSousElement(new Pompe(0.05f, 5.0));
	m_CircuitLait->addSousElement(new Tuyau(0.25, 5.0));
	m_CircuitLait->addSousElement(new Bouilloire(3.5, 10.0, 400.0));
	m_CircuitLait->addSousElement(new Tuyau(0.25, 5.0));

	// Constuire les elements du circuit pour le sucre
	m_CircuitSucre->addSousElement(new Moteur(2.5));
	m_CircuitSucre->addSousElement(new Receptacle(12.5, 15.0, 100));
	m_CircuitSucre->addSousElement(new Moteur(0.5));
	m_CircuitSucre->addSousElement(new Transmission(0.75, 5.0));

	// Constuire les elements du circuit de the
	m_CircuitSucre->addSousElement(new Moteur(2.5));
	m_CircuitThe->addSousElement(new Receptacle(12.5, 15.0, 100));
	m_CircuitThe->addSousElement(new Moteur(0.5));
	m_CircuitThe->addSousElement(new Transmission(0.75, 5.0));

}

MachineLuxe::~MachineLuxe(){

}


void MachineLuxe::infuserThe(float duree){
	m_CircuitThe->operer(duree);
	m_CircuitEauChaude->operer(duree);
	m_CircuitLait->operer(duree);
	m_CircuitSucre->operer(duree);
}



bool MachineLuxe::opACircuitLait(){

	return true;
}


bool MachineLuxe::opACircuitSucre(){

	return true;
}


void MachineLuxe::opNettoyerCircuitEau(){
	m_CircuitEauChaude->nettoyer();
}


void MachineLuxe::opNettoyerCircuitLait(){
	m_CircuitLait->nettoyer();
}


void MachineLuxe::opNettoyerCircuitSucre(){
	m_CircuitSucre->nettoyer();
}


void MachineLuxe::opNettoyerCircuitThe(){
	m_CircuitThe->nettoyer();
}


void MachineLuxe::opNettoyerFiltre(){
	m_filtre->nettoyer();
}

resultat_test MachineLuxe::opDiagnostiquerCircuitEau(){
	auto tartre = m_CircuitEauChaude->getTartre();
	return (tartre < SEUIL_TARTRE_MAX_EAU) ? resultat_test::succes : resultat_test::echec;
}


resultat_test MachineLuxe::opDiagnostiquerCircuitLait(){
	auto tartre = m_CircuitEauChaude->getTartre();
	return (tartre < SEUIL_TARTRE_MAX_LAIT) ? resultat_test::succes : resultat_test::echec;
}


resultat_test MachineLuxe::opDiagnostiquerCircuitSucre(){
	auto debris = m_CircuitThe->getDebris();
	return (debris < SEUIL_DEBRIS_MAX_SUCRE) ? resultat_test::succes : resultat_test::echec;
}


resultat_test MachineLuxe::opDiagnostiquerCircuitThe(){
	auto debris = m_CircuitThe->getDebris();
	return (debris < SEUIL_DEBRIS_MAX_THE) ? resultat_test::succes : resultat_test::echec;
}


resultat_test MachineLuxe::opDiagnostiquerFiltre(){
	return resultat_test::succes;
}