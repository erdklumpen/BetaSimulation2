#include "castate.h"

CAState::CAState(int xLength, int yLength)
{
    m_xLength = xLength;
    m_yLength = yLength;

    m_eigenData = new StateVector(m_yLength);
    m_observedData = new StateVector(m_yLength);

    for(int i = 0; i < yLength; ++i)
    {
        m_eigenData->replace(i, new QVector<int>(m_xLength));
        m_observedData->replace(i, new QVector<int>(m_xLength));
    }
}

CAState::~CAState()
{
    for(int i = 0; i < ySize(); ++i)
    {
        delete m_eigenData->at(i);
        delete m_observedData->at(i);
    }

    delete m_eigenData;
    delete m_observedData;
}

QString CAState::toString()
{
    QString out("");

    for(int i = 0; i < ySize(); ++i)
    {
        out += toStringOneDimension(i);
        out += "\n";
    }

    return out;
}

QString CAState::toStringOneDimension(int y)
{
    QString out("");

    QVector<int>* vec = m_eigenData->at(y);

    for(int i = 0; i < xSize(); ++i)
        out += QString(" %1 ").arg(vec->at(i));

    return out;
}

float CAState::density(int x)
{
    float sum = 0.0;

    for(int i = 0; i < ySize(); ++i)
        sum += m_eigenData->at(i)->count(x);

    return ( (sum / xSize() ) / ySize() );
}

float CAState::densityXY(int x, int y)
{
    float sum = 0.0;

    for(int i = -1; i < ySize(); ++i)
    {
        for(int j = -1; j < ySize(); ++j)
        {
            if(atEigen(QPoint(i, j)) == x && atEigen(QPoint(i + 1, j + 1)) == y)
                sum += 1;
        }
    }

    return ( (sum / xSize() ) / ySize() );
}

int CAState::size()
{
    return xSize() * ySize();
}

int CAState::xSize()
{
    return m_xLength;
}

int CAState::ySize()
{
    return m_yLength;
}

int CAState::atEigen(QPoint pos)
{
    return at(pos, m_eigenData);
}

int CAState::atObserved(QPoint pos)
{
    return at(pos, m_observedData);
}

int CAState::at(QPoint pos, StateVector *stateVec)
{
    if(pos.y() < 0)
        return atOneDimension(pos.x(), stateVec->at(ySize() - 1) );

    if(pos.y() >= ySize())
        return atOneDimension(pos.x(), stateVec->at(0));

    return atOneDimension(pos.x(), stateVec->at(pos.y()));
}

int CAState::atOneDimension(int xPos, QVector<int> *vec)
{
    if(xPos < 0)
        return vec->at(xSize() - 1);

    if(xPos >= xSize())
        return vec->at(0);

    return vec->at(xPos);
}

void CAState::setAtEigen(QPoint pos, int value)
{
    setAt(pos, value, m_eigenData);
}

void CAState::setAtObserved(QPoint pos, int value)
{
    setAt(pos, value, m_observedData);
}

void CAState::setAtBoth(QPoint pos, int value)
{
    setAtEigen(pos, value);
    setAtObserved(pos, value);
}

void CAState::setAt(QPoint pos, int value, StateVector *stateVec)
{
    setAtOneDimension(pos.x(), value, stateVec->at(pos.y()));
}

void CAState::setAtOneDimension(int xPos, int value, QVector<int> *vec)
{
    vec->replace(xPos, value);
}
