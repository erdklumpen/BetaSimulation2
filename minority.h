#ifndef MINORITY_H
#define MINORITY_H

#include "abstractca.h"

class Minority : public AbstractCA
{
public:
    Minority(float alpha, float beta, int xLength, int yLength, QString title);

    QVector<int> neighbourhood(QPoint pos);
    QVector<int> eigenNeighbourhood(QPoint pos);
    int rule(QVector<int> neighbours, QPoint self);
};

#endif // MINORITY_H
