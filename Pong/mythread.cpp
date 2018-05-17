// mythread.cpp

#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include "mythread.h"



shared_values MyThread::shared = {0,0,0,0,0,0,0,0,0,0,0};

MyThread::MyThread(int ID, int thread_id, QObject *parent,QTcpServer *server) :
    QThread(parent),
    tcpServer(server)
{
    this->socketDescriptor = ID;
    this->thread_id = thread_id;
    shared.connected_glasses_count++;
    qDebug()<< "Connected glasses: "<<shared.connected_glasses_count;
}

void MyThread::run()
{
    qDebug() << socketDescriptor << " Starting thread";

    socket= tcpServer->nextPendingConnection();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readWrite()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop
    exec();


}

void MyThread::readWrite()
{
    /*
    qDebug()<<"READY READ AND WRITE";
    QByteArray recData = socket->readAll();

    qDebug() << socketDescriptor << " This message receiving from data glass : " << recData;

    QString sendMessage = "1234;56;789;0;12";
    QByteArray sendByte = sendMessage.toUtf8() ;
    socket->write(sendByte);
*/

    QByteArray q_b;

    /*
    QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender()); //silincede calısıyor.
    if (!socket)
        return;
    */

    std::string data = "";
   // while (socket->canReadLine()) {
        data = "";
       QByteArray line =  socket->readAll();


        qDebug() << " This message receiving from data glass : " << this->thread_id << line;

        if (thread_id == 1){
            shared.gyro1 = line.toInt();
            infos.gyro = shared.gyro2;

        }
        if (thread_id == 2){
            shared.gyro2 = line.toInt();
            infos.gyro = shared.gyro1;
        }
        infos.topx = shared.mainBallX / SCREEN_RATIO;
        infos.topy = shared.mainBallY / SCREEN_RATIO;

        if(socket->bytesToWrite()==0 && socket->isWritable()){

            q_b.clear();
            if (infos.gyro <10 )
                data+="0";

            std::string tempp = std::to_string(infos.gyro);
            data+=tempp;

            //topx
            data+=";";

            if(infos.topx <10)
                data+="0";

            tempp = std::to_string(infos.topx);
            data+=tempp;


             //topy

            data+=";";
            if(infos.topy <10)
                data+="00";

            else if(infos.topy <100)
                data+="0";

            tempp = std::to_string(infos.topy);
            data+=tempp;

            //yollama formatına cevir ve yolla
            QString data_to_write = QString::fromStdString(data);
            q_b = data_to_write.toUtf8();
            socket->write(q_b);
            qDebug() << "string:" << data_to_write ;
            qDebug() << "Sent string as bytes:" << q_b ;

            qDebug() <<"Sent top x: "<<infos.topx << " top y: " << infos.topy;


        }



    //}


}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}
//int MyThread::getGyro1()
//{
//    return gyro1;
//}

//void MyThread::setGyro1(int value)
//{
//    gyro1 = value;
//}

//int MyThread::getGyro2()
//{
//    return gyro2;
//}

//void MyThread::setGyro2(int value)
//{
//    gyro2 = value;
//}
//int MyThread::getBallX()
//{
//    return ballX;
//}

//void MyThread::setBallX(int value)
//{
//    ballX = value;
//}

//int MyThread::getBallY()
//{
//    return ballY;
//}

//void MyThread::setBallY(int value)
//{
//    ballY = value;
//}

//void MyThread::setSecondBallX(int x){
//    second_ballX = x;
//}
//int MyThread::getSecondBallX(){
//    return second_ballX;
//}
//void MyThread::setSecondBallY(int y){
//    second_ballY = y;
//}
//int MyThread::getSecondBallY(){
//    return second_ballY;
//}
