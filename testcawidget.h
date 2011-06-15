#ifndef TESTCAWIDGET_H
#define TESTCAWIDGET_H

#include "abstractca.h"

#include "qwt/qwt_plot.h"
#include "qwt/qwt_plot_curve.h"
#include "qwt/qwt_plot_renderer.h"
#include "qwt/qwt_legend.h"
#include "qwt/qwt_legend_item.h"

#include <QWidget>
#include <QGridLayout>
#include <QDir>
#include <QSvgGenerator>
#include <QList>
#include <QPainter>

namespace Ui {
    class TestCAWidget;
}

class TestCAWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestCAWidget(AbstractCA* ca, QWidget *parent = 0);
    ~TestCAWidget();

    void runTest(int samples, int steps, float start, float stop, float step, bool testAlpha, bool testBeta);
    void exportToSVG(QDir saveDir);

protected:
    void changeEvent(QEvent *e);

private:
    static const QPen ALPHA_PEN;
    static const QPen BETA_PEN;

    static const QString DENSITY_TITLE;
    static const QString ACTIVITY_TITLE;
    static const QString PROPABILITY_TITLE;
    static const QString ALPHA_TITLE;
    static const QString BETA_TITLE;

    void runAlpha(int samples, int steps, float start, float stop, float step);
    void runBeta(int samples, int steps, float start, float stop, float step);

    CAHistory* runCA(int steps);

    void plotTest();

    QwtPlot* getActivityPlot();
    QwtPlot* getDensityPlot(QString key);

    QwtPlot* newPlot(QString yTitle = "", QString xTitle = "");
    void plot(QString title, QPen pen, QVector<QPointF> data, QwtPlot* plot);

    CAHistory* m_alphaHistory;
    CAHistory* m_betaHistory;

    Ui::TestCAWidget *ui;
    AbstractCA* m_ca;
    QList<QwtPlot*>* m_plots;
};

#endif // TESTCAWIDGET_H
