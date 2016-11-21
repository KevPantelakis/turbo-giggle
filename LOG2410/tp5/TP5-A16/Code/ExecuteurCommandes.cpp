///////////////////////////////////////////////////////////
//  ExecuteurCommandes.cpp
//  Implementation of the Class MachineBase
//  Created on:      15-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>

#include "ElmVisitable.h"
#include "ExecuteurCommandes.h"
#include "ProgrammeMachine.h"

std::shared_ptr<ExecuteurCommandes> ExecuteurCommandes::m_instance(nullptr);

const ExecuteurCommandes* ExecuteurCommandes::getInstance()
{
	if (m_instance == nullptr)
		m_instance = std::shared_ptr<ExecuteurCommandes>(new ExecuteurCommandes());
	return m_instance.get();
}

void ExecuteurCommandes::executer( ProgrammeMachine* _prog, ElmVisitable* _circuitCible) const
{
	// Itérer sur les chacune des commandes spécifiées dans le programme et les exécuter
	// A completer
}