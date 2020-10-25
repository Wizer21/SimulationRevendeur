#include "IniApp.h"

IniApp::IniApp(Entreprise& entreprise)
{
  entrepriseRef = &entreprise;
  QVBoxLayout* layout = new QVBoxLayout(this);
  ini(layout);
}

void IniApp::ini(QVBoxLayout* mainLayout)
{

  QLabel* titre = new QLabel("Cargo'", this);
  QLabel* subTitre = new QLabel(tr("Bienvenue dans votre simulateur de gestion d'entreprise"), this);
  nomEntreprise = new QLineEdit(this);
  QPushButton* valider = new QPushButton(tr("C'est parti!"), this);

  titre->setFont(QFont("", 45));
  titre->setAlignment(Qt::AlignCenter);
  mainLayout->addWidget(titre);
  mainLayout->addWidget(subTitre);
  mainLayout->addWidget(nomEntreprise);
  mainLayout->addWidget(valider);

  nomEntreprise->setPlaceholderText(tr("Entrer le nom de votre entreprise"));

  connect(valider, SIGNAL(clicked()), this, SLOT(validButton()));
}

void IniApp::validButton()
{
  entrepriseRef->setName(nomEntreprise->text());
  this->close();
}

IniApp::~IniApp()
{
}
