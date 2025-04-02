#include "Graph.h"


Graph::Graph(QCustomPlot *plot, const QString& xlabel, const QString& ylabel, int graphNumber) : customPlot(plot){
    customPlot->xAxis->setLabel(xlabel);
    customPlot->yAxis->setLabel(ylabel);
    customPlot->legend->setVisible(true);

    QFont axisFont;
    axisFont.setPointSize(14);
    customPlot->xAxis->setLabelFont(axisFont);
    customPlot->yAxis->setLabelFont(axisFont);



    for (int i = 0; i < graphNumber; ++i) {
        QCPGraph *graph = customPlot->addGraph();
        graphs.append(graph);
        xData.append(QVector<double>());
        yData.append(QVector<double>());
    }

}

void Graph::addPoint(int index, float x, float y){
    // QCPGraph *graph = graphs[index];
    xData[index].append(x);
    yData[index].append(y);

    graphs[index]->setData(xData[index], yData[index]);

    customPlot->replot();
}

void Graph::setRandomData(int index){
    QVector<double> x(50), y(50);
    for (int i = 0; i < 50; ++i) {
        x[i] = i;
        y[i] = QRandomGenerator::global()->bounded(0, 100); // Random y values between 0 and 100
    }

    graphs[index]->setData(x, y);
    customPlot->rescaleAxes();
    customPlot->replot();
}
void Graph::setGraphColor(int index, const QColor& color){
    graphs[index]->setPen(color);
}

void Graph::setGraphName(int index, const QString& label){
    graphs[index]->setName(label);
}



QCustomPlot* Graph::getQCustomPlot(){
    return customPlot;
}
