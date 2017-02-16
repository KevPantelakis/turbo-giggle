///////////////////////////////////////////////////////////
//  Reservoir.h
//  Implementation of the Class Reservoir
//  Created on:      27-oct.-2016 15:12:25
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(EA_1AB97552_F013_41ee_BE43_DD469ACB00BE__INCLUDED_)
#define EA_1AB97552_F013_41ee_BE43_DD469ACB00BE__INCLUDED_

#include "ElmCircuitLiquide.h"

class Reservoir : public ElmCircuitLiquide
{
	float m_profondeur;
	float m_largeur;
	float m_hauteur;
	float m_niveau;

public:
	Reservoir( float p, float l, float h, float n );
	virtual ~Reservoir();

	virtual float getProfondeur() const { return m_profondeur; }
	virtual float getLargeur() const { return m_largeur; }
	virtual float getHauteur() const { return m_hauteur; }
	virtual float getNiveau() const { return m_niveau; }
	virtual void setNiveau(float n) { m_niveau = n; }

	virtual void operer( float duree );
	virtual void nettoyer();

};
#endif // !defined(EA_1AB97552_F013_41ee_BE43_DD469ACB00BE__INCLUDED_)
