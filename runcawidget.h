#ifndef RUNCAWIDGET_H
#define RUNCAWIDGET_H

#include "abstractca.h"

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QDir>
#include <QSvgGenerator>

namespace Ui {
    class RunCAWidget;
}

class RunCAWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RunCAWidget(AbstractCA* ca, QWidget *parent = 0);
    ~RunCAWidget();

    void runCA(int steps);
    void exportToSVG(QDir saveDir);

protected:
    void changeEvent(QEvent *e);

private:
    void draw(int row);

    Ui::RunCAWidget *ui;
    AbstractCA* m_ca;
};

#endif // RUNCAWIDGET_H
