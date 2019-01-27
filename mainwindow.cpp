#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>

#include <QTextStream>
#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QDebug>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QTimer>
QSerialPort serialPort;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //QSerialPortInfo &info2;
    ui->setupUi(this);

    // Example use QSerialPortInfo
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
    }

   // qDebug() << "info2 " << info2.portName();


    serialPort.setPortName("COM5");
    serialPort.setBaudRate(QSerialPort::Baud9600);

    if (!serialPort.open(QIODevice::ReadOnly)) {
        qDebug() << "errrrr: " << QObject::tr("Failed, error: %2").arg(serialPort.errorString()) << endl;
    }
   qDebug() <<"crc"<< serialPort.currentReadChannel();
   qDebug() <<"io"<< serialPort.isOpen();
   qDebug() <<"ir"<< serialPort.isReadable();
   qDebug() <<"iw"<< serialPort.isWritable();
   qDebug() <<"om"<< serialPort.openMode();
    qDebug() << ("Jestem");
    QTimer *m_timer = new QTimer(this);
    connect(&serialPort, &QSerialPort::readyRead, this, &MainWindow::handleReadyRead);
    connect(&serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);
   qDebug() << connect(m_timer, &QTimer::timeout, this, &MainWindow::handleTimeout);
        m_timer->start(5000);
}


void MainWindow::handleTimeout()
{
    qDebug() << ("d3333333333333332:");
    return;
    if (m_readData.isEmpty()) {
        qDebug()  << QObject::tr("No data was currently available for reading from port %1").arg(m_serialPort->portName()) << endl;
    } else {
        qDebug()  << QObject::tr("Data successfully received from port %1").arg(m_serialPort->portName()) << endl;
        qDebug()  << m_readData << endl;
    }

  //  QCoreApplication::quit();
}

void MainWindow::handleError(QSerialPort::SerialPortError serialPortError)
{
    qDebug() << ("d444444444444444442:");
    if (serialPortError == QSerialPort::ReadError) {
        qDebug() << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
       // QCoreApplication::exit(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleReadyRead()
{
    qDebug() << ("d2222:");
    //return;
    //m_readData.append(serialPort.readAll());
    //qDebug() << ("data received:") << m_readData;
    qDebug() << ("data received2:") << serialPort.readAll();
    if (!m_timer.isActive())
        m_timer.start(5000);
}
