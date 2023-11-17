#include "rover.h"
#include <QDebug>
#include <QRandomGenerator>

Rover::Rover(QObject* parent) : QObject(parent), isConnected(false), controlLevel(20.0)
{
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Rover::onTimeout);

    timer->setInterval(QRandomGenerator::securelySeeded().bounded(100, 1000));
    timer->start();
}

void Rover::goLeft()
{
    qDebug() << "Jadę w lewo z czułością " << controlLevel;
}

void Rover::goRight()
{
    qDebug() << "Jadę w prawo z czułością " << controlLevel;
}

void Rover::goForward()
{
    qDebug() << "Jadę do przodu z czułością " << controlLevel;
}

void Rover::goBackward()
{
    qDebug() << "Jadę do tyłu z czułością " << controlLevel;
}

void Rover::stop()
{
    qDebug() << "Zatrzymuję się";
}

void Rover::onTimeout()
{
    isConnected = !isConnected;
    emit isConnectedChanged();   // Bardzo ważne jest wywołanie sygnału po zmianie parametru, jeśli informacja ma odświeżyć się w QML

    if (isConnected)
    {
        timer->setInterval(QRandomGenerator::securelySeeded().bounded(5000, 20000));
    }
    else
    {
        timer->setInterval(QRandomGenerator::securelySeeded().bounded(500, 4000));
    }

    qDebug() << (isConnected ? "Connected" : "Disconnected") << "Interval" << timer->interval();
}
