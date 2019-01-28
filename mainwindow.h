#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QSerialPort>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void DiscoverDevices();
public slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

public:
    QSerialPort *m_serialPort;
    QByteArray  m_readData;
    QTimer      m_timer;
    struct PMS7003
    {
        unsigned int PM1;
        unsigned int PM2_5;
        unsigned int PM10;
        unsigned int PM1atm;
        unsigned int PM2_5atm;
        unsigned int PM10atm;
        unsigned int PCNT_0_3;
        unsigned int PCNT_0_5;
        unsigned int PCNT_1_0;
        unsigned int PCNT_2_5;
        unsigned int PCNT_5_0;
        unsigned int PCNT_10_0;
    }PMS7003;

private slots:
    void on_Refresh_released();
    void on_StartStop_released();
};

#endif // MAINWINDOW_H
