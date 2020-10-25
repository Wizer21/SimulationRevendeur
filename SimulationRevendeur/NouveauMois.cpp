#include "NouveauMois.h"

NouveauMois::NouveauMois(QWidget* parent, std::vector<Item>& getList, Entreprise* getEntreprise)
  : QDialog(parent)
{

  setID = 0;
  pointeurList = &getList;
  pointeurEntreprise = getEntreprise;
  coutTotal = 0;

  QVBoxLayout* layout = new QVBoxLayout(this);
  ini(layout, getList);
  setFacturtion();
}

void NouveauMois::ini(QVBoxLayout* mainLayout, std::vector<Item>& getList)
{

  QLabel* titre = new QLabel(tr("Commande"), this);

  //Scroll
  QScrollArea* scrollArea = new QScrollArea();
  QWidget* widgetINArea = new QWidget();
  QVBoxLayout* layoutArea = new QVBoxLayout();

  //Facture
  QWidget* facturation = new QWidget();
  QGridLayout* layoutFacture = new QGridLayout();
  QLabel* titreFacture = new QLabel(tr("Facture"));
  QLabel* ancienSolde = new QLabel(tr("Ancien Solde"));
  QLineEdit* displayAncienSolde = new QLineEdit(QString::number(pointeurEntreprise->getBanque()));
  QLabel* coutTotalLabel = new QLabel(tr("Cout de la commande"));
  QLineEdit* displayCout = new QLineEdit();
  QLabel* nouveauSolde = new QLabel(tr("Nouveau Solde"));
  displayNouveauSolde = new QLineEdit();

  QPushButton* validerBouton = new QPushButton(tr("Valider"));

  erreur = new QLabel(tr("Fonds Insuffisants"), this);

  displayCout->setObjectName("coutCommande");
  displayNouveauSolde->setObjectName("nouvSolde");

  mainLayout->addWidget(titre);

  //Scroll
  mainLayout->addWidget(scrollArea);
  scrollArea->setWidget(widgetINArea);
  widgetINArea->setLayout(layoutArea);

  scrollArea->setWidgetResizable(true);

  iniItemList(layoutArea, getList);

  //Facture
  mainLayout->addWidget(facturation);
  facturation->setLayout(layoutFacture);
  layoutFacture->addWidget(titreFacture);

  layoutFacture->addWidget(titreFacture, 0, 0, 1, 2);

  layoutFacture->addWidget(ancienSolde, 1, 0);
  layoutFacture->addWidget(displayAncienSolde, 1, 1);
  layoutFacture->addWidget(coutTotalLabel, 2, 0);
  layoutFacture->addWidget(displayCout, 2, 1);
  layoutFacture->addWidget(nouveauSolde, 3, 0);
  layoutFacture->addWidget(displayNouveauSolde, 3, 1);

  erreur->setVisible(true);
  erreur->setStyleSheet("QLabel { background-color : #fb3a3a;}");
  displayAncienSolde->setReadOnly(true);
  displayCout->setReadOnly(true);
  displayNouveauSolde->setReadOnly(true);

  mainLayout->addWidget(validerBouton);
  connect(validerBouton, SIGNAL(clicked()), this, SLOT(validButtonClicked()));

  erreur->setVisible(false);
  erreur->setStyleSheet("QLabel { background-color : #fb3a3a;}");
  mainLayout->addWidget(erreur);
}

