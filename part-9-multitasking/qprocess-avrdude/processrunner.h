#ifndef PROCESSRUNNER_H
#define PROCESSRUNNER_H

#include <QDebug>
#include <QProcess>

class ProcessRunner : public QObject
{
    Q_OBJECT

  public:
    ProcessRunner()
    {
        connect(&process, &QProcess::started, this, &ProcessRunner::onStarted);

        connect(&process, &QProcess::errorOccurred, this, &ProcessRunner::onErroroccurred);

        connect(&process, &QProcess::readyReadStandardError, this, &ProcessRunner::onReadAllStandardError);

        connect(&process, &QProcess::readyReadStandardOutput, this, &ProcessRunner::onReadAllStandardOutput);

        connect(&process, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &ProcessRunner::onFinished);

        /*
        connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)),
                this, SLOT(onFinished(int, QProcess::ExitStatus)));

        connect(&process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
                [=]  (int _exitCode, QProcess::ExitStatus _exitStatus)
                {
                    qDebug() << "AVRDUDE finished!" << _exitCode << _exitStatus;
                }
        );
        */
    }

  public slots:
    void run(const QString& _device, const QString& _binary)
    {
        outputString.clear();

        QStringList _args;
#ifdef Q_OS_WINDOWS
        _args << "-CC:/Program Files (x86)/Arduino/hardware/tools/avr/etc/avrdude.conf"
#else
        _args
#endif
              << "-patmega328p"
              << "-carduino"
#ifdef Q_OS_LINUX
              << "-P/dev/" + _device
#endif
#ifdef Q_OS_WINDOWS
              << "-P" + _device
#endif
              << "-b115200"
              << "-D"
              << "-Uflash:w:" + _binary + ":i";

        process.setArguments(_args);
#ifdef Q_OS_WINDOWS
        process.setProgram("C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avrdude.exe");
#endif
#ifdef Q_OS_LINUX
        process.setProgram("avrdude");
#endif

        process.setProcessChannelMode(QProcess::MergedChannels);

        process.start();
        //        process.startDetached();
    }

  signals:
    void output(const QString& _output);

  private:
    QString outputString;
    QProcess process;

    void appendToOutputStringAndEmit(const QString& _data)
    {
        outputString += _data;
        emit output(outputString);
    }

  private slots:
    void onStarted()   // mogę te informacje wykorzystać do innych celów
    {
        qDebug() << "AVRDUDE started!";
    }

    void onFinished(int _exitCode, QProcess::ExitStatus _exitStatus)   // tę również
    {
        qDebug() << "AVRDUDE finished!" << _exitCode << _exitStatus;
    }

    void onErroroccurred(QProcess::ProcessError _error)
    {
        qDebug() << _error << process.errorString();   // i tę tak samo
    }

    void onReadAllStandardError()
    {
        appendToOutputStringAndEmit(process.readAllStandardError());
    }

    void onReadAllStandardOutput()
    {
        appendToOutputStringAndEmit(process.readAllStandardOutput());
    }
};

#endif   // PROCESSRUNNER_H
