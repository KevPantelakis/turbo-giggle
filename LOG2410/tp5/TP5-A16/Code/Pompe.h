///////////////////////////////////////////////////////////
//  Pompe.h
//  Implementation of the Class Pompe
//  Created on:      27-oct.-2016 15:21:34
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_B00E7F8F_D196_4f0a_8FED_68527147A69D__INCLUDED_)
#define EA_B00E7F8F_D196_4f0a_8FED_68527147A69D__INCLUDED_

#include "ElmCircuitLiquide.h"

class Pompe : public ElmCircuitLiquide
{
	float m_debit;
	float m_puissance;
public:
	const float volumeLiquide = 45.0;

	Pompe( float _d, float _p );
	virtual ~Pompe();

	virtual float getDebit() const { return m_debit; }
	virtual float getPuissance() const { return m_puissance; }

	virtual void operer( float duree );
	virtual void nettoyer();

	virtual void accepter(VisiteurAbs* _vis) { _vis->traiterPompe(this); }
};
#endif // !defined(EA_B00E7F8F_D196_4f0a_8FED_68527147A69D__INCLUDED_)
