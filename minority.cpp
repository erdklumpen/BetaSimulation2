#include "minority.h"

Minority::Minority(float alpha, float beta, int xLength, int yLength, QString title)
    : AbstractCA(alpha, beta, xLength, yLength, title)
{
}

QVector<int> Minority::neighbourhood(QPoint pos)
{
    return mooreNeighbourhood(pos, m_state);
}

QVector<int> Minority::eigenNeighbourhood(QPoint pos)
{
    return mooreNeighbourhood(pos, m_state, true);
}

int Minority::rule(QVector<int> neighbours, QPoint self)
{
    int sum = 0;

    for(int i = 0; i < neighbours.size(); ++i)
    {
        if(neighbours.at(i) == 1)
            ++sum;
    }

    if(m_state->atEigen(self) == 1)
        ++sum;

    if(sum <= 4)
        return 1;

    return 0;
}
