#include "chart.h"

chart::chart(QWidget *parent,int oo,int nn) : QWidget(parent),o(oo),n(nn)
{
    series = new QPieSeries();
    series->append("Absence", n);
    series->append("Presence", o);

    slice = series->slices().at(1);
    slice->setExploded();
    //slice->setLabelVisible();
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);

    chart1 = new QChart();
    chart1->addSeries(series);
    chart1->setTitle("Your presence in %");
    chart1->legend()->show();

    chartView = new QChartView(chart1);
    chartView->setRenderHint(QPainter::Antialiasing);
}
