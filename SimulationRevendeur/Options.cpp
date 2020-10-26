#include "Options.h"

Options::Options(QWidget* parent)
  : QDialog(parent)
{

  QVBoxLayout* layout = new QVBoxLayout(this);
  ini(layout);
}

void Options::ini(QVBoxLayout* layout)
{
  QLabel* titre = new QLabel(tr("Options"), this);
  QWidget* widgetOptions = new QWidget(this);
  QGridLayout* gridLayout = new QGridLayout(this);
  QLabel* langueSelecter = new QLabel(tr("Langue"), this);
  QComboBox* langueList = new QComboBox(this);

  QLabel* theme = new QLabel(tr("Theme"), this);
  QComboBox* themeList = new QComboBox(this);

  QPushButton* valider = new QPushButton(tr("Valider"), this);

  layout->addWidget(titre);
  layout->addWidget(widgetOptions);
  widgetOptions->setLayout(gridLayout);
  gridLayout->addWidget(langueSelecter, 0, 0);
  gridLayout->addWidget(langueList, 0, 1);
  gridLayout->addWidget(theme, 1, 0);
  gridLayout->addWidget(themeList, 1, 1);
  layout->addWidget(valider);

  titre->setFont(QFont("Open Sans", 40));
  langueList->addItem("Francais");
  langueList->addItem("English");
  themeList->addItem(tr("Default"));
  themeList->addItem(tr("Clair"));
  themeList->addItem(tr("Sombre"));

  connect(themeList, SIGNAL(currentIndexChanged(int)), this, SLOT(themeChanged(int)));
  connect(themeList, SIGNAL(currentIndexChanged(int)), this, SLOT(callTheme(int)));
  connect(valider, SIGNAL(clicked()), this, SLOT(closeOption()));
}

void Options::themeChanged(int colorID)
{
  SetTheme::applyTheme(colorID);
}

void Options::callTheme(int colorID)
{
  emit transferSheet(SetTheme::getTransfet(colorID));
}

void Options::closeOption()
{
  this->close();
}

Options::~Options()
{
}
