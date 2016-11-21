///////////////////////////////////////////////////////////
//  ElmCircuitSolide.h
//  Implementation of the Class ElmCircuitSolide
//  Created on:      27-oct.-2016 15:12:27
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_02E96EA1_87F2_42a4_9D3B_29358DF51272__INCLUDED_)
#define EA_02E96EA1_87F2_42a4_9D3B_29358DF51272__INCLUDED_

#include <memory>
#include <iostream>

#include "ElmVisitable.h"
#include "VisiteurAbs.h"

class ElmCircuitSolide : public ElmVisitable
{
	float m_debris;

protected:
	void addDebris(float debrisAjoute) { m_debris += debrisAjoute; }
	void removeDebris() { m_debris = 0; }
	float calculerAccumulationDebris(float duree, float aireSection);

public:
	typedef std::shared_ptr<ElmCircuitSolide> ElmCircuitSolPtr;

	ElmCircuitSolide();
	virtual ~ElmCircuitSolide();

	virtual ElmCircuitSolPtr getSousElement(size_t index);
	virtual const ElmCircuitSolPtr getSousElement(size_t index) const;
	virtual int nombreSousElements() const;
	virtual void addSousElement(const ElmCircuitSolPtr& sousElem);
	virtual void addSousElement(ElmCircuitSolide* sousElem);

	virtual float getDebris() const { return m_debris; };

	virtual void operer( float duree ) = 0;
	virtual void nettoyer() = 0;
};
#endif // !defined(EA_02E96EA1_87F2_42a4_9D3B_29358DF51272__INCLUDED_)
