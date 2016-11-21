///////////////////////////////////////////////////////////
//  CircuitLiqComposite.h
//  Implementation of the Class CircuitLiqComposite
//  Created on:      27-oct.-2016 15:19:51
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_759B8CBB_F1C9_4296_9026_365EC0076DDC__INCLUDED_)
#define EA_759B8CBB_F1C9_4296_9026_365EC0076DDC__INCLUDED_

#include <vector>

#include "ElmCircuitLiquide.h"

class CircuitLiqComposite : public ElmCircuitLiquide
{
	std::vector<ElmCircuitLiqPtr> m_CircuitLiquide;

public:
	CircuitLiqComposite();
	virtual ~CircuitLiqComposite();

	virtual ElmCircuitLiqPtr getSousElement(std::size_t index);
	virtual const ElmCircuitLiqPtr getSousElement(std::size_t index) const;
	virtual int nombreSousElements() const;
	virtual void addSousElement(const ElmCircuitLiqPtr& sousElem);
	virtual void addSousElement(ElmCircuitLiquide* sousElem);

	virtual float getTartre() const;

	virtual void operer(float duree);
	virtual void nettoyer();

	virtual void accepter(VisiteurAbs* _vis) { _vis->traiterCircuitLiqComposite(this); }
};
#endif // !defined(EA_759B8CBB_F1C9_4296_9026_365EC0076DDC__INCLUDED_)
