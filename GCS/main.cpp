#include "cansat_gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cansat_GUI w;
    w.show();
    return a.exec();
}
