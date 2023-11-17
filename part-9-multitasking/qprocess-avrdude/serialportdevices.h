#ifndef SERIALPORTDEVICES_H
#define SERIALPORTDEVICES_H

#include <QObject>
#include <QSerialPortInfo>

class SerialPortDevices : public QObject
{
    Q_OBJECT

  public:
    SerialPortDevices() = default;

  public slots:
    QStringList searchAndGetConnectedDevices()
    {
        QStringList _devicesNames;
        for (const auto& _device : QSerialPortInfo::availablePorts())
        {
            _devicesNames << _device.portName();
        }

        return _devicesNames;
    }
};

#endif   // SERIALPORTDEVICES_H
