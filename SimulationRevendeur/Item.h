#pragma once
#include "stdafx.h"

class Item
{
public:
  Item(QString addNom, double addPA, double addPV, int addStock, int addAscendence, int addPoid, int addId);
  Item(double addPvTotal, int addForce, int quantiteVendue);

  QString getNom();
  double getPA();
  double getPV();
  int getStock();
  int getAscendence();
  int getId();
  int getPoid();
  double getPvTotal();
  int getQuantiteVendue();

  void setStock(int newStock);
  void setPvTotal(double value);
  void setPoid(int value);
  void setQuantiteVendue(int value);

private:
  QString nom;
  double prixAchat;
  double prixVente;
  int stock;
  int ascendence;
  int quantiteVendue;

  double pvTotal;
  int poid;
  int id;
};
