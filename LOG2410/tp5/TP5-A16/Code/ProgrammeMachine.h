///////////////////////////////////////////////////////////
//  ProgrammeMachine.h
//  Implementation of the Class ProgrammeMachine
//  Created on:      10-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_ProgrammeMachine__INCLUDED_)
#define class_ProgrammeMachine__INCLUDED_

#include <vector>

#include "CommandeAbs.h"

class ProgrammeMachine
{
	std::vector<CommandeAbs::CommandeAbsPtr> m_listeCommandes;

public:
	ProgrammeMachine() {};
	virtual ~ProgrammeMachine() {};

	virtual CommandeAbs::CommandeAbsPtr getCommande(std::size_t index);
	virtual const CommandeAbs::CommandeAbsPtr getCommande(std::size_t index) const;
	virtual int nombreCommandes() const;
	virtual void addCommande(const CommandeAbs::CommandeAbsPtr& sousElem);
	virtual void addCommande(CommandeAbs* sousElem);
};
#endif // class_ProgrammeMachine__INCLUDED_