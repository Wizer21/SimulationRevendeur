#include "EspaceDeVente.h"

EspaceDeVente::EspaceDeVente(QWidget* parent, std::vector<Item>& itemList, std::vector<Employe>& listEmployeRef, std::vector<Ville>& villeListRef, double addPoidMax)
  : QDialog(parent)
{
  pointeurItemList = &itemList;
  pointeurVille = &villeListRef;
  listEmploye = &listEmployeRef;

  estimationPrixFinal = 0;
  poidMax = 0;
  poidActuel = 0;
  francoPort = 0;
  poidMax = addPoidMax;

  QGridLayout* mainLayout = new QGridLayout(this);
  ini(mainLayout);
}

void EspaceDeVente::ini(QGridLayout* mainLayout)
{
  //Droit
  QWidget* widgetDroit = new QWidget(this);
  QGridLayout* layoutDroit = new QGridLayout(this);
  QLabel* titre = new QLabel("Espace de vente", this);

  QScrollArea* scrollArea = new QScrollArea(this);
  QWidget* widgetArea = new QWidget(this);
  QGridLayout* layoutInArea = new QGridLayout(this);

  QLabel* forceRestante = new QLabel("Main d'oeuvre disponible:", this);
  displayForce = new QLineEdit(QString::number(poidMax), (this));
  forceBar = new QProgressBar(this);

  tropLourd = new QLabel("Main d'oeuvre insuffisante!", this);

  tropLourd->setStyleSheet("QLabel { background-color : #fb3a3a;}");
  mainLayout->addWidget(widgetDroit);
  widgetDroit->setLayout(layoutDroit);
  layoutDroit->addWidget(titre, 0, 0, 1, 2);
  layoutDroit->addWidget(scrollArea, 1, 0, 1, 2);
  scrollArea->setWidget(widgetArea);
  widgetArea->setLayout(layoutInArea);
  layoutDroit->addWidget(forceRestante, 2, 0);
  layoutDroit->addWidget(displayForce, 2, 1);
  layoutDroit->addWidget(forceBar, 3, 0, 1, 2);
  layoutDroit->addWidget(tropLourd, 4, 0);

  displayForce->setReadOnly(true);
  tropLourd->setVisible(false);
  forceBar->setStyleSheet("QProgressBar {qproperty-alignment: AlignCenter;}");
  forceBar->setValue(0);
  forceBar->setRange(0, poidMax);
  scrollArea->setWidgetResizable(true);
  iniItemList(layoutInArea);

  //Gauches
  QWidget* widgetGauche = new QWidget(this);
  QGridLayout* layoutGauche = new QGridLayout(this);

  mainLayout->addWidget(widgetGauche, 0, 1);
  widgetGauche->setLayout(layoutGauche);

  iniVille(layoutGauche);

  QGroupBox* estimations = new QGroupBox(tr("Estimations"), this);
  QGridLayout* boxLayout = new QGridLayout(this);
  QLabel* fraisEnvoir = new QLabel(tr("Frais d'Envoi"), this);
  displayFrais = new QLineEdit("0", this);
  QLabel* gainEstime = new QLabel(tr("Montant des Ventes"), this);
  displayGain = new QLineEdit("0", this);
  QPushButton* venteFinished = new QPushButton(tr("Valider"), this);

  layoutGauche->addWidget(estimations);
  estimations->setLayout(boxLayout);
  boxLayout->addWidget(fraisEnvoir, 3, 0);
  boxLayout->addWidget(displayFrais, 3, 1);
  boxLayout->addWidget(gainEstime, 5, 0);
  boxLayout->addWidget(displayGain, 5, 1);

  displayFrais->setReadOnly(true);
  displayGain->setReadOnly(true);
  layoutGauche->addWidget(venteFinished, 6, 0, 2, 2);

  venteFinished->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  connect(venteFinished, SIGNAL(clicked()), this, SLOT(validButton()));
}

void EspaceDeVente::iniItemList(QGridLayout* layoutArea)
{
  int y = 0;
  int x = 0;
  int setId = 0;

  for (int i = 0; i < pointeurItemList->size(); i++)
  {
    QWidget* widgetItem = new QWidget(this);
    QGridLayout* gridLayout = new QGridLayout(this);
    QLabel* itemName = new QLabel(pointeurItemList->at(i).getNom(), this);
    QLineEdit* stockDynamic = new QLineEdit(QString::number(pointeurItemList->at(i).getStock()), this);
    QSlider* slider = new QSlider(Qt::Horizontal, this);
    QLabel* gainEstime = new QLabel(tr("Gain Estime"), this);
    QLineEdit* displayGainEstime = new QLineEdit(this);

    layoutArea->addWidget(widgetItem, x, y++);
    widgetItem->setLayout(gridLayout);
    gridLayout->addWidget(itemName, 0, 0);
    gridLayout->addWidget(stockDynamic, 0, 1);
    gridLayout->addWidget(slider, 1, 0, 1, 2);
    gridLayout->addWidget(gainEstime, 2, 0, 1, 2);
    gridLayout->addWidget(displayGainEstime, 3, 0, 1, 2);

    stockDynamic->setReadOnly(true);
    displayGainEstime->setReadOnly(true);
    displayGainEstime->setObjectName(QString::number(setId) + "a");
    stockDynamic->setObjectName(QString::number(setId));
    slider->setObjectName(QString::number(setId++));
    slider->setPageStep(1);

    slider->setRange(0, pointeurItemList->at(i).getStock());
    widgetItem->setStyleSheet("background-color:#e7e7e7;");

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sliderDragged(int)));

    Item itemTemporaire(0, 0, 0);
    listeTemporaire.push_back(itemTemporaire);

    if (y == 3)
    {
      y = 0;
      x++;
    }
  }
}

