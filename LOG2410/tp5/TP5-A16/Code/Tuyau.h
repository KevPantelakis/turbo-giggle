///////////////////////////////////////////////////////////
//  Tuyau.h
//  Implementation of the Class Tuyau
//  Created on:      27-oct.-2016 15:19:37
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_A41D4A19_D079_4be8_8281_1D9BD981BDF8__INCLUDED_)
#define EA_A41D4A19_D079_4be8_8281_1D9BD981BDF8__INCLUDED_

#define _USE_MATH_DEFINES
#include <math.h>

#include "ElmCircuitLiquide.h"

class Tuyau : public ElmCircuitLiquide
{
	float m_rayon;
	float m_longueur;

public:
	Tuyau( float r, float l );
	virtual ~Tuyau();

	virtual float getRayon() const { return m_rayon; }
	virtual float getLongueur() const { return m_longueur; }
	virtual float getVolume() const { return float(m_longueur * M_PI * m_rayon * m_rayon); }

	virtual void operer( float duree );
	virtual void nettoyer();

	virtual void accepter(VisiteurAbs* _vis) { _vis->traiterTuyau(this); }
};
#endif // !defined(EA_A41D4A19_D079_4be8_8281_1D9BD981BDF8__INCLUDED_)
