#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "SimulationRevendeur.h"
#include "IniApp.h"
#include "Entreprise.h"

int main(int argc, char* argv[])
{
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication a(argc, argv);

  // Apply custom language and translation
  auto lTranslator{new QTranslator()};
  if (lTranslator->load(QString(":/translations/simulationrevendeur_%1.qm").arg("en")))
  {
    a.installTranslator(lTranslator);
  }

  // Apply default Qt language and translation
  auto lQtBaseTranslator{new QTranslator()};
  if (lQtBaseTranslator->load("qt_en.qm", QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
  {
    a.installTranslator(lQtBaseTranslator);
  }

  Entreprise entreprise;
  IniApp presentation(entreprise);
  presentation.exec();
  SimulationRevendeur w;
  w.setEntreprise(entreprise);
  w.show();
  return a.exec();
}
