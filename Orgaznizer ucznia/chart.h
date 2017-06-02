#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QtCharts>

class chart : public QWidget
{
    Q_OBJECT
public:
    explicit chart(QWidget *parent = 0,int oo = 3,int nn = 2);
    QPieSeries *series;
    QPieSlice *slice;
    QChart *chart1;
    QChartView *chartView;
    int o;
    int n;

signals:

public slots:
};

#endif // CHART_H
