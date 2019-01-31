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
#include <algorithm>

#include "pms7003.h"

QSerialPort serialPort;
PMS7003 sensor;
QVector<QCPGraphData> timeData0(1);
QVector<QCPGraphData> timeData1(1);
QVector<QCPGraphData> timeData2(1);
QVector<QCPGraphData> timeDataappend(1);

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
    ui->PCNT_0_3value->setText("0");
    ui->PCNT_0_5value->setText("0");
    ui->PCNT_1_0value->setText("0");
    ui->PCNT_2_5value->setText("0");
    ui->PCNT_5_0value->setText("0");
    ui->PCNT_10_0value->setText("0");
    ui->AddDateCheckbox->setText(tr("Add date to file name"));
    ui->SaveFilesCheckbox->setText(tr("Save files"));
    ui->SavePictureCheckbox->setText(tr("Save plot"));

    ui->AddDateCheckbox->setChecked(TRUE);
    ui->SaveFilesCheckbox->setChecked(TRUE);
    ui->SavePictureCheckbox->setChecked(TRUE);
    ui->PM_1Label->setText(tr("PM 1"));
    ui->PM_2_5Label->setText(tr("PM 2.5"));
    ui->PM_10Label->setText(tr("PM 10"));
    ui->PM_1atmLabel->setText(tr("PM 1"));
    ui->PM_2_5atmLabel->setText(tr("PM 2.5"));
    ui->PM_10atmLabel->setText(tr("PM 10"));
    ui->browseButton->setText(tr("browse"));
    ui->Refresh->setText(tr("refresh"));
    ui->StartStop->setText(tr("Start"));
    ui->factorylabel->setText(tr("Factory environment"));
    ui->atmosfericlabel->setText(tr("Standard environment"));
    ui->TimeIntervalLabel->setText(tr("get data every:"));
    ui->PortSelectionLabel->setText(tr("select port:"));

    ui->savePath->setText(QDir::currentPath().append("/PMS7003"));

    ui->TimeIntervalcomboBox->insertItem(0,tr("always"));
    ui->TimeIntervalcomboBox->insertItem(1,tr("every 15min"));
    ui->TimeIntervalcomboBox->insertItem(2,tr("every 30min"));
    ui->TimeIntervalcomboBox->insertItem(3,tr("every hour"));

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->graph(0)->setName(tr("PM 1"));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->customPlot->graph(1)->setName(tr("PM 2.5"));
    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setPen(QPen(Qt::green)); // line color red for second graph
    ui->customPlot->graph(2)->setName(tr("PM 10"));
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm dd.MM.yyyy");
    ui->customPlot->xAxis->setTicker(dateTicker);
    ui->customPlot->xAxis->setTickLabelRotation(90);
    ui-> customPlot->xAxis->setLabel(tr("time"));
    ui-> customPlot->yAxis->setLabel(tr("PM"));
    ui->customPlot->yAxis->setRange(0, 300);

    DiscoverDevices();
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
    char dat[65];

    if(serialPort.bytesAvailable()<32)
    {
        return;
    }
    serialPort.read(dat,65);

    if(dat[0]!=0x42||dat[1]!=0x4d)
    {
       qDebug() << ("ERRRRRRORRRRRR");
       return;
    }

    sensor.processBytes(dat);

    ui->PCNT_0_3value->setText(QString::number(sensor.PCNT_0_3));
    ui->PCNT_0_5value->setText(QString::number(sensor.PCNT_0_5));
    ui->PCNT_1_0value->setText(QString::number(sensor.PCNT_1_0));
    ui->PCNT_2_5value->setText(QString::number(sensor.PCNT_2_5));
    ui->PCNT_5_0value->setText(QString::number(sensor.PCNT_5_0));
    ui->PCNT_10_0value->setText(QString::number(sensor.PCNT_10_0));
    ui->PM_1->display(int(sensor.PM1));
    ui->PM_2_5->display(int(sensor.PM2_5));
    ui->PM_10->display(int(sensor.PM10));
    ui->PM_1atm->display(int(sensor.PM1atm));
    ui->PM_2_5atm->display(int(sensor.PM2_5atm));
    ui->PM_10atm->display(int(sensor.PM10atm));


    if (!m_timer.isActive())
        m_timer.start(5000);
    qDebug() << ("mtimet:") << m_timer.remainingTime();


    timeData0.append(timeDataappend);//append data so never overflows
    timeData1.append(timeDataappend);
    timeData2.append(timeDataappend);
    timeData0[i].key=QDateTime::currentDateTime().toTime_t();
    timeData1[i].key=QDateTime::currentDateTime().toTime_t();
    timeData2[i].key=QDateTime::currentDateTime().toTime_t();

    timeData0[i].value=sensor.PM1;
    ui-> customPlot->graph(0)->data()->set(timeData0);
    timeData1[i].value=sensor.PM2_5;
    ui-> customPlot->graph(1)->data()->set(timeData1);
    timeData2[i].value=sensor.PM10;
    ui-> customPlot->graph(2)->data()->set(timeData2);
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(timeData0[0].key, timeData0[0].key+24);
    ui->customPlot->yAxis->setRange(0, 150);
    ui-> customPlot->replot();
    i++;

    //abort if no need for saving files
    if (ui->SaveFilesCheckbox->isChecked()==FALSE)
    {
        return;
    }
     QFile file(ui->savePath->text().append(".csv"));
     if (file.open(QIODevice::WriteOnly | QIODevice::Append))
     {
           QTextStream stream(&file);
           stream << QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy") << "," <<
                     sensor.PM1<<","  <<
                     sensor.PM2_5<<","  <<
                     sensor.PM10<<endl;
     }
     file.close();
     if (ui->SavePictureCheckbox->isChecked()==FALSE)
     {
         return;
     }
     QPixmap pixMap = ui->customPlot->grab();
     if(pixMap.save(ui->savePath->text().append(".png"))!=TRUE)
     {
         QMessageBox::critical(0, qApp->tr("Error"),
             qApp->tr("Could not save plot"));
     }
}



