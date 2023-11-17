#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "worker.h"
#include <QObject>
#include <QThread>

class Controller : public QObject
{
    Q_OBJECT
  public:
    explicit Controller(QObject* parent = nullptr) : QObject(parent)
    {
        Worker* worker = new Worker;
        worker->moveToThread(&workerThread);

        makeConnections(worker);

        workerThread.start();
    }

    ~Controller() override
    {
        workerThread.quit();
        workerThread.wait();
    }

  signals:
    void result(int result);
    void finished();
    void progress(double value);
    void heavyCalculations();

  private:
    QThread workerThread;

    void makeConnections(const Worker* const _worker) const
    {
        connect(&workerThread, &QThread::finished, _worker, &QObject::deleteLater, Qt::ConnectionType::DirectConnection);

        connect(this, &Controller::heavyCalculations, _worker, &Worker::heavyCalculations, Qt::ConnectionType::QueuedConnection);
        connect(_worker, &Worker::progress, this, &Controller::progress, Qt::ConnectionType::QueuedConnection);
        connect(_worker, &Worker::result, this, &Controller::result, Qt::ConnectionType::QueuedConnection);
        connect(_worker, &Worker::finished, this, &Controller::finished, Qt::ConnectionType::QueuedConnection);
    }
};

#endif   // CONTROLLER_H
