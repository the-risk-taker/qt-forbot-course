#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "worker.h"
#include <QObject>
#include <QReadLocker>
#include <QReadWriteLock>
#include <QThread>

class Controller : public QObject
{
    Q_OBJECT
  public:
    explicit Controller(QReadWriteLock* _lock, QObject* parent = nullptr) : QObject(parent), lock(_lock)
    {
        Worker* worker = new Worker(lock);
        worker->moveToThread(&workerThread);

        makeConnections(worker);

        workerThread.start();
    }

    ~Controller() override
    {
        workerThread.quit();
        workerThread.wait();
    }

  public slots:
    void onProgress(QString* _progress)
    {
        QReadLocker _locker(lock);
        controllerProgress = *_progress;
        emit progress(controllerProgress.toDouble());
    }

  signals:
    void result(int result);
    void finished();
    void progress(double progress);
    void heavyCalculations();

  private:
    QReadWriteLock* lock;
    QThread workerThread;
    QString controllerProgress;

    void makeConnections(const Worker* const _worker) const
    {
        connect(&workerThread, &QThread::finished, _worker, &QObject::deleteLater, Qt::ConnectionType::DirectConnection);

        connect(this, &Controller::heavyCalculations, _worker, &Worker::heavyCalculations, Qt::ConnectionType::QueuedConnection);
        connect(_worker, &Worker::progress, this, &Controller::onProgress, Qt::ConnectionType::QueuedConnection);
        connect(_worker, &Worker::result, this, &Controller::result, Qt::ConnectionType::QueuedConnection);
        connect(_worker, &Worker::finished, this, &Controller::finished, Qt::ConnectionType::QueuedConnection);
    }
};

#endif   // CONTROLLER_H
