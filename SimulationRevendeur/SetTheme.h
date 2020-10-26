#pragma once
#include "stdafx.h"
#include <cstdlib>

class SetTheme
{
public:
  static void applyTheme(int colorID);
  static std::vector<QString> getTransfet(int colorID);

private:
  SetTheme();
  static QString getMainWindows(int colorID);
  static QString getDialog(int colorID);
  static QString getMenuBar(int colorID);
  static QString getMenu(int colorID);
  static QString getLabel(int colorID);
  static QString getLineEdit(int colorID);
  static QString getButton(int colorID);
  static QString getTabWidget(int colorID);
};
