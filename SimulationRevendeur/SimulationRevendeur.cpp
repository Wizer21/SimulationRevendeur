#include "SimulationRevendeur.h"
#include "stdafx.h"

SimulationRevendeur::SimulationRevendeur(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
}

void SimulationRevendeur::setEntreprise(Entreprise& entrepriseGet)
{
  pointeurEntreprise = entrepriseGet;
  iniInterface();
}

void SimulationRevendeur::iniInterface()
{
  srand(time(NULL));
  idSet = 1;
  jour = 0;
  mois = 3;
  totalForce = 0;
  totalSalaire = 0;
  salaireOldPos = 0;
  posX = 0;
  maxBanque = 0;

  QMenuBar* menuBar = new QMenuBar(this);
  this->setMenuBar(menuBar);
  iniMenuBar(menuBar);
  QGridLayout* mainGrid = new QGridLayout(this->ui.centralWidget);

  iniDefaultList();
  ini(mainGrid);
  setDefaultGraphValue();
}

void SimulationRevendeur::iniMenuBar(QMenuBar* barPointeur)
{
  QMenu* visualizer = new QMenu(tr("Visualiseur"), this);
  QMenu* optionMenu = new QMenu(tr("Option"), this);
  QAction* option = new QAction(tr("Option"), this);
  QAction* open3d = new QAction(tr("Ouvrir Visualiseur 3D"), this);

  barPointeur->addMenu(optionMenu);
  barPointeur->addMenu(visualizer);
  optionMenu->addAction(option);
  visualizer->addAction(open3d);

  connect(option, SIGNAL(triggered()), this, SLOT(openOption()));
  connect(open3d, SIGNAL(triggered()), this, SLOT(show3DGraph()));
}

