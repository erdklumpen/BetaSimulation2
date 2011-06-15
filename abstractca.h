#ifndef ABSTRACTCA_H
#define ABSTRACTCA_H

#include "castate.h"
#include "cahistory.h"

#include <boost/random.hpp>
#include <ctime>

#include <QVector>
#include <QPoint>

typedef boost::mt19937 MersenneTwister;
typedef boost::uniform_real<> Distribution;
typedef boost::variate_generator<MersenneTwister&, boost::uniform_real<> > Generator;

class AbstractCA
{
public:
    AbstractCA(float alpha, float beta, int xLength, int yLength, QString title = "Default CA");
    ~AbstractCA();

    void run();

    void initCAState();
    CAState* state() {return m_state;}

    void setAlpha(float probability) {m_alpha = probability;}
    void setBeta(float probability) {m_beta = probability;}

    float alpha() {return m_alpha;}
    float beta() {return m_beta;}

    QString title() {return m_title;}
    float getRandomNumber() {return (*m_gen)();}

    int dimensions() {return m_dimensions;}
    int stepsDone() {return m_stepsDone;}

    CAHistory* history() {return m_history;}
    void initHistory() {m_history = new CAHistory();}

    float activity();
    float density(int x) {return m_state->density(x);}
    float densityXY(int x, int y) {return m_state->densityXY(x, y);}

    static QVector<int> mooreNeighbourhood(QPoint pos, CAState* state, bool eigen = false);

protected:
    virtual QVector<int> neighbourhood(QPoint pos) =0;
    virtual QVector<int> eigenNeighbourhood(QPoint pos) =0;
    virtual int rule(QVector<int> neighbours, QPoint self) =0;

    CAState *m_state;
    CAState *m_workState;
    CAHistory *m_history;

private:
    void setAt(QPoint pos, int newState);
    void update(QPoint pos, int newState);
    void setDimensions(int dimensions) {m_dimensions = dimensions;}

    int m_dimensions;
    int m_stepsDone;

    float m_alpha;
    float m_beta;

    QString m_title;

    MersenneTwister m_rng;
    Distribution m_dist;
    Generator* m_gen;
};

#endif // ABSTRACTCA_H
