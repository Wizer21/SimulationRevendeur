#include "AcceptFire.h"

AcceptFire::AcceptFire(QWidget* parent, QString nom, int salaire)
  : QDialog(parent)
{
  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  ini(mainLayout, nom, salaire);
}

void AcceptFire::ini(QVBoxLayout* layoutPointeur, QString nom, int salaire)
{
  QLabel* titre = new QLabel(tr("Voulez vous virer ") + nom + " ?", this);
  QLabel* question = new QLabel(tr("Cela vous coutera ") + QString::number(salaire / 2) + " .", this);
  QGridLayout* gridlayout = new QGridLayout(this);
  QPushButton* oui = new QPushButton("Oui", this);
  QPushButton* non = new QPushButton("Non", this);

  layoutPointeur->addWidget(titre);
  layoutPointeur->addWidget(question);
  layoutPointeur->addLayout(gridlayout);
  gridlayout->addWidget(oui, 0, 0);
  gridlayout->addWidget(non, 0, 1);

  connect(oui, SIGNAL(clicked()), this, SLOT(repOui()));
  connect(non, SIGNAL(clicked()), this, SLOT(repNon()));
}

void AcceptFire::repOui()
{
  emit getReponse("oui");
  this->close();
}

void AcceptFire::repNon()
{
  emit getReponse("non");
  this->close();
}

AcceptFire::~AcceptFire()
{
}
