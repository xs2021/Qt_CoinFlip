#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = 0);

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    PlayScene * pScene;

signals:
    //自定义返回信号
    void chooseSceneBack();

public slots:

};

#endif // CHOOSELEVELSCENE_H
