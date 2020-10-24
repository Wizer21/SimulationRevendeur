#pragma once
#include "ui_SimulationRevendeur.h"
#include <QtWidgets/QMainWindow>
#include "stdafx.h"
#include "Item.h"
#include "Entreprise.h"
#include "Employe.h"
#include <QtCharts/QLineSeries>
#include <QChart>
#include <QChartView>
#include <QtDataVisualization>
#include "NouveauMois.h"
#include "NouvelEmployee.h"
#include "OpenViewer.h"
#include <time.h>
#include "EspaceDeVente.h"
#include "Ville.h"
#include <QValueAxis>

using namespace QtCharts;
using namespace QtDataVisualization;

class SimulationRevendeur : public QMainWindow
{
  Q_OBJECT

public:
  SimulationRevendeur(QWidget* parent = Q_NULLPTR);

public slots:
  void newAchat();
  void manageEmployeClicked();
  void venteClicked();
  void show3DGraph();
  void setNewBanque(double value);
  void setDial(int value);

private:
  void ini(QGridLayout* mainLayout);
  void iniDefaultList();
  void iniMenuBar(QMenuBar* barPointeur);
  bool checkID(int idTest);
  QChartView* ini2DEmploye();
  QChartView* ini2DEntreprise();
  void calculForce_SalaireMax();
  void updateList(QTableWidget* pointeurTable);
  void updateEmptrepriseValue();
  void addNews();

  int idSet;
  int mois;
  int totalForce;
  int totalSalaire;
  int totalSalaireDial;
  int posX;
  double maxBanque;
  QChartView* employeGraph;
  QChartView* entrepriseGraph;
  QLCDNumber* banque;
  Entreprise* pointeurEntreprise;
  QTableWidget* view;
  QChart* chartBank;

  QValueAxis* axeVertical;
  QValueAxis* axeHorizontal;
  QLineSeries* lineCout;
  QLineSeries* lineForce;
  QLineSeries* lineBanque;
  QLineSeries* lineSalaire;

  QLineEdit* displayForce;
  QLineEdit* displayNbrEmploye;
  QVBoxLayout* layoutNews;

  std::vector<Ville> villeList;
  std::vector<Item> itemList;
  std::vector<Employe> employeList;
  std::vector<double> historiqueBanque;
  Ui::SimulationRevendeurClass ui;
};
