#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include <server.h>
#include <mainwindow.h>
#include <mythread.h>

Server::Server(QWidget *parent, MainWindow *mWindow, Menu *serverMenu)
    : QDialog(parent)
    , mainWindow(mWindow)
    , menu(serverMenu)
{
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened, this, &Server::sessionOpened);

        networkSession->open();
    } else {
        sessionOpened();
    }
    playerNumber = 1;
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::readWrite);
}

void Server::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    QHostAddress *addr= new QHostAddress(IPADDRESS);
    if (!tcpServer->listen(*addr,PORTNUMBER)) {
        QMessageBox::critical(this, tr("Server"),
                              tr("Unable to start the server From Session: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

}

void Server::readWrite()
{
    MyThread *thread = new MyThread(tcpServer->socketDescriptor(),playerNumber, this, tcpServer);
    playerNumber++;
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

    menu->updateGame(playerNumber - 1);
}
