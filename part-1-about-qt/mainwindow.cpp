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
 * Część: pierwsza
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Connect się powiódł?" << connect(ui->pushButtonTest, SIGNAL(clicked()), this, SLOT(myCustomSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonOK_clicked()
{
    qDebug() << "Wcisnąłeś przycisk OK";
}

void MainWindow::myCustomSlot()
{
    qDebug() << "Wcisnales przycisk Test i wykorzystałeś mechanizm sygnałów i slotów";
}
