///////////////////////////////////////////////////////////
//  Receptacle.h
//  Implementation of the Class Receptacle
//  Created on:      27-oct.-2016 15:20:09
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_FEE859FB_57BA_4907_A329_4D06BF1D28F1__INCLUDED_)
#define EA_FEE859FB_57BA_4907_A329_4D06BF1D28F1__INCLUDED_

#include "ElmCircuitSolide.h"

class Receptacle : public ElmCircuitSolide
{
	float m_rayon;
	float m_hauteur;
	float m_niveau;

public:
	Receptacle( float r, float h, float n );
	virtual ~Receptacle();

	virtual float getRayon() const { return m_rayon; };
	virtual float getHauteur() const { return m_hauteur; };
	virtual float getNiveau() const { return m_niveau; }
	virtual void setNiveau(float n) { m_niveau = n; }

	virtual void operer( float duree );
	virtual void nettoyer();

	virtual void accepter(VisiteurAbs* _vis) { _vis->traiterReceptacle(this); }
};
#endif // !defined(EA_FEE859FB_57BA_4907_A329_4D06BF1D28F1__INCLUDED_)
