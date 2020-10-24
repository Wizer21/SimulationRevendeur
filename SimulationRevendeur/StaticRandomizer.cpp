#include "StaticRandomizer.h"

int StaticRandomizer::randomI(int i)
{
  int value = rand() % i;
  return value;
}

double StaticRandomizer::addRandomDouble(int valueDiv100)
{
  double nbr = rand() % valueDiv100 * 0.01;
  return nbr;
}

QString StaticRandomizer::randomName()
{
  std::vector<QString> listSyllabe;
  listSyllabe.push_back("sa");
  listSyllabe.push_back("ma");
  listSyllabe.push_back("dab");
  listSyllabe.push_back("jeu");
  listSyllabe.push_back("ar");
  listSyllabe.push_back("pa");
  listSyllabe.push_back("lu");
  listSyllabe.push_back("nu");
  listSyllabe.push_back("quo");

  QString name = "";

  int nbrSyllabe = randomI(4) + 1;

  for (int i = 0; i < nbrSyllabe; i++)
  {
    name += listSyllabe.at(randomI(9));
  }

  QStringList parts = name.split(' ', QString::SkipEmptyParts);
  for (int i = 0; i < parts.size(); ++i)
    parts[i].replace(0, 1, parts[i][0].toUpper());

  name = parts.join(" ");

  return name;
}

void StaticRandomizer::wizz(QWidget* widget, QString hexa)
{
  for (int i = 0; i < 4; i++)
  {
    widget->setStyleSheet("QLabel { background-color : #ffffff;}");
    wait(10);
    widget->setStyleSheet("QLabel { background-color : #fb3a3a;}");
    wait(10);
    widget->setStyleSheet("QLabel { background-color : #ffffff;}");
    wait(10);
    widget->setStyleSheet("QLabel { background-color : #fb3a3a;}");
  }
}

void StaticRandomizer::wait(int milliSec)
{
  QTime timer = QTime::currentTime().addMSecs(milliSec);
  while (QTime::currentTime() < timer)
  {
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
  }
}