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
#include <QString>
#include <QDateTime>
#include <QGraphicsScene>
QSerialPort serialPort;


QVector<double> xx(101), yy(101); // initialize with entries 0..100
QVector<QCPGraphData> timeData(101);

unsigned int i=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PM_1->setPalette(Qt::blue);
    ui->PM_2_5->setPalette(Qt::blue);
    ui->PM_10->setPalette(Qt::blue);
    ui->PM_1atm->setPalette(Qt::darkBlue);
    ui->PM_2_5atm->setPalette(Qt::darkBlue);
    ui->PM_10atm->setPalette(Qt::darkBlue);
    ui->PCNT_0_3text->setText(tr("Particles beyond 0,3um:"));
    ui->PCNT_0_5text->setText(tr("Particles beyond 0,5um:"));
    ui->PCNT_1_0text->setText(tr("Particles beyond 1um:"));
    ui->PCNT_2_5text->setText(tr("Particles beyond 2,5um:"));
    ui->PCNT_5_0text->setText(tr("Particles beyond 5um:"));
    ui->PCNT_10_0text->setText(tr("Particles beyond 10um:"));

    DiscoverDevices();
    int8_t a=0b10011100;
    int8_t b=0b00011100;
    qDebug() << ("a=")<<a;
    qDebug() << ("b=")<<b;
    qDebug() << ("a1=")<<int(a);
    qDebug() << ("b1=")<<int(b);
    qDebug() << ("a1=")<<uint8_t(a);
    qDebug() << ("b1=")<<uint8_t(b);
    ui->PCNT_0_3value->setText("0");
    ui->PCNT_0_5value->setText("0");
    ui->PCNT_1_0value->setText("0");
    ui->PCNT_2_5value->setText("0");
    ui->PCNT_5_0value->setText("0");
    ui->PCNT_10_0value->setText("0");
        ui->customPlot->addGraph();

        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
        dateTicker->setDateTimeFormat("hh:mm dd.MM.yyyy");
       ui->customPlot->xAxis->setTicker(dateTicker);
       ui->customPlot->xAxis->setTickLabelRotation(90);

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

void MainWindow::DiscoverDevices()
{
    ui->PortSelection->clear();
    int i=0;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->PortSelection->insertItem(i,info.portName());
        i++;
    }
}

