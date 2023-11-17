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
 * Część: czwarta
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    connect(this->discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(captureDeviceProperties(QBluetoothDeviceInfo)));

    connect(this->discoveryAgent, SIGNAL(finished()), this, SLOT(searchingFinished()));

    this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);

    connect(this->socket, SIGNAL(connected()), this, SLOT(connectionEstablished()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(connectionInterrupted()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(socketReadyToRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::captureDeviceProperties(const QBluetoothDeviceInfo& device)
{
    ui->comboBoxDevices->addItem(device.name() + " " + device.address().toString());

    this->addToLogs("Znaleziono urządzenie o nazwie: " + device.name() + " i adresie: " + device.address().toString());
}

void MainWindow::searchingFinished()
{
    ui->pushButtonSearch->setEnabled(true);

    this->addToLogs("Wyszukiwanie zakończone.");
}

void MainWindow::on_pushButtonSearch_clicked()
{
    this->addToLogs("Rozpoczynam wyszukiwanie.");

    ui->comboBoxDevices->clear();
    ui->pushButtonSearch->setEnabled(false);
    this->discoveryAgent->start();   // rozpoczęcie wyszukiwania
}

void MainWindow::on_pushButtonConnect_clicked()
{
    QString comboBoxQString = ui->comboBoxDevices->currentText();
    QStringList portList = comboBoxQString.split(" ");
    QString deviceAddres = portList.last();

    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));

    // qDebug() << "Service UUID" << serviceUuid << "QBluetoothUuid" << QBluetoothUuid(serviceUuid);

    this->socket->connectToService(QBluetoothAddress(deviceAddres), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);

    this->addToLogs("Rozpoczęto łączenie z urządzeniem o nazwie: " + portList.first() + " i adresie: " + deviceAddres);
}

void MainWindow::on_pushButtonCloseConnection_clicked()
{
    this->addToLogs("Zamykam połączenie.");
    this->socket->disconnectFromService();
}

void MainWindow::on_pushButtonLedOn_clicked()
{
    this->addToLogs("Włączam diodę.");

    this->sendMessageToDevice("1");
}

void MainWindow::on_pushButtonLedOff_clicked()
{
    this->addToLogs("Wyłączam diodę.");

    this->sendMessageToDevice("0");
}

void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEditLogs->append(currentDateTime + "\t" + message);
}

void MainWindow::connectionEstablished()
{
    this->addToLogs("Połączenie ustanowione.");
}

void MainWindow::connectionInterrupted()
{
    this->addToLogs("Połączenie przerwane.");
}

void MainWindow::socketReadyToRead()
{
    while (this->socket->canReadLine())
    {
        QString line = this->socket->readLine();
        // qDebug() << line;

        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        // qDebug() << line.left(pos);

        this->addToLogs(line.left(pos));
    }
}

void MainWindow::sendMessageToDevice(QString message)
{
    if (this->socket->isOpen() && this->socket->isWritable())
    {
        this->addToLogs("Wysyłam informacje do urządzenia " + message);
        this->socket->write(message.toStdString().c_str());
    }
    else
    {
        this->addToLogs("Nie mogę wysłać wiadomości. Połączenie nie zostało ustanowione!");
    }
}
