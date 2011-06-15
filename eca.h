#ifndef ECA_H
#define ECA_H

#include "abstractca.h"

#include <QList>

class ECA;

typedef int (ECA::*Clause)(QVector<int> neighbours, QPoint self);

class ECA : public AbstractCA
{
public:
    ECA(float alpha, float beta, int xLength, int yLength, QString title, int ecaNumber);

private:
    QVector<int> neighbourhood(QPoint pos);
    QVector<int> eigenNeighbourhood(QPoint pos);
    int rule(QVector<int> neighbours, QPoint self);

    int m_ecaNumber;

    QList<Clause>* m_usedClauses;
    Clause m_clauseArray[8];

    int clause000(QVector<int> neighbours, QPoint self);
    int clause001(QVector<int> neighbours, QPoint self);
    int clause010(QVector<int> neighbours, QPoint self);
    int clause011(QVector<int> neighbours, QPoint self);

    int clause100(QVector<int> neighbours, QPoint self);
    int clause101(QVector<int> neighbours, QPoint self);
    int clause110(QVector<int> neighbours, QPoint self);
    int clause111(QVector<int> neighbours, QPoint self);
};

#endif // ECA_H
