#ifndef PMS7003_H
#define PMS7003_H

#include <QObject>
#include <QSerialPort>

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

    void getData();
    void getData(char *Bytes);
    void processBytes(char *Bytes);

signals:

public slots:



};

#endif // PMS7003_H
