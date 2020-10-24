#include "Employe.h"

Employe::Employe() {}

Employe::Employe(QString addNom, int addSalaire, int addForce, int addId)
{
  nom = addNom;
  salaire = addSalaire;
  force = addForce;
  id = addId;
}

QString Employe::getNom()
{
  return nom;
}

int Employe::getSalaire()
{
  return salaire;
}

int Employe::getForce()
{
  return force;
}

int Employe::getId()
{
  return id;
}