void MainWindow::handleReadyRead()
{
    char dat[200];
    int dataindex=0;



    if(serialPort.bytesAvailable()<32)
        return;
    qDebug() << ("d2322323345:");
    qDebug() << ("readdata:") << serialPort.read(dat,50);
    qDebug() << ("dat:") << int(dat[0]);
    qDebug() << ("dat1:") << int(dat[1]);
    qDebug() << ("dat2:") << int(dat[2]);
    qDebug() << ("dat3:") << int(dat[3]);
    qDebug() << ("dat4:") << int(dat[4]);

   // while(dataindex<50)
   // {
   //     if(dat[dataindex]==0x42)
  //  }
      if(dat[0]!=0x42||dat[1]!=0x4d)
      {
          qDebug() << ("ERRRRRRORRRRRR");

      }

    PMS7003.PM1=uint8_t(dat[4])<<8|uint8_t(dat[5]);
    PMS7003.PM2_5=uint8_t(dat[6])<<8|uint8_t(dat[7]);
    PMS7003.PM10=uint8_t(dat[8])<<8|uint8_t(dat[9]);

    PMS7003.PM1atm=uint8_t(dat[10])<<8|uint8_t(dat[11]);
    PMS7003.PM2_5atm=uint8_t(dat[12])<<8|uint8_t(dat[13]);
    PMS7003.PM10atm=uint8_t(dat[14])<<8|uint8_t(dat[15]);

    PMS7003.PCNT_0_3=uint8_t(dat[16])<<8|uint8_t(dat[17]);
    PMS7003.PCNT_0_5=uint8_t(dat[18])<<8|uint8_t(dat[19]);
    PMS7003.PCNT_1_0=uint8_t(dat[20])<<8|uint8_t(dat[21]);
    PMS7003.PCNT_2_5=uint8_t(dat[22])<<8|uint8_t(dat[23]);
    PMS7003.PCNT_5_0=uint8_t(dat[24])<<8|uint8_t(dat[25]);
    PMS7003.PCNT_10_0=uint8_t(dat[26])<<8|uint8_t(dat[27]);


    unsigned int crc=PMS7003.PCNT_5_0=uint8_t(dat[30])<<8|uint8_t(dat[31]);
    unsigned int crc2=0;
    qDebug() << ("crc") << crc;
    for (dataindex=0;dataindex<30;dataindex++)
    {
        crc2=crc2+uint8_t(dat[dataindex]);
    }
    qDebug() << ("crc2") << crc2;

    qDebug() << ("PM1atm:") << int(PMS7003.PM1atm);
    qDebug() << ("PM23atm:") << int(PMS7003.PM2_5atm);
    qDebug() << ("PM10atm:") << int(PMS7003.PM10atm);
    qDebug() << ("PCNT_0_3:") << int(PMS7003.PCNT_0_3);
    qDebug() << ("PCNT_0_5:") << int(PMS7003.PCNT_0_5);
    qDebug() << ("PCNT_1_0:") << int(PMS7003.PCNT_1_0);
    qDebug() << ("PCNT_2_5") << int(PMS7003.PCNT_2_5);
    qDebug() << ("PCNT_5_0:") << int(PMS7003.PCNT_5_0);
    qDebug() << ("PCNT_10_0:") << int(PMS7003.PCNT_10_0);

    ui->PCNT_0_3value->setText(QString::number(PMS7003.PCNT_0_3));
    ui->PCNT_0_5value->setText(QString::number(PMS7003.PCNT_0_5));
    ui->PCNT_1_0value->setText(QString::number(PMS7003.PCNT_1_0));
    ui->PCNT_2_5value->setText(QString::number(PMS7003.PCNT_2_5));
    ui->PCNT_5_0value->setText(QString::number(PMS7003.PCNT_5_0));
    ui->PCNT_10_0value->setText(QString::number(PMS7003.PCNT_10_0));


    ui->PM_1->display(int(PMS7003.PM1));
    ui->PM_2_5->display(int(PMS7003.PM2_5));
    ui->PM_10->display(int(PMS7003.PM10));
    ui->PM_1atm->display(int(PMS7003.PM1atm));
    ui->PM_2_5atm->display(int(PMS7003.PM2_5atm));
    ui->PM_10atm->display(int(PMS7003.PM10atm));


    if (!m_timer.isActive())
        m_timer.start(5000);
    qDebug() << ("mtimet:") << m_timer.remainingTime();
i++;
//QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy");
    timeData[i].key=QDateTime::currentDateTime().toTime_t();
    timeData[i].value=PMS7003.PM1;
   // xx[i] = QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy");; // x goes from -1 to 1
   // yy[i] = PMS7003.PM1; // let's plot a quadratic function
    // create graph and assign data to it:

   ui-> customPlot->graph()->data()->set(timeData);
    // give the axes some labels:
   ui-> customPlot->xAxis->setLabel("x");
   ui-> customPlot->yAxis->setLabel("PM 1");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(timeData[1].key, timeData[1].key+24*3600);
    ui->customPlot->yAxis->setRange(0, 150);
   ui-> customPlot->replot();
   if (i>99)
       i=0;

   QPixmap pixMap = ui->customPlot->grab();
 qDebug() << ("pixMap=")<<  pixMap.save("baba.png");

}



void MainWindow::on_Refresh_released()
{
    DiscoverDevices();
}

void MainWindow::on_StartStop_released()
{
    qDebug() << ui->PortSelection->currentText();
    serialPort.setPortName(ui->PortSelection->currentText());
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

void MainWindow::on_pushButton_released()
{
    QString directory = QFileDialog::getSaveFileName(this,
                               tr("Find Files"), QDir::currentPath());
    ui->savePath->setText(directory);
}
