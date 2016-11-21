///////////////////////////////////////////////////////////
//  VisiteurCalculVolumeLiquide.cpp
//  Implementation of the Class VisiteurCalculVolumeLiquide
//  Created on:      27-oct.-2016 15:21:34
//  Original author: francois
///////////////////////////////////////////////////////////

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "VisiteurCalculVolumeLiquide.h"

VisiteurCalculVolumeLiquide::VisiteurCalculVolumeLiquide()
	: _volumeTotal(0.0)
{
}

void VisiteurCalculVolumeLiquide::traiterBouilloire(Bouilloire* _bouil)
{
	// Calcul du volume de la bouilloire
	// A completer
}

void VisiteurCalculVolumeLiquide::traiterPompe(Pompe* _pomp)
{
	// Le volume de la pompe est une valeur fixe
	// A completer
}

void VisiteurCalculVolumeLiquide::traiterReservoir(Reservoir* _reserv)
{
	// Calcul du volume de la bouilloire
	// A completer
}

void VisiteurCalculVolumeLiquide::traiterTuyau(Tuyau* _tuy)
{
	// Calcul du volume de la bouilloire
	_volumeTotal += _tuy->getVolume();
}
