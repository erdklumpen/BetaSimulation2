#include "abstractca.h"

AbstractCA::AbstractCA(float alpha, float beta, int xLength, int yLength, QString title)
{
    setAlpha(alpha);
    setBeta(beta);

    m_title = title;

    m_rng();
    m_rng.seed(time(0));
    m_gen = new Generator(m_rng, m_dist);

    if(yLength == 1)
        setDimensions(1);
    else
        setDimensions(2);

    m_history = new CAHistory();

    m_state = new CAState(xLength, yLength);
    m_workState = new CAState(xLength, yLength);
    initCAState();
}

AbstractCA::~AbstractCA()
{
    delete m_state;
    delete m_workState;
}

void AbstractCA::initCAState()
{
    m_stepsDone = 0;

    for(int i = 0; i < m_state->ySize(); ++i)
    {
        for(int j = 0; j < m_state->xSize(); ++j)
        {
            double number = getRandomNumber();
            QPoint currentPos = QPoint(j, i);

            if(number > 0.5)
            {
                m_state->setAtBoth(currentPos, 1);
                m_workState->setAtBoth(currentPos, 1);
            }
            else
            {
                m_state->setAtBoth(currentPos, 0);
                m_workState->setAtBoth(currentPos, 0);
            }
        }
    }
}

void AbstractCA::run()
{
    if(m_history->empty())
    {
        m_history->appendActivity(activity());
        m_history->appendDensity("1", density(1));
        m_history->appendDensity("01", densityXY(0, 1));
        m_history->appendDensity("00", densityXY(0, 0));
        m_history->appendDensity("11", densityXY(1, 1));
    }


    for(int j = 0; j < m_state->ySize(); ++j)
    {
        for(int k = 0; k < m_state->xSize(); ++k)
        {
            QPoint currentPos = QPoint(k, j);

            QVector<int> neighbours = neighbourhood(currentPos);
            int newState = rule(neighbours, currentPos);
            update(currentPos, newState);
        }
    }

    CAState* k = m_state;
    m_state = m_workState;
    m_workState = k;

    m_history->appendActivity(activity());
    m_history->appendDensity("1", density(1));
    m_history->appendDensity("01", densityXY(0, 1));
    m_history->appendDensity("00", densityXY(0, 0));
    m_history->appendDensity("11", densityXY(1, 1));

    ++m_stepsDone;
}

void AbstractCA::update(QPoint pos, int newState)
{
    double randAlpha = getRandomNumber();

    if(randAlpha <= alpha())
        setAt(pos, newState);
    else
        setAt(pos, m_state->atEigen(pos));
}

void AbstractCA::setAt(QPoint pos, int newState)
{
    double randBeta = getRandomNumber();

    m_workState->setAtEigen(pos, newState);

    if(randBeta <= beta())
        m_workState->setAtObserved(pos, newState);
    else
        m_workState->setAtObserved(pos, m_state->atObserved(pos));
}

float AbstractCA::activity()
{
    float instable = 0.0;

    for(int i = 0; i < m_state->ySize(); ++i)
    {
        for(int j = 0; j < m_state->xSize(); ++j)
        {
            QPoint currentPos = QPoint(j, i);

            QVector<int> neighbours = neighbourhood(currentPos);
            int newState = rule(neighbours, currentPos);

            if(newState != m_state->atEigen(currentPos))
                ++instable;
        }
    }

    float activity = instable / m_state->size();

    return activity;
}

QVector<int> AbstractCA::mooreNeighbourhood(QPoint pos, CAState *state, bool eigen)
{
    QVector<int> neighbours(8);

    if(eigen)
    {
        neighbours[0] = state->atEigen( QPoint(pos.x() - 1, pos.y() - 1) );
        neighbours[1] = state->atEigen( QPoint(pos.x()    , pos.y() - 1) );
        neighbours[2] = state->atEigen( QPoint(pos.x() + 1, pos.y() - 1) );

        neighbours[3] = state->atEigen( QPoint(pos.x() - 1, pos.y()) );
        neighbours[4] = state->atEigen( QPoint(pos.x() + 1, pos.y()) );

        neighbours[5] = state->atEigen( QPoint(pos.x() - 1, pos.y() + 1) );
        neighbours[6] = state->atEigen( QPoint(pos.x()    , pos.y() + 1) );
        neighbours[7] = state->atEigen( QPoint(pos.x() + 1, pos.y() + 1) );
    }
    else
    {
        neighbours[0] = state->atObserved( QPoint(pos.x() - 1, pos.y() - 1) );
        neighbours[1] = state->atObserved( QPoint(pos.x()    , pos.y() - 1) );
        neighbours[2] = state->atObserved( QPoint(pos.x() + 1, pos.y() - 1) );

        neighbours[3] = state->atObserved( QPoint(pos.x() - 1, pos.y()) );
        neighbours[4] = state->atObserved( QPoint(pos.x() + 1, pos.y()) );

        neighbours[5] = state->atObserved( QPoint(pos.x() - 1, pos.y() + 1) );
        neighbours[6] = state->atObserved( QPoint(pos.x()    , pos.y() + 1) );
        neighbours[7] = state->atObserved( QPoint(pos.x() + 1, pos.y() + 1) );
    }


    return neighbours;
}
