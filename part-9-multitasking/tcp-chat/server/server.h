#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT

  public:
    Q_PROPERTY(bool serverStatus READ getServerStatus NOTIFY serverStatusChanged)

    explicit Server(QObject* parent = nullptr) : QObject(parent), client(nullptr), serverStatus(false)
    {
        connect(&server, &QTcpServer::newConnection, this, &Server::onNewConnection);
    }

  public slots:
    inline void writeToClient(const QString& _data)
    {
        if (client)
        {
            client->write(_data.toUtf8());
        }
    }

    inline bool getServerStatus() const
    {
        return serverStatus;
    }

    inline void setServerStatus(bool _value)
    {
        serverStatus = _value;
        emit serverStatusChanged();
    }

    void setupServer(int _port)
    {
        if (!server.listen(QHostAddress::Any, static_cast<quint16>(_port)))
        {
            qDebug() << "Server could not start";
            exit(-1);
        }
        else
        {
            qDebug() << "Server started on address:" << QHostAddress(QHostAddress::Any) << "and port:" << _port;
            setServerStatus(true);
        }
    }

  signals:
    void messageFromClient(const QString& _data);
    void serverStatusChanged();

  private:
    QTcpServer server;
    QTcpSocket* client;
    bool serverStatus;

    inline void writeToServer(const QString& _data)
    {
        client->write(_data.toUtf8());
    }

  private slots:
    void onNewConnection()
    {
        if (client != nullptr)
        {
            client->disconnectFromHost();
        }

        client = server.nextPendingConnection();
        serverStatus = true;

        // QAbstractSocket
        connect(client, &QAbstractSocket::connected, []() { qDebug() << "Connected!"; });
        connect(client, &QAbstractSocket::disconnected, [this]() {
            qDebug() << "Disconnected!";
            client = nullptr;
        });
        connect(client, &QAbstractSocket::disconnected, client, &QObject::deleteLater);   // zwolnienie pamięci!
        connect(client, &QAbstractSocket::hostFound, []() { qDebug() << "Host Found!"; });
        connect(client, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred), [](QAbstractSocket::SocketError _socketError) {
            qDebug() << "Error occurred:" << _socketError;
        });
        connect(client, &QAbstractSocket::stateChanged, [](QAbstractSocket::SocketState _socketState) { qDebug() << "Socket state changed to: " << _socketState; });

        // QIODevice
        connect(client, &QIODevice::readyRead, [&]() { emit messageFromClient(client->readAll()); });

        writeToServer("Hello client!");
    }
};

#endif   // SERVER_H
