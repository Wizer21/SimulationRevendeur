#pragma once
#include <cstdlib>
#include "stdafx.h"

class StaticRandomizer
{

public:
  static int randomI(int i);
  static double addRandomDouble(int valueDiv100);
  static QString randomName();
  static void wizz(QWidget* widget, QString hexa);
  static void wait(int milliSec);

private:
  StaticRandomizer(){};
};
