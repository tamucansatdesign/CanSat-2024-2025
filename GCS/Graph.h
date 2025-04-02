#ifndef GRAPH_H
#define GRAPH_H
#include "qcustomplot.h"
#include <QString>

class Graph {
public:
    Graph(QCustomPlot *plot, const QString &xlabel, const QString &ylabel, int graphNumber=1);

    // void setData(int index, const QVector<double> &x, const QVector<double> &y);
    void addPoint(int index, float x, float y);
    void setRandomData(int index);
    void setGraphColor(int index, const QColor &color);
    void setGraphName(int index, const QString &label);
    QCustomPlot* getQCustomPlot();
private:
    QCustomPlot *customPlot;
    QVector<QCPGraph *> graphs;
    QVector<QVector<double>> xData, yData;
};



#endif // GRAPH_H
