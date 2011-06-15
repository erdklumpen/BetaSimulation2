#ifndef CASTATE_H
#define CASTATE_H

#include <QString>
#include <QVector>
#include <QPoint>

#include <QDebug>

typedef QVector< QVector<int>* > StateVector;

class CAState
{
public:
    CAState(int xLength, int yLength);
    ~CAState();

    float density(int x);
    float densityXY(int x, int y);

    QString toString();

    int size();
    int xSize();
    int ySize();

    void setAtEigen(QPoint pos, int value);
    void setAtObserved(QPoint pos, int value);
    void setAtBoth(QPoint pos, int value);

    int atEigen(QPoint pos);
    int atObserved(QPoint pos);

private:
    StateVector* m_eigenData;
    StateVector* m_observedData;

    int m_xLength;
    int m_yLength;

    QString toStringOneDimension(int y);

    void setAt(QPoint pos, int value, StateVector* stateVec);
    void setAtOneDimension(int xPos, int value, QVector<int>* vec);

    int at(QPoint pos, StateVector* stateVec);
    int atOneDimension(int xPos, QVector<int>* vec);
};

#endif // CASTATE_H
