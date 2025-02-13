#ifndef CANSAT_GUI_H
#define CANSAT_GUI_H

#include <QMainWindow>
#include "Graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Cansat_GUI;
}
QT_END_NAMESPACE

class Cansat_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Cansat_GUI(QWidget *parent = nullptr);
    ~Cansat_GUI();

private:
    Ui::Cansat_GUI *ui;
    Graph *graphWidgets[8];
    QTimer *dataTimer;
    double timeElapsed;
};
#endif // CANSAT_GUI_H
