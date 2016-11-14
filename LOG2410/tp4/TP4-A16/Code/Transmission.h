///////////////////////////////////////////////////////////
//  Transmission.h
//  Implementation of the Class Transmission
//  Created on:      27-oct.-2016 15:12:32
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_AB53D57F_FC9C_4c69_872F_2B216B782CFD__INCLUDED_)
#define EA_AB53D57F_FC9C_4c69_872F_2B216B782CFD__INCLUDED_

#include "ElmCircuitSolide.h"

class Transmission : public ElmCircuitSolide
{
	float m_largeur;
	float m_longueur;

public:
	Transmission( float la, float lo );
	virtual ~Transmission();

	virtual float getLargeur() const { return m_largeur; }
	virtual float getLongueur() const { return m_longueur; }

	virtual void operer( float duree );
	virtual void nettoyer();

};
#endif // !defined(EA_AB53D57F_FC9C_4c69_872F_2B216B782CFD__INCLUDED_)