void SimulationRevendeur::ini(QGridLayout* mainLayout)
{
  //1 Gauche
  QWidget* widgetZone1 = new QWidget(this);
  QGridLayout* layoutMainPartie1 = new QGridLayout(this);
  QLabel* titre = new QLabel(pointeurEntreprise.getName(), this);
  date = new QLabel("00/00/20", this);
  QPushButton* achatButton = new QPushButton(tr("Achat"), this);

  //Tab
  QTabWidget* tabNews = new QTabWidget(this);

  QScrollArea* scrollNews = new QScrollArea(this);
  QWidget* newWidget = new QWidget(this);
  layoutNews = new QVBoxLayout(this);

  QScrollArea* scrollEntreprise = new QScrollArea(this);
  QWidget* widgetEntreprise = new QWidget(this);
  layoutNewsEntreprise = new QVBoxLayout(this);

  //Tableau
  QWidget* widgetTableau = new QWidget(this);
  QHBoxLayout* layoutTableau = new QHBoxLayout(this);
  view = new QTableWidget(5, 2, this);
  QStringList headersList;

  tabNews->addTab(scrollNews, tr("Nouveautés Mondiales"));
  tabNews->addTab(scrollEntreprise, tr("Entreprise"));

  mainLayout->addWidget(widgetZone1, 0, 0);
  widgetZone1->setLayout(layoutMainPartie1);
  layoutMainPartie1->addWidget(titre, 0, 0, 1, 2);
  layoutMainPartie1->addWidget(date, 1, 0, 1, 2);
  layoutMainPartie1->addWidget(achatButton, 0, 2, 2, 1);
  layoutMainPartie1->addWidget(tabNews, 2, 0, 2, 3);

  achatButton->setMinimumHeight(achatButton->height() * 2);
  achatButton->setMinimumWidth(achatButton->height() * 2);
  achatButton->setMaximumHeight(achatButton->height() * 2);
  achatButton->setMaximumWidth(achatButton->height() * 2);
  tabNews->setMinimumHeight(this->height() * 0.5);

  // Tab
  scrollNews->setWidget(newWidget);
  newWidget->setLayout(layoutNews);
  scrollEntreprise->setWidget(widgetEntreprise);
  widgetEntreprise->setLayout(layoutNewsEntreprise);

  layoutMainPartie1->addWidget(widgetTableau, 4, 0, 2, 3);

  headersList << tr("Nom")
              << tr("Stock");
  date->setFont(QFont("", 20));
  titre->setFont(QFont("", 50));
  layoutNews->setAlignment(Qt::AlignTop);
  layoutNews->setContentsMargins(5, 0, 0, 0);
  scrollNews->setWidgetResizable(true);
  layoutNewsEntreprise->setAlignment(Qt::AlignTop);
  layoutNewsEntreprise->setContentsMargins(5, 0, 0, 0);
  scrollEntreprise->setWidgetResizable(true);

  view->setMinimumWidth(this->width() * 0.6);
  view->setHorizontalHeaderLabels(headersList);

  widgetTableau->setLayout(layoutTableau);
  layoutTableau->addWidget(view);

  updateList(view);

  //2 Droite
  QWidget* widgetZone2 = new QWidget(this);
  QGridLayout* layoutMainPartie2 = new QGridLayout(this);
  QLabel* nbrEmploye = new QLabel(tr("Nombre d'Employee"), this);
  displayNbrEmploye = new QLineEdit("2", this);
  QPushButton* manageEmploye = new QPushButton(tr("Gestionnaire Employe"), this);
  QPushButton* vente = new QPushButton(tr("Vendre"), this);
  banque = new QLCDNumber(this);

  forceHorraire = new QDial(this);
  QLabel* chargeDesEmploye = new QLabel(tr("Charge Employee"), this);
  displayForce = new QLineEdit("100%", this);

  mainLayout->addWidget(widgetZone2, 0, 1);
  widgetZone2->setLayout(layoutMainPartie2);
  layoutMainPartie2->addWidget(nbrEmploye, 0, 0);
  layoutMainPartie2->addWidget(displayNbrEmploye, 0, 1);
  layoutMainPartie2->addWidget(manageEmploye, 1, 0, 1, 2);
  layoutMainPartie2->addWidget(banque, 2, 0, 1, 2);
  layoutMainPartie2->addWidget(vente, 3, 0, 1, 2);

  layoutMainPartie2->addWidget(forceHorraire, 0, 2, 2, 1);
  layoutMainPartie2->addWidget(chargeDesEmploye, 2, 2, 1, 1);
  layoutMainPartie2->addWidget(displayForce, 3, 2, 1, 1);

  layoutMainPartie2->addWidget(ini2DEntreprise(), 4, 0, 4, 4);

  displayForce->setReadOnly(true);
  forceHorraire->setSliderPosition(100);
  forceHorraire->setNotchesVisible(true);
  forceHorraire->setRange(0, 120);
  manageEmploye->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  vente->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  banque->setMinimumHeight(displayNbrEmploye->height() * 1.2);
  banque->display(pointeurEntreprise.getBanque());

  connect(forceHorraire, SIGNAL(valueChanged(int)), this, SLOT(setDial(int)));
  connect(achatButton, SIGNAL(clicked()), this, SLOT(newAchat()));
  connect(manageEmploye, SIGNAL(clicked()), this, SLOT(manageEmployeClicked()));
  connect(vente, SIGNAL(clicked()), this, SLOT(venteClicked()));
}

void SimulationRevendeur::updateList(QTableWidget* pointeurTable)
{
  int x = 0;
  int y = 0;
  int rowNumber = 0;
  for (int i = 0; i < itemList.size(); i++)
  {
    pointeurTable->setRowCount(++rowNumber);
    QTableWidgetItem* nameContainer = new QTableWidgetItem(itemList.at(i).getNom());
    QTableWidgetItem* stockContainer = new QTableWidgetItem(QString::number(itemList.at(i).getStock()));
    pointeurTable->setItem(x, y++, nameContainer);
    pointeurTable->setItem(x++, y--, stockContainer);
  }
}

