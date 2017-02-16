///////////////////////////////////////////////////////////
//  Moteur.h
//  Implementation of the Class Moteur
//  Created on:      27-oct.-2016 15:12:31
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_2815D8AE_D6ED_458b_997A_3DB65BC13FEC__INCLUDED_)
#define EA_2815D8AE_D6ED_458b_997A_3DB65BC13FEC__INCLUDED_

#include "ElmCircuitSolide.h"

class Moteur : public ElmCircuitSolide
{
	float m_puissance;
public:
	Moteur( float p );
	virtual ~Moteur();

	virtual float getPuissance() const { return m_puissance; }

	virtual void operer( float duree );
	virtual void nettoyer();

	virtual void accepter(VisiteurAbs* _vis) { _vis->traiterMoteur(this); }
};
#endif // !defined(EA_2815D8AE_D6ED_458b_997A_3DB65BC13FEC__INCLUDED_)
