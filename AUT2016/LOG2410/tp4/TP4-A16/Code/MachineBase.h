///////////////////////////////////////////////////////////
//  MachineBase.h
//  Implementation of the Class MachineBase
//  Created on:      27-oct.-2016 15:12:17
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_76DD9B19_EF79_4e4a_B3CA_6DABC7246388__INCLUDED_)
#define EA_76DD9B19_EF79_4e4a_B3CA_6DABC7246388__INCLUDED_

#include <memory>

#include "ElmCircuitLiquide.h"
#include "ElmCircuitSolide.h"
#include "MachineAbs.h"

class MachineBase : public MachineAbs
{
	ElmCircuitLiquide::ElmCircuitLiqPtr m_CircuitEauChaude;
	ElmCircuitSolide::ElmCircuitSolPtr m_CircuitThe;

	friend class Test_TP4;

public:
	MachineBase();
	virtual ~MachineBase();

	virtual void infuserThe(float duree);

protected:
	// Valeurs seuils pour le nettoyage
	const float SEUIL_TARTRE_MAX_EAU = 10.0;
	const float SEUIL_DEBRIS_MAX_THE = 300;

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
#endif // !defined(EA_76DD9B19_EF79_4e4a_B3CA_6DABC7246388__INCLUDED_)
