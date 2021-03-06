#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QObject>
#include <QLabel>
#include <QString>
#include <QGraphicsScene>
#include "constants.h"
class QGraphicsItem;
class QTimer;

extern int x_pos_of_ball;
extern int y_pos_of_ball;
#define BLOCK_SIZE 8

class Gameplay : public QObject
{
    Q_OBJECT // bu macro meta-obje içeren tüm classlarda bulunmalı,q

public:
    explicit Gameplay(QGraphicsScene & scene, QGraphicsRectItem *p1, QGraphicsRectItem *p2, QGraphicsItem *ball,
                         int gameMode, QGraphicsItem *token,QObject *parent, QGraphicsItem *ball2,
                         QGraphicsPixmapItem *mainarea,QGraphicsPixmapItem *goalarea);
protected:
    virtual bool eventFilter(QObject *, QEvent *);

signals:
    void goal(int player);
    void stopGame(int time);

private slots:
    void pong_tick();
    void arkanoid_tick();
    void pauseGame(int time);
        void breakLoop();
private:
    void check_pong_winner(int player);
    void check_arkanoid_winner();
    void check_blocks();
    void set_pong();
    void set_arkanoid();
    void update_block_coordinates();
    qreal calculateP2Direction(int client_data);
    qreal calculateP1Direction(int client_data);
    int data = 5;
    int control = 0;
    int p1Score = 0;
    int p2Score = 0;
    int block_count = 0;
    bool game_over = false;
    int flagStop = 0;
private:
    QGraphicsScene & iScene;
    QGraphicsItem  *iBall, *iToken, *iBall_2;
    QGraphicsRectItem *left_side;
    QGraphicsRectItem *blocks[8], *iP1 , *iP2;
    QString str_block_coordinates;
    std::string cpp_string;
    bool block_state[8];
    bool side_state = true;
    void setBlocks();
    void detectCollusion();
    void detectSideCollusion();
    int defaultP2Size=60;
    QTimer *iTimer;
    qreal orgin1=30;
    qreal orgin2=30;
    QPointF iBallDirection;
    QPointF iBall2Direction;
    QPointF iTokenDirection;
    qreal iP1Direction;
    qreal iP2Direction;
    int g_mode;
    int gyro1;
    int gyro2;
    QGraphicsPixmapItem *mainArea;
    QGraphicsPixmapItem *goalArea;
    QTimer *gTimer;
};

#endif // GAMEPLAY_H
