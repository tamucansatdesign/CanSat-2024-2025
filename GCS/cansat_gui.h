#ifndef CANSAT_GUI_H
#define CANSAT_GUI_H

#include <QMainWindow>
#include "Graph.h"
#include "frame_parser.h"
QSerialPort *serial;

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
    void readSerialData();
private slots:
    void updateGUI(int ID, QString time, float packet_count,
                      QString mode, QString state, float altitude, float temperature, float pressure, float voltage,
                      float gyro_r, float gyro_p, float gyro_y,
                      float accel_r, float accel_p, float accel_y, float mag_r,
                      float mag_p, float mag_y, float auto_gyro_rotation_rate,
                      QString gps_time, float gps_altitude, float gps_latitude,
                      float gps_longitude, int gps_sats, QString cmd_echo);

<<<<<<< HEAD
    void on_Calibrate_clicked();

    void on_Connect_clicked();

    void on_Cx_on_clicked();

    void on_Load_Data_clicked();

    void on_Mechanism_clicked();

    void on_Save_Data_clicked();

    void on_Set_Time_clicked();

    void on_Simulate_clicked();
=======
    void on_connectSerial_clicked();
>>>>>>> 802247bdd8bf4697290deaeb424781e6dffe343d

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

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////
#include "cansat_gui.h"
#include "ui_cansat_gui.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QDebug>
#include <QStringList>

CanSat_GUI::CanSat_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CanSat_GUI)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &CanSat_GUI::readSerialData);

    // Graph setup
    setupGraphs();

    connect(ui->serialConnect, &QPushButton::clicked, this, &CanSat_GUI::toggleSerialConnection);
    connect(ui->startTelemetry, &QPushButton::clicked, this, &CanSat_GUI::toggleTelemetry);
    connect(ui->saveButton, &QPushButton::clicked, this, &CanSat_GUI::saveData);
    connect(ui->loadButton, &QPushButton::clicked, this, &CanSat_GUI::loadData);

    updateSerialPorts();
}

CanSat_GUI::~CanSat_GUI()
{
    if (serial->isOpen()) serial->close();
    delete ui;
}

void CanSat_GUI::setupGraphs()
{
    // Altitude graph
    ui->altGraph->addGraph(); // Container
    ui->altGraph->graph(0)->setName("Container");
    ui->altGraph->addGraph(); // Payload
    ui->altGraph->graph(1)->setName("Payload");
    ui->altGraph->xAxis->setLabel("Packet Count");
    ui->altGraph->yAxis->setLabel("Altitude (m)");
    ui->altGraph->legend->setVisible(true);

    // Add other graphs similarly...
}

void CanSat_GUI::updateSerialPorts()
{
    ui->serialPorts->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        ui->serialPorts->addItem(port.portName());
    }
}

void CanSat_GUI::toggleSerialConnection()
{
    if (!serial->isOpen()) {
        serial->setPortName(ui->serialPorts->currentText());
        serial->setBaudRate(QSerialPort::Baud9600);
        if (serial->open(QIODevice::ReadWrite)) {
            ui->serialConnect->setText("Disconnect");
            allPackets.clear();
            clearGraphs();
            ui->statusBox->clear();
            ui->telemetryBox->clear();
        }
    } else {
        serial->close();
        ui->serialConnect->setText("Connect");
    }
}

void CanSat_GUI::readSerialData()
{
    while (serial->canReadLine()) {
        QByteArray line = serial->readLine().trimmed();
        QString packet(line);
        allPackets.append(packet);

        QStringList data = packet.split(',');
        addNewData(packet, data);
    }
}

void CanSat_GUI::addNewData(const QString &packet, const QStringList &data)
{
    if (data.size() < 25) return;

    int ID = data[0].toInt();
    QString time = data[1];
    int packet_count = data[2].toInt();
    QString mode = data[3];
    QString state = data[4];
    float altitude = data[5].toFloat();
    float temperature = data[6].toFloat();
    float pressure = data[7].toFloat();
    float voltage = data[8].toFloat();
    float gyro_r = data[9].toFloat();
    float gyro_p = data[10].toFloat();
    float gyro_y = data[11].toFloat();
    float accel_r = data[12].toFloat();
    float accel_p = data[13].toFloat();
    float accel_y = data[14].toFloat();
    float mag_r = data[15].toFloat();
    float mag_p = data[16].toFloat();
    float mag_y = data[17].toFloat();
    float auto_gyro_rotation_rate = data[18].toFloat();
    QString gps_time = data[19];
    float gps_altitude = data[20].toFloat();
    float gps_latitude = data[21].toFloat();
    float gps_longitude = data[22].toFloat();
    int gps_sats = data[23].toInt();
    QString cmd_echo = data[24];

    ui->telemetryBox->append(packet);

    // Update altitude graph
    ui->altGraph->graph(0)->addData(packet_count, altitude);
    ui->altGraph->graph(1)->addData(packet_count, gps_altitude);
    ui->altGraph->replot();

    ui->statusBox->clear();
    ui->statusBox->append("ID: " + QString::number(ID));
    ui->statusBox->append("Time: " + time);
    ui->statusBox->append("Packet Count: " + QString::number(packet_count));
    ui->statusBox->append("Mode: " + mode);
    ui->statusBox->append("State: " + state);
    ui->statusBox->append("Temperature: " + QString::number(temperature));
    ui->statusBox->append("Pressure: " + QString::number(pressure));
    ui->statusBox->append("Voltage: " + QString::number(voltage));
    ui->statusBox->append("Gyro [R,P,Y]: " + QString::number(gyro_r) + ", " + QString::number(gyro_p) + ", " + QString::number(gyro_y));
    ui->statusBox->append("Accel [R,P,Y]: " + QString::number(accel_r) + ", " + QString::number(accel_p) + ", " + QString::number(accel_y));
    ui->statusBox->append("Mag [R,P,Y]: " + QString::number(mag_r) + ", " + QString::number(mag_p) + ", " + QString::number(mag_y));
    ui->statusBox->append("Auto Gyro Rate: " + QString::number(auto_gyro_rotation_rate));
    ui->statusBox->append("GPS [Time, Alt, Lat, Long, Sats]: " + gps_time + ", " + QString::number(gps_altitude) + ", " + QString::number(gps_latitude) + ", " + QString::number(gps_longitude) + ", " + QString::number(gps_sats));
    ui->statusBox->append("Cmd Echo: " + cmd_echo);
}

void CanSat_GUI::clearGraphs()
{
    ui->altGraph->graph(0)->data()->clear();
    ui->altGraph->graph(1)->data()->clear();
    ui->altGraph->replot();
    // Clear other graphs similarly
}

void CanSat_GUI::toggleTelemetry()
{
    if (!serial->isOpen()) return;

    if (ui->startTelemetry->text() == "Start Telemetry") {
        serial->write("0\r");
        ui->startTelemetry->setText("Stop Telemetry");
    } else {
        serial->write("1\r");
        ui->startTelemetry->setText("Start Telemetry");
    }
}

void CanSat_GUI::saveData()
{
    QFile file(ui->outputName->text() + ".csv");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString &line : allPackets) {
            out << line << "\n";
        }
        file.close();
    }
}

void CanSat_GUI::loadData()
{
    QFile file(ui->outputName->text() + ".csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    allPackets.clear();
    clearGraphs();
    ui->statusBox->clear();
    ui->telemetryBox->clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        addNewData(line, line.split(','));
    }
    file.close();
}


