/********************************************************************************
** Form generated from reading UI file 'cansat_gui.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANSAT_GUI_H
#define UI_CANSAT_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Cansat_GUI
{
public:
    QWidget *centralwidget;
    QCustomPlot *graph1;
    QCustomPlot *graph2;
    QCustomPlot *graph3;
    QCustomPlot *graph4;
    QCustomPlot *graph5;
    QCustomPlot *graph6;
    QCustomPlot *graph7;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QCustomPlot *graph8;
    QMenuBar *menubar;
    QMenu *menu2025_CanSat_GUI;
    QMenu *menufd;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Cansat_GUI)
    {
        if (Cansat_GUI->objectName().isEmpty())
            Cansat_GUI->setObjectName("Cansat_GUI");
        Cansat_GUI->resize(1361, 715);
        centralwidget = new QWidget(Cansat_GUI);
        centralwidget->setObjectName("centralwidget");
        graph1 = new QCustomPlot(centralwidget);
        graph1->setObjectName("graph1");
        graph1->setGeometry(QRect(30, 60, 301, 241));
        graph2 = new QCustomPlot(centralwidget);
        graph2->setObjectName("graph2");
        graph2->setGeometry(QRect(360, 60, 301, 241));
        graph3 = new QCustomPlot(centralwidget);
        graph3->setObjectName("graph3");
        graph3->setGeometry(QRect(690, 60, 301, 241));
        graph4 = new QCustomPlot(centralwidget);
        graph4->setObjectName("graph4");
        graph4->setGeometry(QRect(1020, 60, 301, 241));
        graph5 = new QCustomPlot(centralwidget);
        graph5->setObjectName("graph5");
        graph5->setGeometry(QRect(30, 310, 301, 241));
        graph6 = new QCustomPlot(centralwidget);
        graph6->setObjectName("graph6");
        graph6->setGeometry(QRect(360, 310, 301, 241));
        graph7 = new QCustomPlot(centralwidget);
        graph7->setObjectName("graph7");
        graph7->setGeometry(QRect(690, 310, 301, 241));
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(20, 560, 1321, 91));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(200, 20, 75, 24));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(360, 20, 75, 24));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(80, 20, 113, 22));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 61, 16));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(1100, 10, 113, 22));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1040, 10, 61, 16));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(1220, 10, 61, 24));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(1290, 10, 61, 24));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(440, 20, 75, 24));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(520, 20, 81, 24));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(280, 20, 75, 24));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(610, 20, 75, 24));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(690, 10, 71, 16));
        label_3->setMinimumSize(QSize(71, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(690, 30, 101, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(800, 10, 81, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(800, 30, 241, 16));
        graph8 = new QCustomPlot(centralwidget);
        graph8->setObjectName("graph8");
        graph8->setGeometry(QRect(1020, 310, 301, 241));
        Cansat_GUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Cansat_GUI);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1361, 22));
        menu2025_CanSat_GUI = new QMenu(menubar);
        menu2025_CanSat_GUI->setObjectName("menu2025_CanSat_GUI");
        menufd = new QMenu(menubar);
        menufd->setObjectName("menufd");
        Cansat_GUI->setMenuBar(menubar);
        statusbar = new QStatusBar(Cansat_GUI);
        statusbar->setObjectName("statusbar");
        Cansat_GUI->setStatusBar(statusbar);
        QWidget::setTabOrder(pushButton, lineEdit);
        QWidget::setTabOrder(lineEdit, pushButton_2);
        QWidget::setTabOrder(pushButton_2, plainTextEdit);
        QWidget::setTabOrder(plainTextEdit, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, pushButton_3);
        QWidget::setTabOrder(pushButton_3, pushButton_4);
        QWidget::setTabOrder(pushButton_4, pushButton_5);
        QWidget::setTabOrder(pushButton_5, pushButton_6);
        QWidget::setTabOrder(pushButton_6, pushButton_7);
        QWidget::setTabOrder(pushButton_7, pushButton_8);

        menubar->addAction(menu2025_CanSat_GUI->menuAction());
        menubar->addAction(menufd->menuAction());

        retranslateUi(Cansat_GUI);

        QMetaObject::connectSlotsByName(Cansat_GUI);
    } // setupUi

    void retranslateUi(QMainWindow *Cansat_GUI)
    {
        Cansat_GUI->setWindowTitle(QCoreApplication::translate("Cansat_GUI", "Cansat_GUI", nullptr));
        pushButton->setText(QCoreApplication::translate("Cansat_GUI", "Connect", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Cansat_GUI", "SIM", nullptr));
        label->setText(QCoreApplication::translate("Cansat_GUI", "Serial Port:", nullptr));
        label_2->setText(QCoreApplication::translate("Cansat_GUI", "Load CSV:", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Cansat_GUI", "Save Data", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Cansat_GUI", "Load Data", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Cansat_GUI", "CAL", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Cansat_GUI", "MEC", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Cansat_GUI", "CX ON", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Cansat_GUI", "Set Time", nullptr));
        label_3->setText(QCoreApplication::translate("Cansat_GUI", "GPS Sats: 0", nullptr));
        label_4->setText(QCoreApplication::translate("Cansat_GUI", "Packet Count: 100", nullptr));
        label_5->setText(QCoreApplication::translate("Cansat_GUI", "Voltage: 8.7 V", nullptr));
        label_6->setText(QCoreApplication::translate("Cansat_GUI", "GPS Latitude and Longitude: 49.7532,-57.5374", nullptr));
        menu2025_CanSat_GUI->setTitle(QCoreApplication::translate("Cansat_GUI", "2025 CanSat GUI", nullptr));
        menufd->setTitle(QCoreApplication::translate("Cansat_GUI", "Falling with Style", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Cansat_GUI: public Ui_Cansat_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANSAT_GUI_H
