#ifndef SERIAL_PARSER_H
#define SERIAL_PARSER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

//#include "frame_parser.h"// Rename to Serial???


// struct Frame {
//     QString ID;
//     float mission_time;
//     float packet_count;
//     QString mode;
//     QString state;
//     float altitude;
//     float temperature;
//     float pressure;
//     float voltage;
//     float gyro_r;
//     float gyro_p;
//     float gyro_y;
//     float accel_r;
//     float accel_p;
//     float accel_y;
//     float mag_r;
// };

class FrameParser : public QObject
{
    Q_OBJECT

public:
    explicit FrameParser(QObject *parent = nullptr);
    void startSerialCommunication(const QString &portName, int baudRate);
    QPair<float, QString> TimeToFloat(QString timeString);
signals:
    void newDataParsed(int ID, QString time, int packet_count,
                       QString mode, QString state, float altitude, float temperature, float pressure, float voltage,
                       float gyro_r, float gyro_p, float gyro_y,
                       float accel_r, float accel_p, float accel_y, float mag_r,
                       float mag_p, float mag_y, float auto_gyro_rotation_rate,
                       QString gps_time, float gps_altitude, float gps_latitude,
                       float gps_longitude, int gps_sats, QString cmd_echo);

private slots:
    void readSerialData();  // Slot to handle incoming serial data

private:
    QSerialPort *serial;
};

#endif // FRAME_PARSER_H


