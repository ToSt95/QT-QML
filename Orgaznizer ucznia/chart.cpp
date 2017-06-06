#include "chart.h"

chart::chart(QWidget *parent,int oo,int nn) : QWidget(parent),o(oo),n(nn)
{
    series = new QPieSeries();
    series->append("Presence", n);
    series->append("Absence", o);

    slice = series->slices().at(1);
    slice->setExploded();
    //slice->setLabelVisible();
    slice->setPen(QPen(Qt::black, 2));
    slice->setBrush(Qt::red);


    series->slices().at(0)->setPen(QPen(Qt::black, 2));
    series->slices().at(0)->setBrush(Qt::green);


    chart1 = new QChart();
    chart1->addSeries(series);
    chart1->setTitle("Your presence in %");
    chart1->legend()->show();

    chartView = new QChartView(chart1);
    chartView->setRenderHint(QPainter::Antialiasing);
}
