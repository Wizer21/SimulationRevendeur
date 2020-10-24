#pragma once

#include <QWindow>
#include "stdafx.h"
#include <QtCharts/QLineSeries>
#include <QChart>
#include <QChartView>
#include <QtDataVisualization>

using namespace QtCharts;
using namespace QtDataVisualization;

class OpenViewer : public QDialog
{
  Q_OBJECT

public:
  OpenViewer(QWidget* parent, std::vector<double> historiqueBanque);
  ~OpenViewer();
};
