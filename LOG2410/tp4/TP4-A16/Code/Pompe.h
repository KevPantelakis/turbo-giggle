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
public:
	Pompe( float d );
	virtual ~Pompe();

	virtual float getDebit() const { return m_debit; }

	virtual void operer( float duree );
	virtual void nettoyer();

};
#endif // !defined(EA_B00E7F8F_D196_4f0a_8FED_68527147A69D__INCLUDED_)
