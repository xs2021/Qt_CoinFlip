#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushbutton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushbutton(QWidget *parent = 0);

    //重写构造函数
    MyPushbutton(QString normalImg, QString pressImg = "");

    QString m_NormalImg;//默认显示图片路径
    QString m_PressImg; //按下后显示图片路径

    //向下弹起
    void zoom1();
    //向上弹起
    void zoom2();

    //重写按下
    void mousePressEvent(QMouseEvent *e);
    //重写释放
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:

};

#endif // MYPUSHBUTTON_H