void MainWindow::on_Refresh_released()
{
    DiscoverDevices();
}

void MainWindow::on_StartStop_released()
{
    if(working==false)
    {
        working=true;
        ui->StartStop->setText(tr("stop"));
        serialPort.setPortName(ui->PortSelection->currentText());
        serialPort.setBaudRate(QSerialPort::Baud9600);
        if (!serialPort.open(QIODevice::ReadOnly))
        {
           QMessageBox::critical(0, qApp->tr("Error"),
              qApp->tr("Failed, error: %2").arg(serialPort.errorString()));
        }
        connect(&serialPort, &QSerialPort::readyRead, this, &MainWindow::handleReadyRead);
        connect(&serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);

        QTimer *m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &MainWindow::handleTimeout);
        m_timer->start(5000);


        ui->AddDateCheckbox->setEnabled(FALSE);
        ui->SaveFilesCheckbox->setEnabled(FALSE);
        ui->SavePictureCheckbox->setEnabled(FALSE);
        //abort if no need for saving files
        if (ui->SaveFilesCheckbox->isChecked()==FALSE)
        {
            return;
        }
        if(ui->AddDateCheckbox->isChecked())
        {
            ui->savePath->setText(ui->savePath->text().append(QDateTime::currentDateTime().toString("mmhhddMMyy")));
        }
        QFile file(ui->savePath->text().append(".csv"));
        if ( file.open(QIODevice::WriteOnly) )
        {
             QTextStream stream( &file );
             stream << tr("Date and time")<<","  <<
                       tr("PM 1") <<","  <<
                       tr("PM 2.5") <<","  <<
                       tr("PM 10") << endl;
        }
        file.close();
        ui->savePath->setEnabled(FALSE);
    }
    else
    {
        serialPort.close();
        working=false;
        disconnect(&serialPort, &QSerialPort::readyRead, this, &MainWindow::handleReadyRead);
        disconnect(&serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                    this, &MainWindow::handleError);
        ui->StartStop->setText(tr("start"));
        ui->AddDateCheckbox->setEnabled(TRUE);
        ui->SaveFilesCheckbox->setEnabled(TRUE);
        ui->SavePictureCheckbox->setEnabled(TRUE);

        timeData0.clear();
        timeData1.clear();
        timeData2.clear();
        i=0;
    }
}

void MainWindow::on_browseButton_released()
{
    QString directory = QFileDialog::getSaveFileName(this,
                               tr("Find Files"), QDir::currentPath(),
                               "Images and Text files (*.png *.csv)");

    if(directory.lastIndexOf(QChar('.'))>directory.length()-5)
    {
        directory= directory.left(directory.lastIndexOf(QChar('.')));
    }
    ui->savePath->setText(directory);
}

void MainWindow::on_SaveFilesCheckbox_toggled(bool checked)
{
    if(ui->SaveFilesCheckbox->isChecked())
    {
        ui->AddDateCheckbox->setEnabled(TRUE);
        ui->SavePictureCheckbox->setEnabled(TRUE);
        ui->savePath->setEnabled(TRUE);
        ui->browseButton->setEnabled(TRUE);
    }
    else
    {
        ui->AddDateCheckbox->setEnabled(FALSE);
        ui->SavePictureCheckbox->setEnabled(FALSE);
        ui->savePath->setEnabled(FALSE);
        ui->browseButton->setEnabled(FALSE);
    }
}
