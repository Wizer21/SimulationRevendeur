#include "Item.h"

Item::Item(QString addNom, double addPA, double addPV, int addStock, int addAscendence, int addPoid, int addId)
{
  nom = addNom;
  prixAchat = addPA;
  prixVente = addPV;
  stock = addStock;
  ascendence = addAscendence;
  poid = addPoid;
  id = addId;
}

Item::Item(double addPvTotal, int addForce, int addQuantiteVendue)
{
  pvTotal = addPvTotal;
  poid = addForce;
  quantiteVendue = addQuantiteVendue;
}

// Get
QString Item::getNom()
{
  return nom;
}

double Item::getPA()
{
  return prixAchat;
}

double Item::getPV()
{
  return prixVente;
}

int Item::getStock()
{
  return stock;
}

int Item::getAscendence()
{
  return ascendence;
}

int Item::getId()
{
  return id;
}

double Item::getPvTotal()
{
  return pvTotal;
}

int Item::getPoid()
{
  return poid;
}

int Item::getQuantiteVendue()
{
  return quantiteVendue;
}

// Set
void Item::setStock(int newStock)
{
  stock = newStock;
}

void Item::setPvTotal(double value)
{
  pvTotal = value;
}

void Item::setPoid(int value)
{
  poid = value;
}

void Item::setQuantiteVendue(int value)
{
  quantiteVendue = value;
}