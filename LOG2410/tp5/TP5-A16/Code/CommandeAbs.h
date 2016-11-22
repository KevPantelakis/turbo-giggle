///////////////////////////////////////////////////////////
//  CommandeAbs.h
//  Implementation of the Class CommandeAbs
//  Created on:      10-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_CommandeAbs__INCLUDED_)
#define class_CommandeAbs__INCLUDED_

#include <memory>

class CommandeAbs
{
public:
	typedef std::shared_ptr<CommandeAbs> CommandeAbsPtr;

	CommandeAbs() {};
	virtual ~CommandeAbs() {};

	// Methode d'execution de la commande
	virtual void executer(class ElmVisitable* _elm) = 0;
};
#endif // class_CommandeAbs__INCLUDED_