///////////////////////////////////////////////////////////
//  Filtre.h
//  Implementation of the Class Filtre
//  Created on:      27-oct.-2016 15:21:34
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_Filtre__INCLUDED_)
#define class_Filtre__INCLUDED_

class Filtre
{
	int m_tartre;
	int m_debris;

protected:
	void removeTartre() { m_tartre = 0; }
	void removeDebris() { m_debris = 0; }

public:
	Filtre();
	virtual ~Filtre();

	virtual int getTartre();
	virtual void addTartre(int tartreAjoute);

	virtual int getDebris();
	virtual void addDebris(int debrisAjoute);

	virtual void operer( float duree );
	virtual void nettoyer();

};
#endif // class_Filtre__INCLUDED_