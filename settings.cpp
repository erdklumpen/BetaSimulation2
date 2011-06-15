#include "settings.h"
#include "ui_settings.h"

Settings::Settings(double alpha, double beta, int steps, int xLength, int yLength,
                   bool draw, bool testAlpha, bool testBeta, float start, float stop,
                   float stepWidth, int samples, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->alpha->setValue(alpha);
    ui->beta->setValue(beta);
    ui->steps->setValue(steps);

    ui->xLength->setValue(xLength);
    ui->yLength->setValue(yLength);

    ui->draw->setChecked(draw);
    ui->testAlpha->setChecked(testAlpha);
    ui->testBeta->setChecked(testBeta);

    ui->start->setValue(start);
    ui->stop->setValue(stop);
    ui->width->setValue(stepWidth);

    ui->samples->setValue(samples);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

double Settings::alpha()
{
    return ui->alpha->value();
}

double Settings::beta()
{
    return ui->beta->value();
}

int Settings::steps()
{
    return ui->steps->value();
}

int Settings::xLength()
{
    return ui->xLength->value();
}

int Settings::yLength()
{
    return ui->yLength->value();
}

bool Settings::draw()
{
    return ui->draw->isChecked();
}

bool Settings::testAlpha()
{
    return ui->testAlpha->isChecked();
}

bool Settings::testBeta()
{
    return ui->testBeta->isChecked();
}

float Settings::start()
{
    return ui->start->value();
}

float Settings::stop()
{
    return ui->stop->value();
}

float Settings::stepWidth()
{
    return ui->width->value();
}

int Settings::samples()
{
    return ui->samples->value();
}
