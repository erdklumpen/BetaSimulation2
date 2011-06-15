#include "testcawidget.h"
#include "ui_testcawidget.h"

const QPen TestCAWidget::ALPHA_PEN(Qt::blue);
const QPen TestCAWidget::BETA_PEN(Qt::red);

const QString TestCAWidget::DENSITY_TITLE("Dichte");
const QString TestCAWidget::ACTIVITY_TITLE("Aktivität");
const QString TestCAWidget::PROPABILITY_TITLE("Wahrscheinlichkeit");
const QString TestCAWidget::ALPHA_TITLE("alpha");
const QString TestCAWidget::BETA_TITLE("beta");

TestCAWidget::TestCAWidget(AbstractCA *ca, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestCAWidget)
{
    ui->setupUi(this);
    m_ca = ca;
    m_plots = new QList<QwtPlot*>();

    m_alphaHistory = new CAHistory();
    m_betaHistory = new CAHistory();
}

TestCAWidget::~TestCAWidget()
{
    delete ui;
    delete m_ca;
}

void TestCAWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TestCAWidget::runTest(int samples, int steps, float start, float stop, float step, bool testAlpha, bool testBeta)
{
    delete m_alphaHistory;
    delete m_betaHistory;

    m_alphaHistory = new CAHistory();
    m_betaHistory = new CAHistory();

    if(testAlpha)
        runAlpha(samples, steps, start, stop, step);

    if(testBeta)
        runBeta(samples, steps, start, stop, step);

    plotTest();
}

void TestCAWidget::runAlpha(int samples, int steps, float start, float stop, float step)
{
    float alpha = start;
    while(alpha < stop || (fabs(alpha - stop) < 0.00001))
    {
        qDebug() << "alpha: " << alpha;
        m_ca->setAlpha(alpha);

        QMap<QString, float> sampleSum;
        float activitySum = 0.0;

        for(int i = 0; i < samples; ++i)
        {
            qDebug() << "sample: " << i;
            CAHistory* lastRun = runCA(steps);

            activitySum += lastRun->getActivity().last().y();

            QStringList keys = lastRun->getDensities();
            for(int j = 0; j < keys.size(); ++j)
            {
                QString key = keys.at(j);

                if(!sampleSum.contains(key))
                    sampleSum.insert(key, lastRun->getDensity(key).last().y());
                else
                    sampleSum.insert(key,lastRun->getDensity(key).last().y() + sampleSum.value(key));
            }

            m_ca->initHistory();
            m_ca->initCAState();

            delete lastRun;
        }

        float averageActivity = activitySum / samples;
        m_alphaHistory->appendActivity(averageActivity, alpha);

        QStringList keys = sampleSum.keys();
        for(int i = 0; i < keys.size(); ++i)
        {
            QString key = keys.at(i);

            float average = sampleSum.value(key) / samples;
            m_alphaHistory->appendDensity(key, average, alpha);
        }

        alpha += step;
    }
}

void TestCAWidget::runBeta(int samples, int steps, float start, float stop, float step)
{
    float beta = start;
    while(beta < stop || (fabs(beta - stop) < 0.00001))
    {
        qDebug() << "beta: " << beta;
        m_ca->setBeta(beta);

        QMap<QString, float> sampleSum;
        float activitySum = 0.0;

        for(int i = 0; i < samples; ++i)
        {
            qDebug() << "sample: " << i;
            CAHistory* lastRun = runCA(steps);

            activitySum += lastRun->getActivity().last().y();

            QStringList keys = lastRun->getDensities();
            for(int j = 0; j < keys.size(); ++j)
            {
                QString key = keys.at(j);

                if(!sampleSum.contains(key))
                    sampleSum.insert(key, lastRun->getDensity(key).last().y());
                else
                    sampleSum.insert(key,lastRun->getDensity(key).last().y() + sampleSum.value(key));
            }

            m_ca->initHistory();
            m_ca->initCAState();

            delete lastRun;
        }

        float averageActivity = activitySum / samples;
        m_betaHistory->appendActivity(averageActivity, beta);

        QStringList keys = sampleSum.keys();
        for(int i = 0; i < keys.size(); ++i)
        {
            QString key = keys.at(i);

            float average = sampleSum.value(key) / samples;
            m_betaHistory->appendDensity(key, average, beta);
        }

        beta += step;
    }
}

CAHistory* TestCAWidget::runCA(int steps)
{
    for(int i = 0; i < steps; ++i)
        m_ca->run();

    return m_ca->history();
}

void TestCAWidget::plotTest()
{
    QGridLayout* layout = new QGridLayout(this);
    this->setLayout(layout);

    QwtPlot* activityPlot = getActivityPlot();
    m_plots->append(activityPlot);
    layout->addWidget(activityPlot);

    QStringList keys = m_alphaHistory->getDensities();
    for(int i = 0; i < keys.size(); ++i)
    {
        QwtPlot* densityPlot = getDensityPlot(keys.at(i));
        m_plots->append(densityPlot);
        layout->addWidget(densityPlot);
    }
}

QwtPlot* TestCAWidget::getActivityPlot()
{
    QwtPlot* activityPlot = newPlot(ACTIVITY_TITLE, PROPABILITY_TITLE);

    plot(ALPHA_TITLE, ALPHA_PEN, m_alphaHistory->getActivity(), activityPlot);
    plot(BETA_TITLE, BETA_PEN, m_betaHistory->getActivity(), activityPlot);

    return activityPlot;
}

QwtPlot* TestCAWidget::getDensityPlot(QString key)
{
    QwtPlot* densityPlot = newPlot(QString("%1 - %2").arg(key, DENSITY_TITLE), PROPABILITY_TITLE);

    plot(ALPHA_TITLE, ALPHA_PEN, m_alphaHistory->getDensity(key), densityPlot);
    plot(BETA_TITLE, BETA_PEN, m_betaHistory->getDensity(key), densityPlot);

    return densityPlot;
}

void TestCAWidget::plot(QString title, QPen pen, QVector<QPointF> data, QwtPlot *plot)
{
    QwtPlotCurve* curve = new QwtPlotCurve(title);
    curve->setSamples(data);
    curve->setPen(pen);
    curve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
    curve->attach(plot);

    curve->updateLegend(plot->legend());
}

QwtPlot* TestCAWidget::newPlot(QString yTitle, QString xTitle)
{
    QString title = m_ca->title();

    QwtPlot* plot = new QwtPlot(title);
    plot->setAxisTitle(QwtPlot::yLeft, yTitle);
    plot->setAxisTitle(QwtPlot::xBottom, xTitle);
    plot->insertLegend(new QwtLegend(), QwtPlot::BottomLegend);

    return plot;
}

void TestCAWidget::exportToSVG(QDir saveDir)
{
    for(int i = 0; i < m_plots->length(); ++i)
    {
        QwtPlot* currentPlot = m_plots->at(i);

        QString title = currentPlot->title().text();
        QString plotType = currentPlot->axisTitle(QwtPlot::yLeft).text();

        QString fileName = QString("%1 - %2.svg").arg(title, plotType);

        qDebug() << saveDir.absoluteFilePath(fileName);

        QSvgGenerator generator;
        generator.setFileName( saveDir.absoluteFilePath(fileName) );
        generator.setSize(currentPlot->size());
        generator.setViewBox( QRect( QPoint(0,0), currentPlot->sizeHint() ) );

        QwtPlotRenderer* renderer = new QwtPlotRenderer();
        renderer->renderTo(currentPlot, generator);
    }
}
