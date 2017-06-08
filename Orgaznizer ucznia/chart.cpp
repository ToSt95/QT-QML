#include "chart.h"

chart::chart(QWidget *parent,int oo,int nn) : QWidget(parent),o(oo),n(nn)
{
    series = new QPieSeries();
    series->append("Presence", n);
    series->append("Absence", o);

    slice = series->slices().at(1);
    slice->setExploded();
    slice->setPen(QPen(Qt::black, 2));
    //slice->setLabelVisible();
    slice->setBrush(Qt::red);


    series->slices().at(0)->setPen(QPen(Qt::black, 2));
    series->slices().at(0)->setBrush(Qt::darkGreen);
    //series->slices().at(0)->setLabelVisible();



    chart1 = new QChart();
    chart1->addSeries(series);
    chart1->setTitle("<h1><b>Your presence in %</b></h1>\n\n");
    chart1->legend()->show();

    chartView = new QChartView(chart1);
    chartView->setRenderHint(QPainter::Antialiasing);
}
