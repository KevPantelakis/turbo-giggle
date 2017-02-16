///////////////////////////////////////////////////////////
//  VisiteurSansEffet.cpp
//  Implementation of the Class VisiteurSansEffet
//  Created on:      27-oct.-2016 15:21:34
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>

#include "VisiteurSansEffet.h"

VisiteurSansEffet::~VisiteurSansEffet()
{
}

void VisiteurSansEffet::traiterCircuitLiqComposite(CircuitLiqComposite* circ) 
{
	int nse = circ->nombreSousElements();
	for (int ise = 0; ise < nse; ++ise)
	{
		ElmCircuitLiquide::ElmCircuitLiqPtr sep = circ->getSousElement(ise);
		sep->accepter(this);
	}
};

void VisiteurSansEffet::traiterCircuitSolComposite(CircuitSolComposite* circ) 
{
	int nse = circ->nombreSousElements();
	for (int ise = 0; ise < nse; ++ise)
	{
		ElmCircuitSolide::ElmCircuitSolPtr sep = circ->getSousElement(ise);
		sep->accepter(this);
	}
};
