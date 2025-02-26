#include <iostream>  // Include necessary libraries for input-output
#include <vector>    // Include vector for storing values
#include <sstream>   // Include sstream for string stream operations

#include "frame_parser.h"
#include <QDebug>

// Function to parse CSV data into a Frame struct
// void frame_parser::frame_parser(const std::string& csvData) {
//     std::vector<std::string> values = splitCSV(csvData);

//     if (values.size() >= 16) {
//         frame.ID = values[0];
//         frame.mission_time = std::stod(values[1]);
//         frame.packet_count = std::stod(values[2]);
//         frame.mode = values[3];
//         frame.state = values[4];
//         frame.altitude = std::stod(values[5]);
//         frame.temperature = std::stod(values[6]);
//         frame.pressure = std::stod(values[7]);
//         frame.voltage = std::stod(values[8]);
//         frame.gyro_r = std::stod(values[9]);
//         frame.gyro_p = std::stod(values[10]);
//         frame.gyro_y = std::stod(values[11]);
//         frame.accel_r = std::stod(values[12]);
//         frame.accel_p = std::stod(values[13]);
//         frame.accel_y = std::stod(values[14]);
//         frame.mag_r = values[15];
//         frame.mag_p = values[16];
//         frame.mag_y = values[17];
//         frame.auto_gyro_rotation_rate = values[18];
//         frame.gps_time = values[19];         //hh:mm:ss
//         frame.gps_altitude = values[20];     //deg/s
//         frame.gpa_latitude = values[21];     //deg/s
//         frame.gps_longitude = values[22];    //deg/s
//         frame.gps_sats = values[23]; //int
//         frame.cmd_echo = values[24]; //string
//     }
// }



FrameParser::FrameParser(QObject *parent) : QObject(parent), serial(new QSerialPort(this)) {}

void FrameParser::startSerialCommunication(const QString &portName, int baudRate)
{
    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadOnly)) {
        qDebug() << "Connected to" << portName;
        connect(serial, &QSerialPort::readyRead, this, &FrameParser::readSerialData);
    } else {
        qDebug() << "Failed to open serial port:" << serial->errorString();
    }
}

void FrameParser::readSerialData()
{
    while (serial->canReadLine()) {
        QByteArray data = serial->readLine().trimmed();  // Read incoming data
        QString csvData = QString::fromUtf8(data);       // Convert to QString

        QStringList values = csvData.split(",");
        if (values.size() >= 24) {  // Ensure the data is valid
            string time = values[1].toString();
            double packet_count = values[2].toDouble();
            string mode = values[3].toString();
            string state = values[4].toString();
            double altitude = values[5].toDouble();
            double temperature = values[6].toDouble();
            double pressure = values[7].toDouble();
            double voltage = values[8].toDouble();
            double gyro_r = values[9].toDouble();
            double gyro_p = values[10].toDouble();
            double gyro_y = values[11].toDouble();
            double accel_r = values[12].toDouble();
            double accel_p = values[13].toDouble();
            double accel_y = values[14].toDouble();
            double mag_r = values[15].toDouble();
            double mag_p = values[16].toDouble();
            double mag_y = values[17].toDouble();
            double auto_gyro_rotation_rate = values[18].toDouble();
            string gps_time = values[19].toString();
            double gps_altitude = values[20].toDouble();
            double gps_latitude = values[21].toDouble();
            double gps_longitude = values[22].toDouble();
            int gps_stats = values[23].toInt();
            string cmd_echo = values[24].toString();


            emit newDataParsed(time,packet_count, mode, state,  altitude, temperature, pressure,
                               voltage, gyro_r, gyro_p, gyro_y,
                               accel_r, accel_p, accel_y, mag_r, mag_p, mag_y,
                               auto_gyro_rotation_rate, gps_time, gps_altitude, gps_latitude,
                               gps_longitude, gps_stats, cmd_echo);
        }
    }
}
/*
string ID, string time, double packet_count,
                       string mode, string state, double altitude, double temperature, double pressure, double voltage
                       double gyro_r, double gyro_p, double gyro_y,
                       double accel_r, double accel_p, double accel_y, double mag_r,
                       double mag_p, double mag_y, double auto_gyro_rotation_rate,
                       string gps_time, double gps_altitude, double gps_latitude,
                       double gps_longitude, int gps_stats, string cmd_echo);
*/




