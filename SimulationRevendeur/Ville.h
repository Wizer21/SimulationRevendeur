#pragma once
#include "stdafx.h"
#include "StaticRandomizer.h"
#include "stdafx.h"

class Ville
{

public:
  Ville::Ville(QString addNom, double addMultiplicateurGain, double addMultiplicateurFrais);
  QString getNom();
  double getMultiplicateurGain();
  double getFraisMultiplicateur();
  void setMultiplicateurGain(double value);
  void setFraisMultiplicateur(double value);
  QString randomEvent(int value);

private:
  QString nom;
  double multiplicateurGain;
  double multiplicateurFrais;
};
