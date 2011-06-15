#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settings.h"
#include "runcawidget.h"
#include "testcawidget.h"

#include "eca.h"
#include "gameoflife.h"
#include "minority.h"

#include <QMainWindow>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    Settings* m_settings;

private slots:
    void on_actionExportieren_triggered();
    void on_actionMinority_triggered();
    void on_actionMinority_2_triggered();
    void on_actionSpiel_des_Lebens_2_triggered();
    void on_actionSpiel_des_Lebens_triggered();
    void on_actionECA_2_triggered();
    void closeTab(int index);

    void on_actionECA_triggered();
    void on_actionEinstellungen_triggered();
};

#endif // MAINWINDOW_H
