#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "abstractca.h"

class GameOfLife : public AbstractCA
{
public:
    GameOfLife(float alpha, float beta, int xLength, int yLength, QString title);

    QVector<int> neighbourhood(QPoint pos);
    QVector<int> eigenNeighbourhood(QPoint pos);
    int rule(QVector<int> neighbours, QPoint self);
};

#endif // GAMEOFLIFE_H
