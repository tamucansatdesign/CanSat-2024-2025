#ifndef SERIAL_PARSER_H
#define SERIAL_PARSER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

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
