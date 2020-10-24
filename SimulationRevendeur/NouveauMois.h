#pragma once

#include <QWidget>
#include "stdafx.h"
#include "Item.h"
#include "Entreprise.h"
#include "StaticRandomizer.h"

class NouveauMois : public QDialog
{
  Q_OBJECT

public:
  NouveauMois(QWidget* parent, std::vector<Item>& getList, Entreprise* getEntreprise);
  ~NouveauMois();

public slots:
  void orderPrice(QString);
  void validButtonClicked();

private:
  int setID;
  double coutTotal;
  QLabel* erreur;
  Entreprise* pointeurEntreprise;
  std::vector<Item>* pointeurList;
  QLineEdit* displayNouveauSolde;

  void ini(QVBoxLayout* mainLayout, std::vector<Item>& getList);
  void iniItemList(QVBoxLayout* mainLayout, std::vector<Item>& getList);
  void setFacturtion();
};
