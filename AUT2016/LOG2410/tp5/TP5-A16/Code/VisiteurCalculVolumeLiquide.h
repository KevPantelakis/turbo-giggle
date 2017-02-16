///////////////////////////////////////////////////////////
//  VisiteurCalculVolumeLiquide.h
//  Implementation of the Class VisiteurCalculVolumeLiquide
//  Created on:      10-nov.-2016
//  Original author: francois
///////////////////////////////////////////////////////////

#if !defined(class_VisiteurCalculVolumeLiquide__INCLUDED_)
#define class_VisiteurCalculVolumeLiquide__INCLUDED_

#include "VisiteurSansEffet.h"

class VisiteurCalculVolumeLiquide : public VisiteurSansEffet
{
private:
	float _volumeTotal;
public:
	VisiteurCalculVolumeLiquide();
	virtual ~VisiteurCalculVolumeLiquide() {};

	// Methode de traitement des elements concrets des circuits liquides
	virtual void traiterBouilloire(Bouilloire* _bouil);
	virtual void traiterPompe(Pompe* _pomp);
	virtual void traiterReservoir(Reservoir* _reserv);
	virtual void traiterTuyau(Tuyau* _tuy);

	// Methode d'acces au volume total
	virtual float getVolumeTotal() const { return _volumeTotal; };
	virtual void resetVolumeTotal() { _volumeTotal = 0; }
};
#endif // class_VisiteurCalculVolumeLiquide__INCLUDED_#pragma once
