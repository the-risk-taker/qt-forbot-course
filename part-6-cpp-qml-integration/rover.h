#ifndef ROVER_H
#define ROVER_H

#include <QObject>
#include <QTimer>

class Rover : public QObject
{
    Q_OBJECT

  public:
    Q_PROPERTY(double controlLevel READ getControlLevel WRITE setControlLevel NOTIFY controlLevelChanged)
    Q_PROPERTY(double isConnected READ getIsConnected() NOTIFY isConnectedChanged)

    explicit Rover(QObject* parent = nullptr);

  public slots:
    void goLeft();
    void goRight();
    void goForward();
    void goBackward();
    void stop();

    double getControlLevel() const
    {
        return controlLevel;
    }

    void setControlLevel(double _controlLevel)
    {
        controlLevel = _controlLevel;
        emit controlLevelChanged();
    }

    bool getIsConnected() const
    {
        return isConnected;
    }

  signals:
    void controlLevelChanged();
    void isConnectedChanged();

  private:
    bool isConnected;
    double controlLevel;

    QTimer* timer;

    void onTimeout();
};

#endif   // ROVER_H
