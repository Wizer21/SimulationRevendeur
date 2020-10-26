#include "SetTheme.h"

SetTheme::SetTheme()
{
}

void SetTheme::applyTheme(int i)
{

  qApp->setStyleSheet(getMainWindows(i) + getMenuBar(i) + getDialog(i) + getMenu(i) + getLabel(i) + getLineEdit(i) + getButton(i) + getTabWidget(i));
}

QString SetTheme::getMainWindows(int colorID)
{
  switch (colorID)
  {
    case 0:
      return "";
      break;
    case 1:
      return ("QMainWindow {background-color:#ffffff}");
      break;
    default:
      return ("QMainWindow {background-color:#2f2f2f}");
      break;
  }
}

QString SetTheme::getMenuBar(int colorID)
{
  switch (colorID)
  {
    case 0:
      return "";
      break;
    case 1:
      return ("QMenuBar {background-color:#ffffff; color:#036eab}");
      break;
    default:
      return ("QMenuBar {background-color:#4d4d4d; color:#ffffff}");
      break;
  }
}

QString SetTheme::getMenu(int colorID)
{
  switch (colorID)
  {
    case 0:
      return "";
      break;
    case 1:
      return ("QMenu {background-color:#ffffff; color:#036eab}");
      break;
    default:
      return ("QMenu {background-color:#2f2f2f; color:#ffffff}");
      break;
  }
}

QString SetTheme::getDialog(int colorID)
{
  switch (colorID)
  {
    case 0:
      return "";
      break;
    case 1:
      return ("QDialog {background-color:#ffffff}");
      break;
    default:
      return ("QDialog {background-color:#2f2f2f}");
      break;
  }
}

QString SetTheme::getLabel(int colorID)
{
  switch (colorID)
  {
    case 0:
      return "";
      break;
    case 1:
      return ("QLabel {color:#036eab; font: Arial}");
      break;
    default:
      return ("QLabel {color:#ffffff}");
      break;
  }
}

QString SetTheme::getLineEdit(int colorID)
{
  switch (colorID)
  {
    case 0:
      return "";
      break;
    case 1:
      return ("QLineEdit {background-color:#caecff; color:#036eab; border-style: solid; border-color:#caecff; border-width: 1px}");
      break;
    default:
      return ("");
      break;
  }
}

QString SetTheme::getButton(int colorID)
{
  switch (colorID)
  {
    case 0:
      return "";
      break;
    case 1:
      return ("QPushButton {background-color:#ffffff; color:#036eab; border-style: solid; border-width: 1px; border-color:#c9ebff} QPushButton:hover{background-color:#b0e2ff ; border-color:#c9ebff}");
      break;
    default:
      return ("QPushButton {background-color:#2f2f2f; color:#ffffff; border-style: solid; border-width: 1px; border-color:#000000} QPushButton:hover{background-color:#9e9e9e }");
      break;
  }
}

QString SetTheme::getTabWidget(int colorID)
{
  switch (colorID)
  {
    case 0:
      return "";
      break;
    case 1:
      return ("QTabBar::tab {background-color:#ffffff; color:#036eab} QTabBar::tab:selected {background-color:#caecff} QWidget {background-color:#ffffff");
      break;
    default:
      return ("");
      break;
  }
}

std::vector<QString> SetTheme::getTransfet(int colorID)
{
  std::vector<QString> list;
  switch (colorID)
  {
    case 0:
      list.push_back("");
      list.push_back("");
      break;
    case 1:
      list.push_back("QLabel {background-color:#caecff; color:#036eab; border-style: solid; border-color:#caecff; border-width: 1px}");
      list.push_back("QLCDNumber {background-color:#ffffff; color:#036eab; border-style: solid; border-width: 1px; border-color:#c9ebff}");
      break;
    default:
      list.push_back("");
      list.push_back("");
      break;
  }
  return list;
}