#include "Entreprise.h"

Entreprise::Entreprise()
{
  banque = 9264;
}

double Entreprise::getBanque()
{
  return banque;
}

void Entreprise::setBanque(double newBanque)
{
  banque = newBanque;
}

void Entreprise::setName(QString addName)
{
  nom = addName;
}

QString Entreprise::getName()
{
  return nom;
}
