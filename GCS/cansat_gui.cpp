#include "cansat_gui.h"
#include "ui_cansat_gui.h"
#include <QSerialPort>
#include <QSerialPortInfo>

Cansat_GUI::Cansat_GUI(QWidget *parent) : QMainWindow(parent), ui(new Ui::Cansat_GUI), parser(new FrameParser(this))
{
    ui->setupUi(this);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);


    //Altitude Graph
    graphWidgets[0] = new Graph(ui->graph1, "Mission Time (s)", "Altitude (m)", 2);
    graphWidgets[0]->setGraphName(0, "PRES");
    graphWidgets[0]->setGraphName(1,"GPS");
    graphWidgets[0]->setGraphColor(1, QColorConstants::Red);
    graphWidgets[0]->setRandomData(0);
    graphWidgets[0]->setRandomData(1);
    graphWidgets[0]->getQCustomPlot()->xAxis->setTicker(textTicker);

    //Temperature Graph
    graphWidgets[1] = new Graph(ui->graph2, "Mission Time (s)", "Temperature (°C)");
    graphWidgets[1]->setGraphName(0,"TEMP");
    graphWidgets[1]->setRandomData(0);

    //Pressure Graph
    graphWidgets[2] = new Graph(ui->graph3, "Mission Time (s)", "Pressure (kPa)");
    graphWidgets[2]->setGraphName(0, "PRES");
    graphWidgets[2]->setRandomData(0);

    //Gyroscope Graph
    graphWidgets[3] = new Graph(ui->graph4, "Mission Time (s)", "Gyroscope (deg/s)", 3);
    graphWidgets[3]->setGraphName(0, "R");
    graphWidgets[3]->setGraphName(1, "P");
    graphWidgets[3]->setGraphName(2, "Y");
    graphWidgets[3]->setGraphColor(1, QColorConstants::Red);
    graphWidgets[3]->setGraphColor(2, QColorConstants::Green);
    graphWidgets[3]->setRandomData(0);
    graphWidgets[3]->setRandomData(1);
    graphWidgets[3]->setRandomData(2);

    //Accelerometer Graph
    graphWidgets[4] = new Graph(ui->graph5, "Mission Time (s)", "Acceleraction (deg/s^2)", 3);
    graphWidgets[4]->setGraphName(0, "R");
    graphWidgets[4]->setGraphName(1, "P");
    graphWidgets[4]->setGraphName(2, "Y");
    graphWidgets[4]->setGraphColor(1, QColorConstants::Red);
    graphWidgets[4]->setGraphColor(2, QColorConstants::Green);
    graphWidgets[4]->setRandomData(0);
    graphWidgets[4]->setRandomData(1);
    graphWidgets[4]->setRandomData(2);

    //Magnetometer Graph
    graphWidgets[5] = new Graph(ui->graph6, "Mission Time (s)", "Magnetic Field (G)", 3);
    graphWidgets[5]->setGraphName(0, "R");
    graphWidgets[5]->setGraphName(1, "P");
    graphWidgets[5]->setGraphName(2, "Y");
    graphWidgets[5]->setGraphColor(1, QColorConstants::Red);
    graphWidgets[5]->setGraphColor(2, QColorConstants::Green);
    graphWidgets[5]->setRandomData(0);
    graphWidgets[5]->setRandomData(1);
    graphWidgets[5]->setRandomData(2);

    //Auto Gyro Descender Graph
    graphWidgets[6] = new Graph(ui->graph7, "Mission Time (s)", "Auto-Gyro Rate (deg/s)");
    graphWidgets[6]->setGraphName(0, "AGR");
    graphWidgets[6]->setRandomData(0);

    //GPS Coordinate Graph
    graphWidgets[7] = new Graph(ui->graph8, "Longitude (deg)", "Latitude (deg)");
    graphWidgets[7]->setGraphName(0, "COORD");
    graphWidgets[7]->setRandomData(0);
    //connecting signals and slots
    connect(parser, &FrameParser::newDataParsed, this, &Cansat_GUI::updateGUI);

}

