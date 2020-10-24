#pragma once
#include "stdafx.h"

class Employe
{
public:
  Employe();
  Employe(QString addNom, int addSalaire, int addForce, int addId);

  QString getNom();
  int getSalaire();
  int getForce();
  int getId();

private:
  QString nom;
  int salaire;
  int force;
  int id;
};
