/*****************************************************************************/
//  Test_TP5.h
//  Implementation of the Class Test_TP5
//  Created on:      2015-10-14
//  Modified on:     2016-10-26
//  Original author: El Houcine Boudoukha and Farouk Ouenniche
//  Modification:    Francois Guibault - Adapt to PolyInfusion
/*****************************************************************************/

#ifndef TEST_TP5_H
#define TEST_TP5_H


#include <memory>
#include <exception>

#include "MachineBase.h"
#include "MachineLuxe.h"

//
// Classe TestTP5
//
// Classe de test pour les elements implementes au TP5
//
class Test_TP5
{
private:
	std::shared_ptr<MachineAbs> m_machine1;
	std::shared_ptr<MachineAbs> m_machine2;

protected:
	void printSuccess();
	void printFailure();

public:

	//-------------------------------------------
	// Constructeur & Destructeur
	//-------------------------------------------
	Test_TP5();
	~Test_TP5();

	// Tests
	void executeCompositeTest();      // Execute les tests sur les composites
	void executeTemplateMethodTest(); // Execute les tests sur les template methods
	void executeVisiteurTest();		  // Execute les tests sur les visiteurs
	void executeCommandeTest();		  // Execute les tests sur les commandes
};

#endif// TEST_TP5_H
