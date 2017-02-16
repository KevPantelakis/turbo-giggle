///////////////////////////////////////////////////////////
//  Bouilloire.h
//  Implementation of the Class Bouilloire
//  Created on:      27-oct.-2016 15:18:24
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_0000F826_4B89_414d_B3BF_F30F40A68BD6__INCLUDED_)
#define EA_0000F826_4B89_414d_B3BF_F30F40A68BD6__INCLUDED_

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "ElmCircuitLiquide.h"

class Bouilloire : public ElmCircuitLiquide
{
	float m_rayon;
	float m_hauteur;
	float m_temperature;
	float m_niveau;
	float m_puissance;

public:
	const float niveauMinimum = 10.0;

	Bouilloire(float _r, float _h, float _p);
	virtual ~Bouilloire();

	virtual float getRayon() const { return m_rayon; };
	virtual float getHauteur() const { return m_hauteur; };
	virtual float getNiveau() const { return m_niveau; };
	virtual float getVolume() const { return float(m_hauteur * M_PI * m_rayon * m_rayon); }
	virtual float getTemperature() const { return m_temperature; };
	virtual void setNiveau(float n) { m_niveau = n; }
	virtual void setTemperature(float t) { m_temperature = t; }
	virtual float getPuissance() const { return m_puissance; }

	virtual void operer( float duree );
	virtual void nettoyer();

	virtual void accepter(VisiteurAbs* _vis) { _vis->traiterBouilloire(this); }
};
#endif // !defined(EA_0000F826_4B89_414d_B3BF_F30F40A68BD6__INCLUDED_)
