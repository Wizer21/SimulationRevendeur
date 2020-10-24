#include "Entreprise.h"

Entreprise::Entreprise()
{
  banque = 15320;
}

double Entreprise::getBanque()
{
  return banque;
}

void Entreprise::setBanque(double newBanque)
{
  banque = newBanque;
}
