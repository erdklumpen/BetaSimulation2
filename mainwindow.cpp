#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_settings = new Settings(1.0, 1.0, 100, 10, 10, true, true, true, 0.0, 1.0, 0.1, 100, this);

    this->connect(ui->tabArea, SIGNAL(tabCloseRequested(int)), SLOT(closeTab(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionEinstellungen_triggered()
{
    m_settings->exec();
}

void MainWindow::closeTab(int index)
{
    ui->tabArea->widget(index)->deleteLater();
    ui->tabArea->removeTab(index);
}

//ECA
void MainWindow::on_actionECA_triggered()
{
    bool ok;
    int ecaNumber = QInputDialog::getInt(this, "ECA Nummer", "Bitte die ECA Nummer eingeben", 0, 0, 255, 1, &ok);

    if(ok)
    {
        QString title = QString("ECA - %1").arg(ecaNumber);

        ECA* eca = new ECA(m_settings->alpha(), m_settings->beta(), m_settings->xLength(), 1, title, ecaNumber);
        RunCAWidget* runCAWidget = new RunCAWidget(eca);
        ui->tabArea->addTab(runCAWidget, title);
        runCAWidget->runCA(m_settings->steps());
    }
}

//ECA test
void MainWindow::on_actionECA_2_triggered()
{
    bool ok;
    int ecaNumber = QInputDialog::getInt(this, "ECA Nummer", "Bitte die ECA Nummer eingeben", 0, 0, 255, 1, &ok);

    if(ok)
    {
        QString title = QString("ECA - %1").arg(ecaNumber);

        ECA* eca = new ECA(m_settings->alpha(), m_settings->beta(), m_settings->xLength(), 1, title, ecaNumber);
        TestCAWidget* testCAWidget = new TestCAWidget(eca);
        ui->tabArea->addTab(testCAWidget, title);

        float start = m_settings->start();
        float stop = m_settings->stop();
        float stepWidth = m_settings->stepWidth();

        bool testAlpha = m_settings->testAlpha();
        bool testBeta = m_settings->testBeta();
        testCAWidget->runTest(m_settings->samples(), m_settings->steps(), start, stop, stepWidth, testAlpha, testBeta);
    }
}

//Game of Life
void MainWindow::on_actionSpiel_des_Lebens_2_triggered()
{
    float alpha = m_settings->alpha();
    float beta = m_settings->beta();
    int xLength = m_settings->xLength();
    int yLength = m_settings->yLength();

    QString title = "Spiel des Lebens";

    GameOfLife* gol = new GameOfLife(alpha, beta, xLength, yLength, title);
    RunCAWidget* runCAWidget = new RunCAWidget(gol);
    ui->tabArea->addTab(runCAWidget, title);
    runCAWidget->runCA(m_settings->steps());
}

//Game of Life test
void MainWindow::on_actionSpiel_des_Lebens_triggered()
{
    float alpha = m_settings->alpha();
    float beta = m_settings->beta();
    int xLength = m_settings->xLength();
    int yLength = m_settings->yLength();

    QString title = "Spiel des Lebens";

    GameOfLife* gol = new GameOfLife(alpha, beta, xLength, yLength, title);
    TestCAWidget* testCAWidget = new TestCAWidget(gol);
    ui->tabArea->addTab(testCAWidget, title);

    float start = m_settings->start();
    float stop = m_settings->stop();
    float stepWidth = m_settings->stepWidth();

    bool testAlpha = m_settings->testAlpha();
    bool testBeta = m_settings->testBeta();
    testCAWidget->runTest(m_settings->samples(), m_settings->steps(), start, stop, stepWidth, testAlpha, testBeta);
}

//Minority
void MainWindow::on_actionMinority_2_triggered()
{
    float alpha = m_settings->alpha();
    float beta = m_settings->beta();
    int xLength = m_settings->xLength();
    int yLength = m_settings->yLength();

    QString title = "Minority";

    Minority* minority = new Minority(alpha, beta, xLength, yLength, title);
    RunCAWidget* runCAWidget = new RunCAWidget(minority);
    ui->tabArea->addTab(runCAWidget, title);
    runCAWidget->runCA(m_settings->steps());
}

//Minority test
void MainWindow::on_actionMinority_triggered()
{
    float alpha = m_settings->alpha();
    float beta = m_settings->beta();
    int xLength = m_settings->xLength();
    int yLength = m_settings->yLength();

    QString title = "Minority";

    Minority* minority = new Minority(alpha, beta, xLength, yLength, title);
    TestCAWidget* testCAWidget = new TestCAWidget(minority);
    ui->tabArea->addTab(testCAWidget, title);

    float start = m_settings->start();
    float stop = m_settings->stop();
    float stepWidth = m_settings->stepWidth();

    bool testAlpha = m_settings->testAlpha();
    bool testBeta = m_settings->testBeta();
    testCAWidget->runTest(m_settings->samples(), m_settings->steps(), start, stop, stepWidth, testAlpha, testBeta);
}

void MainWindow::on_actionExportieren_triggered()
{
    QString dirPath = QFileDialog::getExistingDirectory();
    QDir dir(dirPath);

    QWidget* widget = ui->tabArea->currentWidget();

    RunCAWidget* runCAWidget = dynamic_cast<RunCAWidget*>(widget);

    if(runCAWidget != NULL)
    {
        runCAWidget->exportToSVG(dir);
        return;
    }

    TestCAWidget* testCAWidget = dynamic_cast<TestCAWidget*>(widget);

    if(testCAWidget != NULL)
    {
        testCAWidget->exportToSVG(dir);
        return;
    }
}
