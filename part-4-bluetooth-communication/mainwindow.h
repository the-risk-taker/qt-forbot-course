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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private slots:
    void on_pushButtonSearch_clicked();
    void on_pushButtonConnect_clicked();
    void on_pushButtonCloseConnection_clicked();
    void on_pushButtonLedOn_clicked();
    void on_pushButtonLedOff_clicked();

    void captureDeviceProperties(const QBluetoothDeviceInfo& device);
    void searchingFinished();

    void connectionEstablished();
    void connectionInterrupted();
    void socketReadyToRead();

  private:
    Ui::MainWindow* ui;

    QBluetoothDeviceDiscoveryAgent* discoveryAgent;

    void addToLogs(QString message);

    QBluetoothSocket* socket;

    void sendMessageToDevice(QString message);
};

#endif   // MAINWINDOW_H