// Set Listes
void SimulationRevendeur::iniDefaultList()
{
  Item item1("PS4", 246, 500, 0, 0, 24, idSet++);
  Item item2("XBOX", 223, 486, 0, 0, 23, idSet++);
  Item item3("Nier Automata", 21, 46, 0, 0, 12, idSet++);
  Item item4("Dofus", 15, 36, 0, 0, 8, idSet++);
  Item item5("POP Mercy", 8.46, 14.99, 0, 0, 3, idSet++);

  itemList.push_back(item1);
  itemList.push_back(item2);
  itemList.push_back(item3);
  itemList.push_back(item4);
  itemList.push_back(item5);

  Employe employe1("Bob", 1243, 246, 0);
  Employe employe2("Marcel", 1134, 153, 1);

  employeList.push_back(employe1);
  employeList.push_back(employe2);

  Ville paris(tr("Paris"), 1, 1);
  Ville londres(tr("Londres"), 1, 1);
  Ville tokyo(tr("Tokyo"), 1, 1);

  villeList.push_back(paris);
  villeList.push_back(londres);
  villeList.push_back(tokyo);
}

void SimulationRevendeur::setDefaultGraphValue()
{
  lineBanque->append(jour, 3257);
  lineSalaire->append(jour++, 1890);

  lineBanque->append(jour, 7200);
  lineSalaire->append(jour++, 2030);

  lineBanque->append(jour, 4905);
  lineSalaire->append(jour++, 2924);

  historiqueBanque.push_back(3257);
  historiqueBanque.push_back(7200);
  historiqueBanque.push_back(4905);

  calculForce_SalaireMax();
  updateEmptrepriseValue();
  addNews();
}

bool SimulationRevendeur::checkID(int idTest)
{
  for (int i = 0; i < itemList.size(); i++)
  {
    if (itemList.at(i).getId() == idTest)
    {
      return false;
    }
  }
  return true;
}

QChartView* SimulationRevendeur::ini2DEntreprise()
{
  chartBank = new QChart();

  lineBanque = new QLineSeries();
  lineSalaire = new QLineSeries();

  lineBanque->setName(tr("Fond disponibles"));
  lineSalaire->setName(tr("Cumul des salaires"));

  axeVertical = new QValueAxis(this);
  axeHorizontal = new QValueAxis(this);

  chartBank->setMargins(QMargins(0, 0, 0, 0));

  entrepriseGraph = new QChartView(chartBank);
  entrepriseGraph->setMinimumHeight(entrepriseGraph->width() / 2);
  entrepriseGraph->setRenderHint(QPainter::Antialiasing);

  chartBank->addAxis(axeVertical, Qt::AlignLeft);
  chartBank->addAxis(axeHorizontal, Qt::AlignBottom);

  chartBank->addSeries(lineBanque);
  chartBank->addSeries(lineSalaire);
  lineBanque->attachAxis(axeHorizontal);
  lineBanque->attachAxis(axeVertical);
  lineSalaire->attachAxis(axeHorizontal);
  lineSalaire->attachAxis(axeVertical);

  calculForce_SalaireMax();

  return entrepriseGraph;
}

void SimulationRevendeur::updateEmptrepriseValue()
{
  historiqueBanque.push_back(pointeurEntreprise.getBanque());

  lineBanque->append(jour, pointeurEntreprise.getBanque());
  lineSalaire->append(jour, salaireOldPos);

  axeHorizontal->setMax(jour * 1.5);

  if (maxBanque < pointeurEntreprise.getBanque())
  {
    maxBanque = pointeurEntreprise.getBanque();
    axeVertical->setMax(pointeurEntreprise.getBanque() * 1.2);
  }
}

void SimulationRevendeur::calculForce_SalaireMax()
{
  int forceTemporaire = 0;
  int salaireTemporaire = 0;

  for (int i = 0; i < employeList.size(); i++)
  {
    forceTemporaire += employeList.at(i).getForce();
    salaireTemporaire += employeList.at(i).getSalaire();
  }
  totalForce = forceTemporaire;
  totalSalaire = salaireTemporaire;
  salaireOldPos = salaireTemporaire * (forceHorraire->value() * 0.01);
}

