///////////////////////////////////////////////////////////
//  Bouilloire.h
//  Implementation of the Class Bouilloire
//  Created on:      27-oct.-2016 15:18:24
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_0000F826_4B89_414d_B3BF_F30F40A68BD6__INCLUDED_)
#define EA_0000F826_4B89_414d_B3BF_F30F40A68BD6__INCLUDED_

#include "ElmCircuitLiquide.h"

class Bouilloire : public ElmCircuitLiquide
{
	float m_rayon;
	float m_hauteur;
	float m_temperature;

public:
	Bouilloire(float r, float h);
	virtual ~Bouilloire();

	virtual float getRayon() const { return m_rayon; };
	virtual float getHauteur() const { return m_hauteur; };
	virtual float getTemperature() const { return m_temperature; };
	virtual void setTemperature(float t) { m_temperature = t; }

	virtual void operer( float duree );
	virtual void nettoyer();

};
#endif // !defined(EA_0000F826_4B89_414d_B3BF_F30F40A68BD6__INCLUDED_)
