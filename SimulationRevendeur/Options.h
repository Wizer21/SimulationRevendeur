#pragma once

#include <QDialog>
#include "stdafx.h"
#include "SetTheme.h"

class Options : public QDialog
{
  Q_OBJECT

public:
  Options(QWidget* parent);
  ~Options();

public slots:
  void themeChanged(int colorID);
  void callTheme(int colorID);
  void closeOption();

signals:
  void transferSheet(std::vector<QString> list);

private:
  void ini(QVBoxLayout* layout);
};
