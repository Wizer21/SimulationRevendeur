#pragma once

#include <QDialog>
#include "stdafx.h"

class AcceptFire : public QDialog
{
  Q_OBJECT

public:
  AcceptFire(QWidget* parent, QString nom, int salaire);
  ~AcceptFire();

public slots:
  void repOui();
  void repNon();

signals:
  void getReponse(QString reponse);

private:
  void ini(QVBoxLayout* layoutPointeur, QString nom, int salaire);
};
