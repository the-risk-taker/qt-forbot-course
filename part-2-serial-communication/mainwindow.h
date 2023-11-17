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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

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

    void readFromPort();

    void on_pushButtonCloseConnection_clicked();

    void on_pushButtonLedOn_clicked();

    void on_pushButtonLedOff_clicked();

  private:
    Ui::MainWindow* ui;

    void addToLogs(QString message);

    QSerialPort* device;
    void sendMessageToDevice(QString message);
};

#endif   // MAINWINDOW_H
