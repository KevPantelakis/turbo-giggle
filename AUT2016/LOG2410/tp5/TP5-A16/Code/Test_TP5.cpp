
#include "Test_TP5.h"

#include <iostream>

#include "MachineBase.h"
#include "MachineLuxe.h"

#include "VisiteurCalculVolumeLiquide.h"
#include "VisiteurCalculerPuissance.h"

#include "CommandeFixerTemperatureLiquide.h"

Test_TP5::Test_TP5()
: m_machine1(new MachineBase() ), m_machine2(new MachineLuxe() )
{
}

Test_TP5::~Test_TP5()
{
}

void Test_TP5::executeVisiteurTest()
{
	std::cout << std::endl << std::endl << "------------------------- VISITEUR -------------------------------" << std::endl << std::endl;
	std::cout << std::endl;

	// Appliquer de facon intrusive les visiteurs aux elements de la machine de base
	MachineBase* m1 = dynamic_cast<MachineBase*>(m_machine1.get());
	std::shared_ptr<ElmCircuitLiquide> circ1_eauChaude = m1->m_CircuitEauChaude;
	VisiteurCalculVolumeLiquide visCalcVol;
	circ1_eauChaude->accepter(&visCalcVol);
	std::cout << "Volume de liquide de m1: " << visCalcVol.getVolumeTotal() << std::endl;
	std::cout << "VISITEUR test 1:" << (fabs(visCalcVol.getVolumeTotal() - 4200) < 2.0 ? "SUCCES" : "ECHEC") << std::endl;
	visCalcVol.resetVolumeTotal();

	std::shared_ptr<ElmCircuitSolide> circ1_the = m1->m_CircuitThe;
	VisiteurCalculerPuissance visCalcPuiss;
	circ1_eauChaude->accepter(&visCalcPuiss);
	circ1_the->accepter(&visCalcPuiss);
	std::cout << "Puissance totale consommee par la machine 1: " << visCalcPuiss.getPuissanceTotale() << std::endl;
	std::cout << "VISITEUR test 2:" << (fabs(visCalcPuiss.getPuissanceTotale() - 515.5) < 0.1 ? "SUCCES" : "ECHEC") << std::endl;
	visCalcPuiss.resetPuissanceTotale();

	// Appliquer de facon intrusive les visiteurs aux elements de la machine de luxe
	MachineLuxe* m2 = dynamic_cast<MachineLuxe*>(m_machine2.get());
	std::shared_ptr<ElmCircuitLiquide> circ2_eauChaude = m2->m_CircuitEauChaude;
	std::shared_ptr<ElmCircuitLiquide> circ2_lait = m2->m_CircuitLait;
	circ2_eauChaude->accepter(&visCalcVol);
	circ2_lait->accepter(&visCalcVol);
	std::cout << "Volume de liquide de m2: " << visCalcVol.getVolumeTotal() << std::endl;
	std::cout << "VISITEUR test 3:" << (fabs(visCalcVol.getVolumeTotal() - 5595.0) < 2.0 ? "SUCCES" : "ECHEC") << std::endl;
	visCalcVol.resetVolumeTotal();

	std::shared_ptr<ElmCircuitSolide> circ2_the = m2->m_CircuitThe;
	std::shared_ptr<ElmCircuitSolide> circ2_sucre = m2->m_CircuitSucre;
	circ2_eauChaude->accepter(&visCalcPuiss);
	circ2_lait->accepter(&visCalcPuiss);
	circ2_the->accepter(&visCalcPuiss);
	circ2_sucre->accepter(&visCalcPuiss);
	std::cout << "Puissance totale consommee par la machine m2: " << visCalcPuiss.getPuissanceTotale() << std::endl;
	std::cout << "VISITEUR test 4:" << (fabs(visCalcPuiss.getPuissanceTotale() - 968.5) < 0.1 ? "SUCCES" : "ECHEC") << std::endl;
	visCalcVol.resetVolumeTotal();
}

void Test_TP5::executeCommandeTest()
{
	std::cout << std::endl << std::endl << "------------------------- COMMAND -------------------------------" << std::endl << std::endl;
	std::cout << std::endl;
	try {
		m_machine1->infuserThe(100.0);
		std::cout << "COMMANDE test 1: SUCCES" << std::endl;

		// Verifier de facon intrusive si le niveau dans le reservoir a ete change
		MachineBase* m1 = dynamic_cast<MachineBase*>(m_machine1.get());
		std::shared_ptr<ElmCircuitLiquide> circ1_eauChaude = m1->m_CircuitEauChaude;
		ElmCircuitLiquide::ElmCircuitLiqPtr elmp = circ1_eauChaude->getSousElement(0);
		Reservoir* reservp = dynamic_cast<Reservoir*>(elmp.get());
		if (reservp != nullptr)
		{
			std::cout << "COMMANDE test 2: " << ((reservp->getNiveau() == 2050) ? "SUCCES" : "ECHEC") << std::endl;
		}
	}

	catch (std::exception& except)
	{
		except.what();
	}
}

void Test_TP5::printSuccess()
{
	std::cout << "[Reussi]" << std::endl;
}

void Test_TP5::printFailure()
{
	std::cout << "[Echec]" << std::endl;
}