void Cansat_GUI::updateGUI(int ID, QString time, float packet_count,
                          QString mode, QString state, float altitude, float temperature, float pressure, float voltage,
                          float gyro_r, float gyro_p, float gyro_y,
                          float accel_r, float accel_p, float accel_y, float mag_r,
                          float mag_p, float mag_y, float auto_gyro_rotation_rate,
                          QString gps_time, float gps_altitude, float gps_latitude,
                          float gps_longitude, int gps_sats, QString cmd_echo){


    auto time_result = parser->TimeToFloat(time);
    float float_time = time_result.first;
    QString string_time = time_result.second;



    textTicker = QSharedPointer<QCPAxisTickerText>(new QCPAxisTickerText);


    graphWidgets[0]->getQCustomPlot()->xAxis->setTicker(textTicker);
    graphWidgets[0]->addPoint(0, float_time, altitude);
    graphWidgets[0]->addPoint(1, float_time, altitude);

    // Temperature Graph
    graphWidgets[1]->getQCustomPlot()->xAxis->setTicker(textTicker);
    graphWidgets[1]->addPoint(0, float_time, temperature);

    // Pressure Graph
    graphWidgets[2]->getQCustomPlot()->xAxis->setTicker(textTicker);
    graphWidgets[2]->addPoint(0, float_time, pressure);

    // Gyroscope Graph
    graphWidgets[3]->getQCustomPlot()->xAxis->setTicker(textTicker);
    graphWidgets[3]->addPoint(0, float_time, gyro_r);
    graphWidgets[3]->addPoint(1, float_time, gyro_p);
    graphWidgets[3]->addPoint(2, float_time, gyro_y);

    // Accelerometer Graph
    graphWidgets[4]->getQCustomPlot()->xAxis->setTicker(textTicker);
    graphWidgets[4]->addPoint(0, float_time, accel_r);
    graphWidgets[4]->addPoint(1, float_time, accel_p);
    graphWidgets[4]->addPoint(2, float_time, accel_y);

    // Magnetometer Graph
    graphWidgets[5]->getQCustomPlot()->xAxis->setTicker(textTicker);
    graphWidgets[5]->addPoint(0, float_time, mag_r);
    graphWidgets[5]->addPoint(1, float_time, mag_p);
    graphWidgets[5]->addPoint(2, float_time, mag_y);

    // Auto Gyro Descender Graph
    graphWidgets[6]->getQCustomPlot()->xAxis->setTicker(textTicker);
    graphWidgets[6]->addPoint(0, float_time, auto_gyro_rotation_rate);

    // GPS Coordinate Graph
    graphWidgets[7]->addPoint(0, gps_longitude, gps_latitude);


}



Cansat_GUI::~Cansat_GUI()
{
    delete ui;
}
//Wasn't sure about updating this stuff, but I can do it too.


serial = new QSerialPort(this);
connect(serial, &QSerialPort::readyRead, this, &Cansat_GUI::readSerialData);

void Cansat_GUI::on_Calibrate_clicked()
{
    if (serial && serial->isOpen()) {
        QByteArray calibrateCommand = "CALIBRATE\n";  // Replace with actual command your system expects
        serial->write(calibrateCommand);
        qDebug() << "Calibration command sent.";
    } else {
        qDebug() << "Serial port not open!";
    }
}


void Cansat_GUI::on_Connect_clicked()
{
    qDebug() << "Connect button clicked";

    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Disconnected from serial port.";
        return;
    }

    // Configure serial port (update with correct values if needed)
    serial->setPortName("COM3"); // TODO: replace with dynamic selection if needed
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port opened successfully!";
    } else {
        qDebug() << "Failed to open serial port:" << serial->errorString();
    }
}

void Cansat_GUI::readSerialData()
{
    QByteArray data = serial->readAll();
    qDebug() << "Received data:" << data;

    // Optional: send data to parser
    parser->parseFrame(data);
    savedTelemetryData.append(QString::fromUtf8(data));  // In readSerialData()
}

void Cansat_GUI::on_Cx_on_clicked()
{
    if (serial && serial->isOpen()) {
        QByteArray command = "CXON\n";  // Replace with actual command
        serial->write(command);
        qDebug() << "CXON command sent.";
    } else {
        qDebug() << "Serial port not open!";
    }
}


void Cansat_GUI::on_Load_Data_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Telemetry File", "", "Text Files (*.txt *.csv)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file!";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        parser->parseFrame(line.toUtf8());
    }

    qDebug() << "Data loaded from file:" << fileName;
}

void Cansat_GUI::on_Mechanism_clicked()
{
    if (serial && serial->isOpen()) {
        QByteArray command = "MECHANISM\n";  // Replace with real trigger
        serial->write(command);
        qDebug() << "Mechanism command sent.";
    } else {
        qDebug() << "Serial port not open!";
    }
}


QStringList savedTelemetryData;
void Cansat_GUI::on_Save_Data_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Telemetry", "", "Text Files (*.txt *.csv)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing!";
        return;
    }

    QTextStream out(&file);
    for (const QString &line : savedTelemetryData)
        out << line << '\n';

    qDebug() << "Telemetry data saved to:" << fileName;
}


void Cansat_GUI::on_Set_Time_clicked()
{
    if (serial && serial->isOpen()) {
        QString timeCommand = QString("TIME:%1\n").arg(QDateTime::currentDateTime().toString("hh:mm:ss"));
        serial->write(timeCommand.toUtf8());
        qDebug() << "Time sync command sent:" << timeCommand;
    } else {
        qDebug() << "Serial port not open!";
    }
}


void Cansat_GUI::on_Simulate_clicked()
{
    qDebug() << "Simulate button clicked";

    // Simulate one full packet and feed to parser
    QString fakeData = "ID:1,TIME:12:00:00,ALT:123.4,TEMP:22.5,PRES:101.3,VOLT:3.7,"
                       "GYRO_R:0.1,GYRO_P:0.2,GYRO_Y:0.3,"
                       "ACC_R:0.1,ACC_P:0.2,ACC_Y:0.3,"
                       "MAG_R:0.4,MAG_P:0.5,MAG_Y:0.6,"
                       "AGR:0.7,GPS_TIME:12:00:00,GPS_ALT:124.5,GPS_LAT:39.1234,"
                       "GPS_LONG:-76.5432,GPS_SATS:8,CMD_ECHO:OK\n";

    parser->parseFrame(fakeData.toUtf8());
}

