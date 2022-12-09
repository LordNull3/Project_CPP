#ifndef STAT_COMBO_H
#define STAT_COMBO_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "ui_stats.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class stats;
}

class stats : public QDialog
{
    Q_OBJECT

public:
    explicit stats(QWidget *parent = nullptr);
    ~stats();

    QChartView *chartView ;
    void Stats_bar();

private:
    Ui::stats *ui;
};

#endif // STAT_COMBO_H
