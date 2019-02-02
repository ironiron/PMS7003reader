#ifndef PMS7003_H
#define PMS7003_H

#include <QObject>
#include <QSerialPort>
#include <QMessageBox>
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
#include <QString>
#include <QDateTime>
#include <QGraphicsScene>
#include <algorithm>

class PMS7003 : public QObject
{
    Q_OBJECT
public:
public:
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
    explicit PMS7003(QObject *parent = 0);
    void setPort(QString serialport);
    void reset(void);
    void setSleepMode(void);
    void wakeUp(void);


    void getData();
    void getData(char *Bytes);
    void processBytes(char *Bytes);

signals:

private slots:
    void handleread(void);
    void handleError(void);
private:
    QSerialPort port;

};

#endif // PMS7003_H