void SimulationRevendeur::manageEmployeClicked()
{

  int oldSalairemax = salaireOldPos;

  NouvelEmployee emloye(this, employeList);
  connect(&emloye, SIGNAL(sendEmploye(QString)), this, SLOT(receiveNewEntreprise(QString)));
  emloye.exec();

  calculForce_SalaireMax();

  displayNbrEmploye->setText(QString::number(static_cast<int>(employeList.size())));
  adjustGraph(oldSalairemax, totalSalaire);
}

void SimulationRevendeur::newAchat()
{
  jour++;
  NouveauMois nouveau(this, itemList, &pointeurEntreprise);
  connect(&nouveau, SIGNAL(transfertAchats(QString)), this, SLOT(receiveNewEntreprise(QString)));
  nouveau.exec();
  updateList(view);

  // Set Banque
  banque->display(pointeurEntreprise.getBanque());

  // Set Graph
  calculForce_SalaireMax();
  updateEmptrepriseValue();
  setDate();
}

void SimulationRevendeur::venteClicked()
{
  jour++;
  calculForce_SalaireMax();
  EspaceDeVente* espace = new EspaceDeVente(this, itemList, employeList, villeList, totalForce);

  connect(espace, SIGNAL(localNewBanque(double)), this, SLOT(setNewBanque(double)));
  connect(espace, SIGNAL(transfertsSalaireEtGain(double, double)), this, SLOT(applyNewSale(double, double)));
  espace->exec();

  // Set Banque
  banque->display(pointeurEntreprise.getBanque());

  // Set Graph
  calculForce_SalaireMax();
  updateEmptrepriseValue();

  //News
  addNews();
  setDate();
}

void SimulationRevendeur::addNews()
{
  int ran1 = StaticRandomizer::randomI(3);
  int ran2 = StaticRandomizer::randomI(3);

  news1 = new QLabel(villeList.at(ran1).randomEvent(StaticRandomizer::randomI(11)), this);
  news2 = new QLabel(villeList.at(ran2).randomEvent(StaticRandomizer::randomI(11)), this);

  layoutNews->addWidget(news1);
  layoutNews->addWidget(news2);
}

void SimulationRevendeur::setNewBanque(double value)
{
  pointeurEntreprise.setBanque(pointeurEntreprise.getBanque() + value - totalSalaire);
}

void SimulationRevendeur::show3DGraph()
{
  OpenViewer* open3DView = new OpenViewer(this, historiqueBanque);
  open3DView->show();
}

void SimulationRevendeur::openOption()
{
  Options opt(this);
  connect(&opt, SIGNAL(transferSheet(std::vector<QString>)), this, SLOT(applySheet(std::vector<QString>)));
  opt.exec();
}

void SimulationRevendeur::applySheet(std::vector<QString> list)
{
  news1->setStyleSheet(list.at(0));
  news2->setStyleSheet(list.at(0));
  banque->setStyleSheet(list.at(1));
}

void SimulationRevendeur::setDial(int value)
{
  displayForce->setText(QString::number(value) + "%");

  int newSalaire = totalSalaire * (value * 0.01);
  adjustGraph(salaireOldPos, newSalaire);
  salaireOldPos = newSalaire;
}

void SimulationRevendeur::adjustGraph(int oldValue, int newValue)
{
  lineSalaire->replace(jour, oldValue, jour, newValue);
}

void SimulationRevendeur::receiveNewEntreprise(QString line)
{
  QLabel* lineEmploye = new QLabel(line, this);
  layoutNewsEntreprise->addWidget(lineEmploye);
}

void SimulationRevendeur::applyNewSale(double marge, double fraisport)
{
  receiveNewEntreprise(tr("Votre marge est de ") + QString::number(marge) + tr(" euros, apres déduction de ") + QString::number(fraisport) + tr(" euros de frais de ports, et ") + QString::number(totalSalaire) + tr(" euros de salaire."));
}

void SimulationRevendeur::setDate()
{

  while (jour > 30)
  {
    mois++;
  }
  date->setText(QString::number(jour) + "/" + QString::number(mois) + "/20");
}