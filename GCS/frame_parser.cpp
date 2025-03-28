#include <iostream>  // Include necessary libraries for input-output
#include <vector>    // Include vector for storing values
#include <sstream>   // Include sstream for string stream operations

#include "frame_parser.h"
#include <QDebug>

// Function to parse CSV data into a Frame struct
// void frame_parser::frame_parser(const QString& csvData) {
//     std::vector<QString> values = splitCSV(csvData);

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

QPair<float, QString> FrameParser::TimeToFloat(QString timeString) {
    // Split the time string (assumed format: HH:MM:SS)
    QStringList timeParts = timeString.split(":");

    if (timeParts.size() != 3) {
        qDebug() << "Invalid time format: " << timeString;
        return QPair<float, QString>(0.0f, timeString);
    }

    bool ok1, ok2, ok3;
    int hours = timeParts[0].toInt(&ok1);
    int minutes = timeParts[1].toInt(&ok2);
    float seconds = timeParts[2].toFloat(&ok3);

    if (!ok1 || !ok2 || !ok3) {
        qDebug() << "Error converting time components";
        return QPair<float, QString>(0.0f, timeString);
    }

    // Convert to total seconds
    float totalSeconds = hours * 3600.0f + minutes * 60.0f + seconds;
    return QPair<float, QString>(totalSeconds, timeString);
}



void FrameParser::readSerialData()
{
    while (serial->canReadLine()) {
        QByteArray data = serial->readLine().trimmed();  // Read incoming data
        QString csvData = QString::fromUtf8(data);       // Convert to QString

        QStringList values = csvData.split(",");
        if (values.size() >= 25) {  // Ensure the data is valid
            int ID = values[0].toInt();
            QString time = values[1];
            int packet_count = values[2].toInt();
            QString mode = values[3];
            QString state = values[4];
            float altitude = values[5].toFloat();
            float temperature = values[6].toFloat();
            float pressure = values[7].toFloat();
            float voltage = values[8].toFloat();
            float gyro_r = values[9].toFloat();
            float gyro_p = values[10].toFloat();
            float gyro_y = values[11].toFloat();
            float accel_r = values[12].toFloat();
            float accel_p = values[13].toFloat();
            float accel_y = values[14].toFloat();
            float mag_r = values[15].toFloat();
            float mag_p = values[16].toFloat();
            float mag_y = values[17].toFloat();
            float auto_gyro_rotation_rate = values[18].toFloat();
            QString gps_time = values[19];
            float gps_altitude = values[20].toFloat();
            float gps_latitude = values[21].toFloat();
            float gps_longitude = values[22].toFloat();
            int gps_sats = values[23].toInt();
            QString cmd_echo = values[24];


            emit newDataParsed(ID,time,packet_count, mode, state,  altitude, temperature, pressure,
                               voltage, gyro_r, gyro_p, gyro_y,
                               accel_r, accel_p, accel_y, mag_r, mag_p, mag_y,
                               auto_gyro_rotation_rate, gps_time, gps_altitude, gps_latitude,
                               gps_longitude, gps_sats, cmd_echo);
        }
    }
}





