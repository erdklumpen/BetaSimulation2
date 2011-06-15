#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(double alpha, double beta, int steps, int xLength, int yLength,
                      bool draw, bool testAlpha, bool testBeta, float start, float stop,
                      float stepWidth, int samples, QWidget *parent = 0);
    ~Settings();

    double alpha();
    double beta();

    int steps();

    int xLength();
    int yLength();

    bool draw();

    bool testAlpha();
    bool testBeta();

    float start();
    float stop();
    float stepWidth();

    int samples();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