void EspaceDeVente::iniVille(QGridLayout* layoutArea)
{
  int boxId = 0;
  groupCheckBox = new QButtonGroup(this);
  groupCheckBox->setExclusive(true);
  for (int i = 0; i < pointeurVille->size(); i++)
  {
    QWidget* widgetVille = new QWidget(this);
    QGridLayout* layoutVille = new QGridLayout(this);
    QCheckBox* box = new QCheckBox(this);
    QLabel* nomVille = new QLabel(pointeurVille->at(i).getNom(), this);

    widgetVille->setStyleSheet("background-color:#e7e7e7;");

    layoutArea->addWidget(widgetVille, i, 0, 1, 2);
    widgetVille->setLayout(layoutVille);
    layoutVille->addWidget(box, 0, 0);
    layoutVille->addWidget(nomVille, 0, 1);

    groupCheckBox->addButton(box, boxId++);

    if (i == 0)
    {
      box->setChecked(true);
    }
  }
}

void EspaceDeVente::sliderDragged(int value)
{
  QLineEdit* pointeurLineEdit = this->findChild<QLineEdit*>(sender()->objectName());

  pointeurLineEdit->setText(QString::number(pointeurItemList->at(pointeurLineEdit->objectName().toDouble()).getStock() - value));

  int id = pointeurLineEdit->objectName().toInt();
  listeTemporaire.at(id).setPvTotal((pointeurItemList->at(id).getStock() - pointeurLineEdit->text().toDouble()) * (pointeurItemList->at(id)).getPV());
  listeTemporaire.at(id).setPoid((pointeurItemList->at(id).getPoid() * value));
  listeTemporaire.at(id).setQuantiteVendue(value);

  calculForceEtPrixMax();
  calculFranco();
  displayFrais->setText(QString::number(poidActuel * francoPort));
}

void EspaceDeVente::calculForceEtPrixMax()
{
  poidActuel = 0;
  estimationPrixFinal = 0;
  for (int i = 0; i < listeTemporaire.size(); i++)
  {
    // calcul prix max
    estimationPrixFinal += listeTemporaire.at(i).getPvTotal();
    QLineEdit* gainItem = this->findChild<QLineEdit*>(QString::number(i) + "a");
    gainItem->setText(QString::number(listeTemporaire.at(i).getPvTotal()));
    // force utilisée
    poidActuel += listeTemporaire.at(i).getPoid();
  }
  // Display Force/Gain setProgressBar
  displayGain->setText(QString::number(estimationPrixFinal));

  displayForce->setText(QString::number(poidMax - poidActuel));
  forceBar->setValue(poidActuel);

  if (poidActuel > poidMax)
  {
    forceBar->setStyleSheet("QProgressBar::chunk {border: 0px ; background-color:#fb3a3a}");
    forceBar->setValue(poidMax);
  }
  else
  {
    forceBar->setStyleSheet("QProgressBar::chunk {border: 0px ; background-color:#3afb77}");
  }
}

void EspaceDeVente::calculFranco()
{
  francoPort = 1;
  int prochainFranco = 500;
  while (poidActuel > prochainFranco)
  {
    francoPort -= 0.05;
    prochainFranco += prochainFranco * 2;
  }
}

void EspaceDeVente::validButton()
{
  if (poidActuel > poidMax)
  {
    tropLourd->setVisible(true);
    StaticRandomizer::wizz(tropLourd, "fb3a3a");
    return;
  }

  int checkedBox = groupCheckBox->checkedId();
  double fraisPort = ((francoPort * poidActuel) * pointeurVille->at(checkedBox).getFraisMultiplicateur());
  double newBanque = (estimationPrixFinal * pointeurVille->at(checkedBox).getMultiplicateurGain()) - fraisPort;

  for (int i = 0; i < pointeurItemList->size(); i++)
  {
    pointeurItemList->at(i).setStock(pointeurItemList->at(i).getStock() - listeTemporaire.at(i).getQuantiteVendue());
  }

  emit transfertsSalaireEtGain(newBanque, fraisPort);
  emit localNewBanque(newBanque);
  this->close();
}

EspaceDeVente::~EspaceDeVente()
{
}
