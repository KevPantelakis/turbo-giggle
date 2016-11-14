///////////////////////////////////////////////////////////
//  Tuyau.h
//  Implementation of the Class Tuyau
//  Created on:      27-oct.-2016 15:19:37
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_A41D4A19_D079_4be8_8281_1D9BD981BDF8__INCLUDED_)
#define EA_A41D4A19_D079_4be8_8281_1D9BD981BDF8__INCLUDED_

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

	virtual void operer( float duree );
	virtual void nettoyer();

};
#endif // !defined(EA_A41D4A19_D079_4be8_8281_1D9BD981BDF8__INCLUDED_)
