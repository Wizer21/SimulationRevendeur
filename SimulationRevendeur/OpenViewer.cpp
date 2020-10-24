#include "OpenViewer.h"

OpenViewer::OpenViewer(QWidget* parent, std::vector<double> historiqueBanque)
  : QDialog(parent)
{
  this->setMinimumHeight(500);
  this->setMinimumWidth(500);

  Q3DBars* newBar3D = new Q3DBars();
  int maxValue = 0;

  for (int i = 0; i < historiqueBanque.size(); i++)
  {
    if (maxValue < historiqueBanque.at(i))
    {
      maxValue = historiqueBanque.at(i);
    }

    QBar3DSeries* newSerie = new QBar3DSeries;
    QBarDataRow* newData = new QBarDataRow;

    *newData << historiqueBanque.at(i);
    newSerie->dataProxy()->addRow(newData);
    newBar3D->addSeries(newSerie);
  }

  newBar3D->show();

  QVBoxLayout* layout3D = new QVBoxLayout(this);
  QWidget* newContainer = QWidget::createWindowContainer(newBar3D);
  layout3D->addWidget(newContainer);
}

OpenViewer::~OpenViewer()
{
}