void NouveauMois::iniItemList(QVBoxLayout* mainLayout, std::vector<Item>& getList)
{

  QIntValidator* intOnly = new QIntValidator(0, 99999);

  for (int i = 0; i < getList.size(); i++)
  {

    QWidget* widgetItem = new QWidget(this);
    QGridLayout* gridLayout = new QGridLayout(this);

    widgetItem->setStyleSheet("background-color:#fff");

    mainLayout->addWidget(widgetItem);
    widgetItem->setLayout(gridLayout);

    QLabel* titre = new QLabel(getList.at(i).getNom(), this);
    QLabel* stock = new QLabel(tr("Stock:"), this);
    QLabel* prixUnitaire = new QLabel(tr("Prix Unitaire"), this);
    QLineEdit* displayStock = new QLineEdit(QString::number(getList.at(i).getStock()), this);
    QLineEdit* displayPrixUnitaire = new QLineEdit(QString::number(getList.at(i).getPA()), this);
    QLineEdit* displayVenteMensuel = new QLineEdit("vide", this);
    QLineEdit* entreeJoueur = new QLineEdit(this);
    QLineEdit* prixCommande = new QLineEdit("0");

    entreeJoueur->setObjectName(QString::number(setID));
    displayPrixUnitaire->setObjectName(QString::number(setID) + "a");
    prixCommande->setObjectName(QString::number(setID++) + "b");

    displayStock->setReadOnly(true);
    displayPrixUnitaire->setReadOnly(true);
    displayVenteMensuel->setReadOnly(true);
    entreeJoueur->setValidator(intOnly);
    prixCommande->setReadOnly(true);

    gridLayout->addWidget(titre, 0, 0);
    gridLayout->addWidget(stock, 1, 0);
    gridLayout->addWidget(displayStock, 1, 1);
    gridLayout->addWidget(prixUnitaire, 2, 0);
    gridLayout->addWidget(displayPrixUnitaire, 2, 1);
    gridLayout->addWidget(displayVenteMensuel, 0, 1);
    gridLayout->addWidget(entreeJoueur, 0, 2);
    gridLayout->addWidget(prixCommande, 1, 2, 2, 1);

    displayStock->setReadOnly(true);
    displayPrixUnitaire->setReadOnly(true);
    displayVenteMensuel->setReadOnly(true);
    prixCommande->setReadOnly(true);

    connect(entreeJoueur, SIGNAL(textChanged(QString)), this, SLOT(orderPrice(QString)));
  }
}

void NouveauMois::orderPrice(QString)
{
  QLineEdit* pointeurLineEdit = qobject_cast<QLineEdit*>(sender());
  QString id = pointeurLineEdit->objectName();
  QLineEdit* pointeurPrixUnitaire = this->findChild<QLineEdit*>(id + "a");
  QLineEdit* pointeurPrixCommande = this->findChild<QLineEdit*>(id + "b");
  pointeurPrixCommande->setText(QString::number((pointeurPrixUnitaire->text()).toDouble() * (pointeurLineEdit->text()).toDouble()));
  setFacturtion();
}

void NouveauMois::setFacturtion()
{
  coutTotal = 0;

  for (int i = 0; i < setID; i++)
  {
    QLineEdit* pointeurSomme = this->findChild<QLineEdit*>(QString::number(i) + "b");

    coutTotal += pointeurSomme->text().toDouble();
  }

  QLineEdit* coutCommande = this->findChild<QLineEdit*>(tr("coutCommande"));
  coutCommande->setText("-" + QString::number(coutTotal));
  displayNouveauSolde->setText(QString::number(pointeurEntreprise->getBanque() - coutTotal));
}

void NouveauMois::validButtonClicked()
{

  if (displayNouveauSolde->text().toDouble() < 0)
  {
    erreur->setVisible(true);
    StaticRandomizer::wizz(erreur, "fb3a3a");
    return;
  }

  //Set Banque
  double coutCommande = 0;
  for (int i = 0; i < setID; i++)
  {
    QLineEdit* pointeurSomme = this->findChild<QLineEdit*>(QString::number(i) + "b");

    coutCommande += pointeurSomme->text().toDouble();
  }

  pointeurEntreprise->setBanque(pointeurEntreprise->getBanque() - coutCommande);

  //Set New Stock
  for (int i = 0; i < setID; i++)
  {
    QLineEdit* coutSlotItem = this->findChild<QLineEdit*>(QString::number(i));
    pointeurList->at(i).setStock(pointeurList->at(i).getStock() + coutSlotItem->text().toInt());
  }
  emit transfertAchats(tr("Vous avez realiser un achat de ") + QString::number(coutCommande) + tr(" euros de marchandises"));

  this->close();
}

NouveauMois::~NouveauMois()
{
}
