/*****************************************************************************/
//  Test_TP4.h
//  Implementation of the Class Test_TP4
//  Created on:      2015-10-14
//  Modified on:     2016-10-26
//  Original author: El Houcine Boudoukha and Farouk Ouenniche
//  Modification:    Francois Guibault - Adapt to PolyInfusion
/*****************************************************************************/

#ifndef TEST_TP4_H
#define TEST_TP4_H


#include <memory>
#include <exception>

#include "MachineBase.h"
#include "MachineLuxe.h"

//
// Classe TestTP4
//
// Classe de test pour les elements implementes au TP4
//
class Test_TP4
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
	Test_TP4();
	~Test_TP4();

	// Tests
	void executeCompositeTest();      // Execute les tests sur les composites
	void executeTemplateMethodTest(); // Execute les tests sur les template methods

};

#endif// TEST_TP4_H
