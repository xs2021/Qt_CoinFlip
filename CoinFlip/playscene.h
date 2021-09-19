#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = 0);

    PlayScene(int Index);


    //重写绘图事件
    void paintEvent(QPaintEvent *);

    int LeavlIndex; //当前的关卡

    int gameArray[4][4]; //二维数组记录金币银币数据

    MyCoin * coinBtn[4][4]; //金币按钮数组

    bool isWin = true; //是否胜利
signals:
    void chooseSceneBack();

public slots:
};

#endif // PLAYSCENE_H
