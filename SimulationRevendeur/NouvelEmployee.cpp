#include "NouvelEmployee.h"

NouvelEmployee::NouvelEmployee(QWidget* parent, std::vector<Employe>& getEmploye)
  : QDialog(parent)
{
  pointeurEmployeList = &getEmploye;
  setId = 0;
  idBox = 0;
  reponsePlayer = false;

  setLocalId();
  QGridLayout* mainLayout = new QGridLayout(this);
  ini(mainLayout);
}

void NouvelEmployee::setLocalId()
{
  for (int i = 0; i < pointeurEmployeList->size(); i++)
  {
    if (setId < pointeurEmployeList->at(i).getId())
    {
      setId = pointeurEmployeList->at(i).getId();
    }
  }
}

void NouvelEmployee::ini(QGridLayout* layoutPointeur)
{
  //Gauche
  QWidget* mainWidgetDroit = new QWidget(this);
  QVBoxLayout* layoutGauche = new QVBoxLayout(this);
  QLabel* titre = new QLabel("Gestion employes", this);
  QScrollArea* scrollArea = new QScrollArea(this);
  QWidget* widgetArea = new QWidget(this);
  QVBoxLayout* layoutArea = new QVBoxLayout(this);

  layoutPointeur->addWidget(mainWidgetDroit, 0, 0);
  mainWidgetDroit->setLayout(layoutGauche);
  layoutGauche->addWidget(titre);
  layoutGauche->addWidget(scrollArea);
  scrollArea->setWidget(widgetArea);
  widgetArea->setLayout(layoutArea);

  scrollArea->setWidgetResizable(true);

  iniEmployeList(layoutArea);

  //Droite
  QWidget* mainWidgetGauche = new QWidget(this);
  QVBoxLayout* layoutDroit = new QVBoxLayout(this);
  QPushButton* engagerButton = new QPushButton("Engager !", this);

  layoutPointeur->addWidget(mainWidgetGauche, 0, 1);
  mainWidgetGauche->setLayout(layoutDroit);

  for (int i = 0; i < 3; i++)
  {
    Employe newBob(StaticRandomizer::randomName(), StaticRandomizer::randomI(1000) + 800, StaticRandomizer::randomI(500) + 300, ++setId);
    newEmploye.push_back(newBob);

    QWidget* listWidgetGauche = new QWidget(this);
    QGridLayout* newlayout = new QGridLayout(this);
    QCheckBox* newBox = new QCheckBox(this);
    QLabel* newName = new QLabel(newEmploye.at(i).getNom(), this);

    QLabel* newSalaireLabel = new QLabel("Salaire:", this);
    QLabel* newForceLabel = new QLabel("Force:", this);
    QLineEdit* newSalaire = new QLineEdit(QString::number(newEmploye.at(i).getSalaire()), this);
    QLineEdit* newForce = new QLineEdit(QString::number(newEmploye.at(i).getForce()), this);

    layoutDroit->addWidget(listWidgetGauche);
    listWidgetGauche->setLayout(newlayout);
    newlayout->addWidget(newBox, 0, 0);
    newlayout->addWidget(newName, 0, 1);
    newlayout->addWidget(newSalaireLabel, 0, 2);
    newlayout->addWidget(newForceLabel, 1, 2);
    newlayout->addWidget(newSalaire, 0, 3);
    newlayout->addWidget(newForce, 1, 3);

    newSalaire->setReadOnly(true);
    newForce->setReadOnly(true);
    newBox->setObjectName(QString::number(idBox++));
  }
  layoutDroit->addWidget(engagerButton);

  connect(engagerButton, SIGNAL(clicked()), this, SLOT(pushSelectedEmploye()));
}

void NouvelEmployee::iniEmployeList(QVBoxLayout* layoutPointeur)
{

  for (int i = 0; i < pointeurEmployeList->size(); i++)
  {
    QWidget* widgetList = new QWidget(this);
    QGridLayout* layoutEmploye = new QGridLayout(this);
    QLabel* nom = new QLabel(pointeurEmployeList->at(i).getNom(), this);
    QLabel* salaireLabel = new QLabel("Salaire:", this);
    QLabel* forceLabel = new QLabel("Force:", this);
    QLineEdit* salaire = new QLineEdit(QString::number(pointeurEmployeList->at(i).getSalaire()), this);
    QLineEdit* force = new QLineEdit(QString::number(pointeurEmployeList->at(i).getForce()), this);
    QPushButton* virer = new QPushButton("virer", this);

    widgetList->setObjectName(QString::number(pointeurEmployeList->at(i).getId()));
    virer->setObjectName(QString::number(pointeurEmployeList->at(i).getId()));

    layoutPointeur->addWidget(widgetList);
    widgetList->setLayout(layoutEmploye);

    layoutEmploye->addWidget(nom, 0, 0);
    layoutEmploye->addWidget(salaireLabel, 0, 1);
    layoutEmploye->addWidget(forceLabel, 1, 1);
    layoutEmploye->addWidget(salaire, 0, 2);
    layoutEmploye->addWidget(force, 1, 2);
    layoutEmploye->addWidget(virer, 0, 3, 2, 2);

    salaire->setReadOnly(true);
    force->setReadOnly(true);
    connect(virer, SIGNAL(clicked()), this, SLOT(virerEmploye()));
  }
}

void NouvelEmployee::virerEmploye()
{
  int idSender = sender()->objectName().toInt();
  int i = 0;
  for (i; i < pointeurEmployeList->size(); i++)
  {
    if (pointeurEmployeList->at(i).getId() == idSender)
    {
      break;
    }
  }

  popFire = new AcceptFire(this, pointeurEmployeList->at(i).getNom(), pointeurEmployeList->at(i).getSalaire());
  connect(popFire, SIGNAL(getReponse(QString)), this, SLOT(setReponse(QString)));
  popFire->exec();

  if (reponsePlayer)
  {
    pointeurEmployeList->erase(pointeurEmployeList->begin() + i);
    QWidget* widgetADelete = this->findChild<QWidget*>(QString::number(idSender));
    delete widgetADelete;
  }
}

void NouvelEmployee::pushSelectedEmploye()
{

  for (int i = 0; i < 3; i++)
  {
    QCheckBox* box = this->findChild<QCheckBox*>(QString::number(i));
    if (box->isChecked())
    {
      pointeurEmployeList->push_back(newEmploye.at(i));
    }
  }
  this->close();
}

void NouvelEmployee::setReponse(QString reponse)
{
  if (reponse == "oui")
  {
    reponsePlayer = true;
    return;
  }
  reponsePlayer = false;
}

NouvelEmployee::~NouvelEmployee()
{
}
