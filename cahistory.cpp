#include "cahistory.h"

CAHistory::CAHistory()
{
    m_density = DensityContainer();
    m_activity = QVector<QPointF>();
}

void CAHistory::appendDensity(QString key, float value, float x)
{
    if(m_density.contains(key))
    {
        if(x == -1.0)
            x = m_density.value(key)->size();

        QPointF point = QPointF(x, value);
        m_density.value(key)->append(point);
    }
    else
    {
        if(x == -1.0)
            x = 0.0;

        QPointF point = QPointF(x, value);
        QVector<QPointF>* vector = new QVector<QPointF>();
        vector->append(point);
        m_density.insert(key, vector);
    }
}

void CAHistory::appendActivity(float value, float x)
{
    if(x == -1.0)
        x = m_activity.size();

    m_activity.append( QPointF(x, value) );
}

QVector<QPointF> CAHistory::getDensity(QString key) const
{
    return *(m_density.value(key));
}

QVector<QPointF> CAHistory::getActivity() const
{
    return m_activity;
}

QStringList CAHistory::getDensities() const
{
    return QStringList(m_density.keys());
}

float CAHistory::averageDensity(QString key)
{
    QVector<QPointF>* values = m_density.value(key);
    float sum = 0.0;

    for(int i = 0; i < values->size(); ++i)
    {
        sum += values->at(i).y();
    }

    return sum / values->size();
}

bool CAHistory::empty()
{
    return m_activity.empty() && m_density.empty();
}
