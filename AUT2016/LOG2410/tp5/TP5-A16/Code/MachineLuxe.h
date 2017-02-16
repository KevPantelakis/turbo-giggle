///////////////////////////////////////////////////////////
//  MachineLuxe.h
//  Implementation of the Class MachineLuxe
//  Created on:      27-oct.-2016 15:12:24
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_7F2837BF_4FA5_45d6_9744_DA985F7DF2E2__INCLUDED_)
#define EA_7F2837BF_4FA5_45d6_9744_DA985F7DF2E2__INCLUDED_

#include <memory>

#include "ElmCircuitLiquide.h"
#include "ElmCircuitSolide.h"
#include "MachineAbs.h"

class MachineLuxe : public MachineAbs
{
	std::shared_ptr<ElmCircuitLiquide> m_CircuitEauChaude;
	std::shared_ptr<ElmCircuitLiquide> m_CircuitLait;
	std::shared_ptr<ElmCircuitSolide> m_CircuitSucre;
	std::shared_ptr<ElmCircuitSolide> m_CircuitThe;

	friend class Test_TP5;

public:
	MachineLuxe();
	virtual ~MachineLuxe();

	virtual void infuserThe(float duree);

	virtual void executer(CommandeAbs* cmd) { cmd->executer(m_CircuitEauChaude.get()); }
protected:
	// Valeurs seuils pour le nettoyage
	const float SEUIL_TARTRE_MAX_EAU = 10.0;
	const float SEUIL_TARTRE_MAX_LAIT = 10.0;
	const float SEUIL_DEBRIS_MAX_SUCRE = 200;
	const float SEUIL_DEBRIS_MAX_THE = 200;

	// operations elementaires pour verifier les options
	virtual bool opACircuitLait();
	virtual bool opACircuitSucre();

	// operations elementaires de diagnostique
	virtual resultat_test opDiagnostiquerCircuitEau();
	virtual resultat_test opDiagnostiquerCircuitLait();
	virtual resultat_test opDiagnostiquerCircuitSucre();
	virtual resultat_test opDiagnostiquerCircuitThe();
	virtual resultat_test opDiagnostiquerFiltre();

	// operations elementaires de nettoyage
	virtual void opNettoyerCircuitEau();
	virtual void opNettoyerCircuitLait();
	virtual void opNettoyerCircuitSucre();
	virtual void opNettoyerCircuitThe();
	virtual void opNettoyerFiltre();
};
#endif // !defined(EA_7F2837BF_4FA5_45d6_9744_DA985F7DF2E2__INCLUDED_)
