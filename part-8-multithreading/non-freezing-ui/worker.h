#ifndef WORKER_H
#define WORKER_H

#include <QDebug>
#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
  public:
    explicit Worker(QObject* parent = nullptr) : QObject(parent) {}

  public slots:
    void heavyCalculations()
    {
        qDebug() << "Starting...";

        int _result;
        for (int i = 0; i < ITERATIONS; i++)
        {
            _result = i * i;

            if (0 == i % 100000)
            {
                qDebug() << "Iteration" << i;
                emit progress(static_cast<double>(i + 1) / (ITERATIONS));
            }
        }

        qDebug() << "Finished!";
        emit finished();

        emit result(_result);
    }

  signals:
    void progress(double value);
    void finished();
    void result(int result);

  private:
    static constexpr int ITERATIONS = 500000001;
};

#endif   // WORKER_H
