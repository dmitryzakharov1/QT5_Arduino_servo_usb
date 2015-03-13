#include "mainwindow.h"
#include "ui_mainwindow.h"

int servo1pos;
QString gstr;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(writeData()));

    servo1pos = ui->horizontalSlider->value();
    ui->label_3->setText(QString::number(servo1pos));

    //установим границы horizontalSlider
    ui->horizontalSlider->setMinimum(ui->lineEdit_3->text().toInt());
     ui->horizontalSlider->setMaximum(ui->lineEdit_2->text().toInt());

    ui->serialPortInfoListBox->clear();

       foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
           QStringList list;
           list << info.systemLocation();
           ui->serialPortInfoListBox->addItem(list.first(), list);
       }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSerialPort()
{

    serial->setPortName(ui->serialPortInfoListBox->currentText());
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
        qDebug() << "\nPort settings successfully";
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        qDebug() << "\nPort settings failed";

    }
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);

}


void MainWindow::writeData()
{
    serial->write(gstr.toLocal8Bit());
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->label_3->setText(QString::number(position));
    servo1pos = position;
    gstr = QString::number(servo1pos)  + ":";
}
