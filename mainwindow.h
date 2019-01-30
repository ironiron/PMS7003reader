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


private slots:
    void on_Refresh_released();
    void on_StartStop_released();
    void on_browseButton_released();
};

#endif // MAINWINDOW_H
