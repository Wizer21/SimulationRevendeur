#pragma once
#include "stdafx.h"
#include "StaticRandomizer.h"

class Ville
{

public:
  Ville::Ville(const QString& addNom, double addMultiplicateurGain, double addMultiplicateurFrais);
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
