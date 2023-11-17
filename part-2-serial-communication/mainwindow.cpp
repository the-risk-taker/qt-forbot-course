/*
 *
 * 2019 © Copyright Mateusz Patyk
 *
 * Autor: Mateusz Patyk
 * Kontakt: matpatyk@gmail.com
 *
 * Seria:
 * Qt - Tworzenie interfejsów aplikacji na urządzenia mobilne i komputery personalne wykorzystujące
 * komunikację poprzez port szeregowy i Bluetooth.
 *
 * Dla: Forbot, https://forbot.pl/blog/
 * Część: druga
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSearch_clicked()
{
    ui->comboBoxDevices->clear();

    this->addToLogs("Szukam urządzeń...");

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();

    for (int i = 0; i < devices.count(); i++)
    {
        this->addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
        ui->comboBoxDevices->addItem(devices.at(i).portName() + "\t" + devices.at(i).description());
    }
}

void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEditLogs->append(currentDateTime + "\t" + message);
}

void MainWindow::sendMessageToDevice(QString message)
{
    if (this->device->isOpen() && this->device->isWritable())
    {
        this->addToLogs("Wysyłam informacje do urządzenia " + message);
        this->device->write(message.toStdString().c_str());
    }
    else
    {
        this->addToLogs("Nie mogę wysłać wiadomości. Port nie jest otwarty!");
    }
}

void MainWindow::on_pushButtonConnect_clicked()
{
    if (ui->comboBoxDevices->count() == 0)
    {
        this->addToLogs("Nie wykryto żadnych urządzeń!");
        return;
    }

    QString comboBoxQString = ui->comboBoxDevices->currentText();
    QStringList portList = comboBoxQString.split("\t");
    QString portName = portList.first();

    this->device->setPortName(portName);

    // OTWÓRZ I SKONFIGURUJ PORT:
    if (!device->isOpen())
    {
        if (device->open(QSerialPort::ReadWrite))
        {
            this->device->setBaudRate(QSerialPort::Baud9600);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);

            // CONNECT:
            connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));

            this->addToLogs("Otwarto port szeregowy.");
        }
        else
        {
            this->addToLogs("Otwarcie porty szeregowego się nie powiodło!");
        }
    }
    else
    {
        this->addToLogs("Port już jest otwarty!");
        return;
    }
}

void MainWindow::readFromPort()
{
    while (this->device->canReadLine())
    {
        QString line = this->device->readLine();
        // qDebug() << line;

        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        // qDebug() << line.left(pos);

        this->addToLogs(line.left(pos));
    }
}

void MainWindow::on_pushButtonCloseConnection_clicked()
{
    if (this->device->isOpen())
    {
        this->device->close();
        this->addToLogs("Zamknięto połączenie.");
    }
    else
    {
        this->addToLogs("Port nie jest otwarty!");
        return;
    }
}

void MainWindow::on_pushButtonLedOn_clicked()
{
    this->sendMessageToDevice("1");
}

void MainWindow::on_pushButtonLedOff_clicked()
{
    this->sendMessageToDevice("0");
}
