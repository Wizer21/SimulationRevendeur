#pragma once

#include "stdafx.h"

class Entreprise
{
public:
  Entreprise(QString addNom);
  Entreprise();
  double getBanque();
  QString getName();
  void setBanque(double newBanque);
  void setName(QString addNom);

private:
  QString nom;
  double banque;
};
