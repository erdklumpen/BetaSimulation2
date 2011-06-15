#include "gameoflife.h"

GameOfLife::GameOfLife(float alpha, float beta, int xLength, int yLength, QString title)
    : AbstractCA(alpha, beta, xLength, yLength, title)
{
}

QVector<int> GameOfLife::neighbourhood(QPoint pos)
{
    return mooreNeighbourhood(pos, m_state);
}

QVector<int> GameOfLife::eigenNeighbourhood(QPoint pos)
{
    return mooreNeighbourhood(pos, m_state, true);
}

int GameOfLife::rule(QVector<int> neighbours, QPoint self)
{
    int sum = 0;

    int selfState = m_state->atEigen(self);

    for(int i = 0; i < neighbours.size(); ++i)
    {
        if(neighbours.at(i) == 1)
            sum += 1;
    }

    if(selfState == 0 && sum == 3)
        return 1;

    if(selfState == 1 && (sum == 2 || sum == 3))
        return 1;

    return 0;
}
