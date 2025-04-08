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
    FrameParser *parser;
private slots:
    void updateGUI(int ID, QString time, float packet_count,
                      QString mode, QString state, float altitude, float temperature, float pressure, float voltage,
                      float gyro_r, float gyro_p, float gyro_y,
                      float accel_r, float accel_p, float accel_y, float mag_r,
                      float mag_p, float mag_y, float auto_gyro_rotation_rate,
                      QString gps_time, float gps_altitude, float gps_latitude,
                      float gps_longitude, int gps_sats, QString cmd_echo);

    void on_connectSerial_clicked();

private:
    Ui::Cansat_GUI *ui;
    Graph *graphWidgets[8];
    QMap<float, QString> timeLabels;
    QSharedPointer<QCPAxisTickerText> textTicker;

};

#endif // CANSAT_GUI_H

/*
string ID, string time, float packet_count,
                       string mode, string state, float altitude, float temperature, float pressure, float voltage
                       float gyro_r, float gyro_p, float gyro_y,
                       float accel_r, float accel_p, float accel_y, float mag_r,
                       float mag_p, float mag_y, float auto_gyro_rotation_rate,
                       string gps_time, float gps_altitude, float gps_latitude,
                       float gps_longitude, int gps_stats, string cmd_echo);
*/
