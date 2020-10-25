#pragma once

#include <QDialog>
#include "stdafx.h"
#include "Entreprise.h"
#include "Item.h"
#include "Employe.h"
#include "Ville.h"
#include "StaticRandomizer.h"

class EspaceDeVente : public QDialog
{
  Q_OBJECT

public:
  EspaceDeVente(QWidget* parent, std::vector<Item>& itemList, std::vector<Employe>& listEmploye, std::vector<Ville>& villeListRef, double addPoidMax);
  ~EspaceDeVente();

public slots:
  void sliderDragged(int value);
  void validButton();

signals:
  void localNewBanque(double value);
  void transfertsSalaireEtGain(double marge, double fraisPort);

private:
  double estimationPrixFinal;
  int poidMax;
  int poidActuel;
  double francoPort;

  std::vector<Ville>* pointeurVille;
  std::vector<Item>* pointeurItemList;
  std::vector<Item> listeTemporaire;
  std::vector<Employe>* listEmploye;

  QButtonGroup* groupCheckBox;
  QLineEdit* displayGain;
  QLineEdit* displayForce;
  QLineEdit* displayFrais;
  QProgressBar* forceBar;
  QLabel* tropLourd;

  void ini(QGridLayout* mainLayout);
  void iniItemList(QGridLayout* layoutArea);
  void iniVille(QGridLayout* layoutArea);
  void calculForceEtPrixMax();
  void calculFranco();
};
