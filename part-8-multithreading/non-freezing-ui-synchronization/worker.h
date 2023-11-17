#ifndef WORKER_H
#define WORKER_H

#include <QDebug>
#include <QObject>
#include <QReadWriteLock>
#include <QWriteLocker>

class Worker : public QObject
{
    Q_OBJECT
  public:
    explicit Worker(QReadWriteLock* _lock, QObject* parent = nullptr) : QObject(parent), lock(_lock) {}

  public slots:
    void heavyCalculations()
    {
        qDebug() << "Starting...";

        int _result;
        for (int i = 0; i < ITERATIONS; i++)
        {
            _result = i * i;

            if (0 == i % 10000)
            {
                qDebug() << "Iteration" << i;
                QWriteLocker _locker(lock);
                stringProgress = QString::number(static_cast<double>(i + 1) / (ITERATIONS));
                emit progress(&stringProgress);
            }
        }

        qDebug() << "Finished!";
        emit finished();

        emit result(_result);
    }

  signals:
    void progress(QString* stringProgress);
    void finished();
    void result(int result);

  private:
    QReadWriteLock* lock;
    QString stringProgress;
    static constexpr int ITERATIONS = 500000001;
};

#endif   // WORKER_H
