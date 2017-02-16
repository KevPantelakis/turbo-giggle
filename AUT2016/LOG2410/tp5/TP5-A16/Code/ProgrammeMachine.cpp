///////////////////////////////////////////////////////////
//  ProgrammeMachine.cpp
//  Implementation of the Class MachineAbs
//  Created on:      15-nov.-2016 15:12:15
//  Original author: francois
///////////////////////////////////////////////////////////

#include "ProgrammeMachine.h"

CommandeAbs::CommandeAbsPtr ProgrammeMachine::getCommande(std::size_t index)
{
	return m_listeCommandes[index];
}

const CommandeAbs::CommandeAbsPtr ProgrammeMachine::getCommande(std::size_t index) const
{
	return m_listeCommandes[index];
}

int ProgrammeMachine::nombreCommandes() const
{
	return m_listeCommandes.size();
}

void ProgrammeMachine::addCommande(const CommandeAbs::CommandeAbsPtr & sousElem)
{
	m_listeCommandes.push_back(sousElem);
}

void ProgrammeMachine::addCommande(CommandeAbs* sousElem)
{
	m_listeCommandes.push_back(CommandeAbs::CommandeAbsPtr(sousElem));
}


