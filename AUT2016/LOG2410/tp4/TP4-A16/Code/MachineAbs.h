///////////////////////////////////////////////////////////
//  MachineAbs.h
//  Implementation of the Class MachineAbs
//  Created on:      27-oct.-2016 15:12:15
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_5266E575_96DD_411d_953A_44CE3ED80DA7__INCLUDED_)
#define EA_5266E575_96DD_411d_953A_44CE3ED80DA7__INCLUDED_

#include <memory>

#include "Filtre.h"
#include "resultat_test.h"

class MachineAbs
{
public:
	typedef std::shared_ptr<Filtre> FiltrePtr;

protected:
	FiltrePtr m_filtre;

public:
	MachineAbs( FiltrePtr f);
	virtual ~MachineAbs();

	virtual void infuserThe( float duree ) = 0;

	resultat_test diagnostiquer();
	void nettoyer();

protected:
	// operations elementaires pour verifier les options
	virtual bool opACircuitLait() = 0;
	virtual bool opACircuitSucre() = 0;

	// operations elementaires de diagnostique
	virtual resultat_test opDiagnostiquerCircuitEau() = 0;
	virtual resultat_test opDiagnostiquerCircuitLait() = 0;
	virtual resultat_test opDiagnostiquerCircuitSucre() = 0;
	virtual resultat_test opDiagnostiquerCircuitThe() = 0;
	virtual resultat_test opDiagnostiquerFiltre() = 0;

	// operations elementaires de nettoyage
	virtual void opNettoyerCircuitEau() = 0;
	virtual void opNettoyerCircuitLait() = 0;
	virtual void opNettoyerCircuitSucre() = 0;
	virtual void opNettoyerCircuitThe() = 0;
	virtual void opNettoyerFiltre() = 0;

};
#endif // !defined(EA_5266E575_96DD_411d_953A_44CE3ED80DA7__INCLUDED_)
