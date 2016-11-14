///////////////////////////////////////////////////////////
//  ElmCircuitLiquide.h
//  Implementation of the Class ElmCircuitLiquide
//  Created on:      27-oct.-2016 15:12:20
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_FE6F6F92_F638_4884_B7D0_07F3B88BD2E6__INCLUDED_)
#define EA_FE6F6F92_F638_4884_B7D0_07F3B88BD2E6__INCLUDED_

#include <memory>
#include <iostream>

class ElmCircuitLiquide
{
	float m_tartre;

protected:
	void addTartre(float tartreAjoute) { m_tartre += tartreAjoute; };
	void removeTartre() { m_tartre = 0; }
	float calculerAccumulationTartre(float duree, float longueur, float aireSection);

public:
	typedef std::shared_ptr<ElmCircuitLiquide> ElmCircuitLiqPtr;

	ElmCircuitLiquide();
	virtual ~ElmCircuitLiquide();

	virtual ElmCircuitLiqPtr getSousElement(size_t index);
	virtual const ElmCircuitLiqPtr getSousElement(size_t index) const;
	virtual int nombreSousElements() const;
	virtual void addSousElement(const ElmCircuitLiqPtr& sousElem);
	virtual void addSousElement(ElmCircuitLiquide* sousElem);

	virtual float getTartre() const { return m_tartre; };
	
	virtual void operer( float duree ) = 0;
	virtual void nettoyer() = 0;
};
#endif // !defined(EA_FE6F6F92_F638_4884_B7D0_07F3B88BD2E6__INCLUDED_)
