#include "cansat_gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cansat_GUI w;
    w.parser->startSerialCommunication("/dev/ttyUSB0", 9600);
    w.show();
    return a.exec();
}
