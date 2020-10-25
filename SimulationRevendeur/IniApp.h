#pragma once

#include <QDialog>
#include "stdafx.h"
#include "Entreprise.h"

class IniApp : public QDialog
{
  Q_OBJECT

public:
  IniApp(Entreprise& entreprise);

  ~IniApp();

public slots:
  void validButton();

private:
  Entreprise* entrepriseRef;
  QLineEdit* nomEntreprise;
  void ini(QVBoxLayout* mainLayout);
};
