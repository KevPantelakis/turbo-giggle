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

	// Diagnostiquer le filtre
	resultat_test res = resultat_test::succes;
	if (opDiagnostiquerFiltre() == resultat_test::echec)
	{
		std::cout << "Test Filtre: ECHEC" << std::endl;
		res = resultat_test::echec;
	}
	else
	{
		// Diagnostiquer le circuit d'eau chaude
		if (opDiagnostiquerCircuitEau() == resultat_test::echec)
		{
			std::cout << "Test EAU CHAUDE: ECHEC" << std::endl;
			res = resultat_test::echec;
		}
		else
		{
			// Diagnostiquer le circuit de the
			if (opDiagnostiquerCircuitThe() == resultat_test::echec)
			{
				std::cout << "Test THE: ECHEC" << std::endl;
				res = resultat_test::echec;
			}
			else
			{
				// Verifier si la machine a un circuit pour le lait, et si oui, le Diagnostiquer
				if (opACircuitLait())
				{
					if (opDiagnostiquerCircuitLait() == resultat_test::echec)
					{
						std::cout << "Test LAIT: ECHEC" << std::endl;
						res = resultat_test::echec;
					}
				}

				// Verifier si la machine a un circuit pour le sucre, et si oui, le Diagnostiquer
				if (res == resultat_test::succes && opACircuitSucre())
				{
					if (opDiagnostiquerCircuitSucre() == resultat_test::echec)
					{
						std::cout << "Test SUCRE: ECHEC" << std::endl;
						res = resultat_test::echec;
					}
				}
			}
		}
	}

	return res;
}


void MachineAbs::nettoyer(){
	// Methode servant a appeler les operations de nettoyage pour les differentes composantes de la machine
	
	// Nettoyer le filtre
	opNettoyerFiltre();

	// Nettoyer le circuit d'eau chaude
	opNettoyerCircuitEau();

	// Nettoyer le circuit de the
	opNettoyerCircuitThe();

	// Verifier si la machine a un circuit pour le lait, et si oui, le nettoyer
	if (opACircuitLait())
		opNettoyerCircuitLait();

	// Verifier si la machine a un circuit pour le sucre, et si oui, le nettoyer
	if (opACircuitSucre())
		opNettoyerCircuitSucre();
}

