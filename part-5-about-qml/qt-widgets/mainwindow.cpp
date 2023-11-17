#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer.setInterval(2000);

    connect(&timer, &QTimer::timeout, this, &MainWindow::onTimeout);

    QPalette pal = ui->pushButton->palette();
    pal.setColor(QPalette::Button, QColor(Qt::black));
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setPalette(pal);
    ui->pushButton->setStyleSheet("color: white");
    ui->pushButton->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Button was clicked";

    timer.start();
}

void MainWindow::onTimeout()
{
    QCoreApplication::quit();
}
