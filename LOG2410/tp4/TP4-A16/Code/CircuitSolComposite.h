///////////////////////////////////////////////////////////
//  CircuitSolComposite.h
//  Implementation of the Class CircuitSolComposite
//  Created on:      27-oct.-2016 15:12:34
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_E5678016_8544_477e_9912_91DE377D2BF5__INCLUDED_)
#define EA_E5678016_8544_477e_9912_91DE377D2BF5__INCLUDED_

#include <vector>

#include "ElmCircuitSolide.h"

class CircuitSolComposite : public ElmCircuitSolide
{
	std::vector<ElmCircuitSolPtr> m_CircuitSolide;

public:
	CircuitSolComposite();
	virtual ~CircuitSolComposite();
	
	virtual ElmCircuitSolPtr getSousElement(size_t index);
	virtual const ElmCircuitSolPtr getSousElement(size_t index) const;
	virtual int nombreSousElements() const;
	virtual void addSousElement(const ElmCircuitSolPtr& sousElem);
	virtual void addSousElement(ElmCircuitSolide* sousElem);

	virtual float getDebris() const;

	virtual void operer(float duree);
	virtual void nettoyer();
};
#endif // !defined(EA_E5678016_8544_477e_9912_91DE377D2BF5__INCLUDED_)
