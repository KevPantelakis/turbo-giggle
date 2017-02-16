///////////////////////////////////////////////////////////
//  ExecuteurCommandes.h
//  Implementation of the Class ExecuteurCommandes
//  Created on:      15-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_ExecuteurCommandes__INCLUDED_)
#define class_ExecuteurCommandes__INCLUDED_

#include <memory>

class ExecuteurCommandes
{
private:
	static std::shared_ptr<ExecuteurCommandes> m_instance;
	ExecuteurCommandes() {};

public:
	virtual ~ExecuteurCommandes() {};

	// Methode d'acces a l'instance de l'executeur de commande
	static const ExecuteurCommandes* getInstance();

	// Methode d'execution de la commande
	virtual void executer(class ProgrammeMachine* _prog, class ElmVisitable* _circuitCible) const;
};
#endif // class_ExecuteurCommandes__INCLUDED_#pragma once
