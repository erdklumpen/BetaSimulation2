#include "eca.h"

ECA::ECA(float alpha, float beta, int xLength, int yLength, QString title, int ecaNumber)
    : AbstractCA(alpha, beta, xLength, yLength, title)
{
    m_ecaNumber = ecaNumber;
    m_usedClauses = new QList<Clause>();

    m_clauseArray[0] = &ECA::clause000;
    m_clauseArray[1] = &ECA::clause001;
    m_clauseArray[2] = &ECA::clause010;
    m_clauseArray[3] = &ECA::clause011;

    m_clauseArray[4] = &ECA::clause100;
    m_clauseArray[5] = &ECA::clause101;
    m_clauseArray[6] = &ECA::clause110;
    m_clauseArray[7] = &ECA::clause111;

    for(int i = 0; ecaNumber > 0; ++i)
    {
        int bit = ecaNumber % 2;
        ecaNumber = ecaNumber >> 1;

        if(bit == 1)
            m_usedClauses->append(m_clauseArray[i]);
    }
}

QVector<int> ECA::neighbourhood(QPoint pos)
{
    QVector<int> neighbours(2);

    neighbours[0] = m_state->atObserved( QPoint(pos.x() - 1, pos.y()) );
    neighbours[1] = m_state->atObserved( QPoint(pos.x() + 1, pos.y()) );
    return neighbours;
}

QVector<int> ECA::eigenNeighbourhood(QPoint pos)
{
    QVector<int> neighbours(2);

    neighbours[0] = m_state->atEigen( QPoint(pos.x() - 1, pos.y()) );
    neighbours[1] = m_state->atEigen( QPoint(pos.x() + 1, pos.y()) );
    return neighbours;
}

int ECA::rule(QVector<int> neighbours, QPoint self)
{
    for(int i = 0; i < m_usedClauses->length(); ++i)
    {
        Clause clause = m_usedClauses->at(i);
        int result = (this->*clause)(neighbours, self);

        if(result == 1)
            return true;
    }

    return false;
}

// 000
int ECA::clause000(QVector<int> neighbours, QPoint self)
{
    if(!neighbours[0] && !m_state->atEigen(self) && !neighbours[1])
        return true;

    else
        return false;
}

// 001
int ECA::clause001(QVector<int> neighbours, QPoint self)
{
    if(!neighbours[0] && !m_state->atEigen(self) && neighbours[1])
        return true;

    else
        return false;

}

// 010
int ECA::clause010(QVector<int> neighbours, QPoint self)
{
    if(!neighbours[0] && m_state->atEigen(self) && !neighbours[1])
        return true;

    else
        return false;

}

// 011
int ECA::clause011(QVector<int> neighbours, QPoint self)
{
    if(!neighbours[0] && m_state->atEigen(self) && neighbours[1])
        return true;

    else
        return false;

}

//100
int ECA::clause100(QVector<int> neighbours, QPoint self)
{
    if(neighbours[0] && !m_state->atEigen(self) && !neighbours[1])
        return true;

    else
        return false;

}

// 101
int ECA::clause101(QVector<int> neighbours, QPoint self)
{
    if(neighbours[0] && !m_state->atEigen(self) && neighbours[1])
        return true;

    else
        return false;

}
// 110
int ECA::clause110(QVector<int> neighbours, QPoint self)
{
    if(neighbours[0] && m_state->atEigen(self) && !neighbours[1])
        return true;

    else
        return false;

}

// 111
int ECA::clause111(QVector<int> neighbours, QPoint self)
{
    if(neighbours[0] && m_state->atEigen(self) && neighbours[1])
        return true;

    else
        return false;

}
