#pragma once

#include <QWidget>
#include "stdafx.h"
#include "Employe.h"
#include "AcceptFire.h"
#include "StaticRandomizer.h"

class NouvelEmployee : public QDialog
{
  Q_OBJECT

public:
  NouvelEmployee(QWidget* parent, std::vector<Employe>& getEmploye);
  ~NouvelEmployee();

public slots:
  void virerEmploye();
  void setReponse(QString);
  void pushSelectedEmploye();

signals:
  void sendEmploye(QString line);

private:
  bool reponsePlayer;
  int setId;
  int idBox;
  AcceptFire* popFire;

  void setLocalId();
  void ini(QGridLayout* layoutPointeur);
  void iniEmployeList(QVBoxLayout* layoutPointeur);
  void newsNewEmploye(QString nom);
  void fireEmploye(QString nom);

  std::vector<Employe> newEmploye;
  std::vector<Employe>* pointeurEmployeList;
};
