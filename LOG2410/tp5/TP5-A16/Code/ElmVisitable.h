///////////////////////////////////////////////////////////
//  ElmVisitable.h
//  Implementation of the Class ElmVisitable
//  Created on:      10-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_ElmVisitable__INCLUDED_)
#define class_ElmVisitable__INCLUDED_

class ElmVisitable
{
public:
	ElmVisitable() {};
	virtual ~ElmVisitable() {};

	// Methode permettant d'accepter un visiteur
	virtual void accepter(class VisiteurAbs* _vis) = 0;
};
#endif // class_ElmVisitable__INCLUDED_#pragma once
