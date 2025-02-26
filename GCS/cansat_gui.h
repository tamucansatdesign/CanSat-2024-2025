#ifndef CANSAT_GUI_H
#define CANSAT_GUI_H

#include <QMainWindow>
#include "Graph.h"
#include "frame_parser.h"

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

private slots:
    void updateGraphs(string ID, string time, double packet_count,
                      string mode, string state, double altitude, double temperature, double pressure, double voltage,
                      double gyro_r, double gyro_p, double gyro_y,
                      double accel_r, double accel_p, double accel_y, double mag_r,
                      double mag_p, double mag_y, double auto_gyro_rotation_rate,
                      string gps_time, double gps_altitude, double gps_latitude,
                      double gps_longitude, int gps_stats, string cmd_echo);

private:
    Ui::Cansat_GUI *ui;
    Graph *graphWidgets[8];
    FrameParser *parser;
};

#endif // CANSAT_GUI_H

/*
string ID, string time, double packet_count,
                       string mode, string state, double altitude, double temperature, double pressure, double voltage
                       double gyro_r, double gyro_p, double gyro_y,
                       double accel_r, double accel_p, double accel_y, double mag_r,
                       double mag_p, double mag_y, double auto_gyro_rotation_rate,
                       string gps_time, double gps_altitude, double gps_latitude,
                       double gps_longitude, int gps_stats, string cmd_echo);
*/
