#ifndef SERIAL_PARSER_H
#define SERIAL_PARSER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

//#include "frame_parser.h"// Rename to Serial???


// struct Frame {
//     std::string ID;
//     double mission_time;
//     double packet_count;
//     std::string mode;
//     std::string state;
//     double altitude;
//     double temperature;
//     double pressure;
//     double voltage;
//     double gyro_r;
//     double gyro_p;
//     double gyro_y;
//     double accel_r;
//     double accel_p;
//     double accel_y;
//     double mag_r;
// };

class FrameParser : public QObject
{
    Q_OBJECT

public:
    explicit FrameParser(QObject *parent = nullptr);
    void startSerialCommunication(const QString &portName, int baudRate);

signals:
    void newDataParsed(string ID, string time, double packet_count,
                       string mode, string state, double altitude, double temperature, double pressure, double voltage,
                       double gyro_r, double gyro_p, double gyro_y,
                       double accel_r, double accel_p, double accel_y, double mag_r,
                       double mag_p, double mag_y, double auto_gyro_rotation_rate,
                       string gps_time, double gps_altitude, double gps_latitude,
                       double gps_longitude, int gps_stats, string cmd_echo);

private slots:
    void readSerialData();  // Slot to handle incoming serial data

private:
    QSerialPort *serial;
};

#endif // FRAME_PARSER_H

/*
class serial_parser
{
public:
    serial_parser(const std::string& CSV);
    splitCSV(const std::string& CSV);


signals:


private slots:


private:
    QSerialPort *serial;






};

#endif // SERIAL_PARSER_H
*/
