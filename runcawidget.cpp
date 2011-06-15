#include "runcawidget.h"
#include "ui_runcawidget.h"

RunCAWidget::RunCAWidget(AbstractCA* ca, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunCAWidget)
{
    ui->setupUi(this);

    m_ca = ca;
}

RunCAWidget::~RunCAWidget()
{
    delete ui;
    delete m_ca;
}

void RunCAWidget::changeEvent(QEvent *e)
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

void RunCAWidget::runCA(int steps)
{
    draw(0);
    int j=0;

    for(int i = 0; i < steps ; ++i)
    {
        m_ca->run();
//        qDebug() << "step " << i << " " << m_ca->history()->getActivity().last().y();

        if(i % 1000 == 0)
        {
            draw(j + 1);
            ++j;
        }
    }
}

void RunCAWidget::exportToSVG(QDir saveDir)
{
    if(ui->graphicsView->scene() == 0)
        return;

    QGraphicsScene* scene = ui->graphicsView->scene();

    QSvgGenerator generator;
    generator.setFileName(saveDir.absoluteFilePath("Activity.svg"));

    int xLength = m_ca->state()->xSize() * 10;
    int yLength = m_ca->state()->ySize() * 10 + m_ca->state()->ySize() * 10 * m_ca->stepsDone();

    qDebug() << "X: " << xLength << " Y: " << yLength;

    generator.setSize(QSize(xLength, yLength));
    generator.setViewBox(QRect(0, 0, xLength, yLength));

    QPainter painter(&generator);
    scene->render(&painter);
}

void RunCAWidget::draw(int row)
{
    CAState* state = m_ca->state();

    if(ui->graphicsView->scene() == 0)
    {
        QGraphicsScene* scene = new QGraphicsScene();
        ui->graphicsView->setScene(scene);
    }

    int yOffset = row * state->ySize() * 10;
    QBrush brush;

    for(int i = 0; i < state->ySize(); ++i)
    {
        for(int j = 0; j < state->xSize(); ++j)
        {
            if(state->atEigen(QPoint(j, i)) == 1)
                brush = QBrush(Qt::black);
            else
                brush = QBrush(Qt::white);

            int x = 0 + j * 10;
            int y = 0 + i * 10 + yOffset;

            ui->graphicsView->scene()->addRect(x, y, 10, 10, QPen(Qt::black), brush);
        }
    }

    ui->graphicsView->scene()->addRect(0, 0+yOffset, state->xSize() * 10, state->ySize() * 10, QPen(Qt::red));
}
