#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QString>
#include <QDateTime>
#include <QGraphicsScene>
#include <algorithm>
#include <QByteArray>
#include <QObject>

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
    void setTimers(void);

    bool running=false;
    bool DataStable=false;
public slots:
    void handleTimeout();
public:
    QSerialPort *m_serialPort;
    QByteArray  m_readData;
    QTimer      m_timer;
    QTimer      wait_timer;


private slots:
    void on_Refresh_released();
    void on_StartStop_released();
    void on_browseButton_released();
    void on_SaveFilesCheckbox_toggled(bool checked);
};

#endif // MAINWINDOW_H
