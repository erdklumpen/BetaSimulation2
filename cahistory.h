#ifndef CAHISTORY_H
#define CAHISTORY_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPointF>

#include <QDebug>

typedef QMap< QString, QVector< QPointF >* > DensityContainer;

class CAHistory
{
public:
    CAHistory();
    ~CAHistory() {}

    void appendDensity(QString key, float value, float x = -1.0);
    void appendActivity(float value, float x = -1.0);

    QVector<QPointF> getDensity(QString key) const;
    QVector<QPointF> getActivity() const;

    QStringList getDensities() const;

    float averageDensity(QString key);

    bool empty();

private:
    DensityContainer m_density;
    QVector<QPointF> m_activity;
};

#endif // CAHISTORY_H
