#include "cansat_gui.h"
#include "ui_cansat_gui.h"

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



