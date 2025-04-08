#include "cansat_gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cansat_GUI w;
    w.parser->startSerialCommunication("/dev/ttyUSB0", 9600);
    w.show();
    return a.exec();
}


#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QFile>
#include <QTextStream>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updatePorts();
    void connectSerial();
    void readData();
    void processPacket(const QString &packet);
    void saveData();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QTimer *portCheckTimer;
    QList<QString> allPackets;
    QChart *altChart;
    QLineSeries *altSeries;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), serial(new QSerialPort(this))
{
    ui->setupUi(this);

    altChart = new QChart();
    altSeries = new QLineSeries();
    altChart->addSeries(altSeries);

    QChartView *chartView = new QChartView(altChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartLayout->addWidget(chartView);

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectSerial);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveData);

    portCheckTimer = new QTimer(this);
    connect(portCheckTimer, &QTimer::timeout, this, &MainWindow::updatePorts);
    portCheckTimer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePorts()
{
    ui->portComboBox->clear();
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        ui->portComboBox->addItem(info.portName());
    }
}

void MainWindow::connectSerial()
{
    if (serial->isOpen()) {
        serial->close();
        ui->connectButton->setText("Connect");
    } else {
        serial->setPortName(ui->portComboBox->currentText());
        serial->setBaudRate(QSerialPort::Baud9600);
        if (serial->open(QIODevice::ReadWrite)) {
            ui->connectButton->setText("Disconnect");
        }
    }
}

void MainWindow::readData()
{
    while (serial->canReadLine()) {
        QString packet = serial->readLine().trimmed();
        processPacket(packet);
    }
}

void MainWindow::processPacket(const QString &packet)
{
    allPackets.append(packet);
    QStringList data = packet.split(",");
    if (data.size() > 6) {
        double altitude = data[6].toDouble();
        altSeries->append(QDateTime::currentSecsSinceEpoch(), altitude);
    }
}

void MainWindow::saveData()
{
    QFile file("output.csv");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString &packet : allPackets) {
            out << packet << "\n";
        }
        file.close();
    }
}
