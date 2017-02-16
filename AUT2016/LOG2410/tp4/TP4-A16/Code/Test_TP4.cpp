
#include "Test_TP4.h"

#include <iostream>

#include "MachineBase.h"
#include "MachineLuxe.h"

Test_TP4::Test_TP4()
: m_machine1(new MachineBase() ), m_machine2(new MachineLuxe() )
{
}

Test_TP4::~Test_TP4()
{
}

void Test_TP4::executeCompositeTest()
{
	std::cout << std::endl << std::endl << "------------------------- COMPOSITE -------------------------------" << std::endl << std::endl;
	std::cout << std::endl;

	// Verifier de facon intrusive la structure de la machine de base
	MachineBase* m1 = dynamic_cast<MachineBase*>(m_machine1.get());
	std::shared_ptr<ElmCircuitLiquide> circ1_eauChaude = m1->m_CircuitEauChaude;
	std::cout << "COMPOSITE test 1:" << ((circ1_eauChaude!=nullptr && circ1_eauChaude->nombreSousElements() == 6) ? "SUCCES" : "ECHEC") << std::endl;
	std::shared_ptr<ElmCircuitSolide> circ1_the = m1->m_CircuitThe;
	std::cout << "COMPOSITE test 2:" << ((circ1_the != nullptr && circ1_the->nombreSousElements() == 3) ? "SUCCES" : "ECHEC") << std::endl;

	// Verifier de facon intrusive la structure de la machine de luxe
	MachineLuxe* m2 = dynamic_cast<MachineLuxe*>(m_machine2.get());
	std::shared_ptr<ElmCircuitLiquide> circ2_eauChaude = m2->m_CircuitEauChaude;
	std::cout << "COMPOSITE test 3:" << ((circ2_eauChaude != nullptr && circ2_eauChaude->nombreSousElements() == 5) ? "SUCCES" : "ECHEC") << std::endl;
	std::shared_ptr<ElmCircuitLiquide> souscirc2_eauChaude = circ2_eauChaude->getSousElement(3);
	std::cout << "COMPOSITE test 4:" << ((souscirc2_eauChaude != nullptr && souscirc2_eauChaude->nombreSousElements() == 3) ? "SUCCES" : "ECHEC") << std::endl;
	std::shared_ptr<ElmCircuitLiquide> circ2_lait = m2->m_CircuitLait;
	std::cout << "COMPOSITE test 5:" << ((circ2_lait != nullptr && circ2_lait->nombreSousElements() == 6) ? "SUCCES" : "ECHEC") << std::endl;
	std::shared_ptr<ElmCircuitSolide> circ2_sucre = m2->m_CircuitSucre;
	std::cout << "COMPOSITE test 6:" << ((circ2_sucre != nullptr && circ2_sucre->nombreSousElements() == 3) ? "SUCCES" : "ECHEC") << std::endl;
	std::shared_ptr<ElmCircuitSolide> circ2_the = m2->m_CircuitThe;
	std::cout << "COMPOSITE test 7:" << ((circ2_the != nullptr && circ2_the->nombreSousElements() == 3) ? "SUCCES" : "ECHEC") << std::endl;

}

void Test_TP4::executeTemplateMethodTest()
{
	std::cout << std::endl << std::endl << "------------------------- TEMPLATE METHOD -------------------------------" << std::endl << std::endl;
	std::cout << std::endl;
	m_machine1->infuserThe(20.0);
	m_machine2->infuserThe(30.0);

	// Executer les diagnostiques sur les machines
	std::cout << std::endl << std::endl << "------------------------- DIAGNOSTIQUE DE LA 1ere MACHINE (1) ----------" << std::endl << std::endl;
	resultat_test res1 = m_machine1->diagnostiquer();
	std::cout << "TEMPLATE METHOD diagnostiquer (m1): " << ((res1 == resultat_test::succes) ? "SUCCES" : "ECHEC") << std::endl;

	std::cout << std::endl << std::endl << "------------------------- DIAGNOSTIQUE DE LA 2eme MACHINE (1) ----------" << std::endl << std::endl;
	resultat_test res2 = m_machine2->diagnostiquer();
	std::cout << "TEMPLATE METHOD diagnostiquer (m2): " << ((res2 == resultat_test::succes) ? "SUCCES" : "ECHEC") << std::endl;

	m_machine1->infuserThe(120.0);
	m_machine2->infuserThe(160.0);

	// Executer les diagnostiques sur les machines
	std::cout << std::endl << std::endl << "------------------------- DIAGNOSTIQUE DE LA 1ere MACHINE (2) ----------" << std::endl << std::endl;
	resultat_test res3 = m_machine1->diagnostiquer();
	std::cout << "TEMPLATE METHOD diagnostiquer (m1): " << ((res3 == resultat_test::echec) ? "SUCCES" : "ECHEC") << std::endl;

	std::cout << std::endl << std::endl << "------------------------- DIAGNOSTIQUE DE LA 2eme MACHINE (2) ----------" << std::endl << std::endl;
	resultat_test res4 = m_machine2->diagnostiquer();
	std::cout << "TEMPLATE METHOD diagnostiquer (m2): " << ((res4 == resultat_test::echec) ? "SUCCES" : "ECHEC") << std::endl;

	// Nettoyer les machines
	std::cout << std::endl << std::endl << "------------------------- NETTOYAGE DE LA 1ere MACHINE ----------------" << std::endl << std::endl;
	m_machine1->nettoyer();

	std::cout << std::endl << std::endl << "------------------------- NETTOYAGE DE LA 2eme MACHINE ----------------" << std::endl << std::endl;
	m_machine2->nettoyer();

	m_machine1->infuserThe(120.0);
	m_machine2->infuserThe(160.0);

	// Executer les diagnostiques sur les machines
	std::cout << std::endl << std::endl << "------------------------- DIAGNOSTIQUE DE LA 1ere MACHINE (3) ---------" << std::endl << std::endl;
	resultat_test res5 = m_machine1->diagnostiquer();
	std::cout << "TEMPLATE METHOD diagnostiquer (m1): " << ((res5 == resultat_test::succes) ? "SUCCES" : "ECHEC") << std::endl;

	std::cout << std::endl << std::endl << "------------------------- DIAGNOSTIQUE DE LA 2eme MACHINE (3) ---------" << std::endl << std::endl;
	resultat_test res6 = m_machine2->diagnostiquer();
	std::cout << "TEMPLATE METHOD diagnostiquer (m2): " << ((res6 == resultat_test::echec) ? "SUCCES" : "ECHEC") << std::endl;

}

void Test_TP4::printSuccess()
{
	std::cout << "[Reussi]" << std::endl;
}

void Test_TP4::printFailure()
{
	std::cout << "[Echec]" << std::endl;
}