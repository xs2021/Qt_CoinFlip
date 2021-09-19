#include "mycoin.h"
#include <QDebug>
#include <QTimer>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString imgPath)
{
    QPixmap pix;
    bool ret = pix.load(imgPath);
    if(!ret)
    {
        qDebug()<< "图片加载失败！"<<imgPath;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));


    //初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听两个定时器信号
    //金币翻银币信号
    connect(timer1,&QTimer::timeout,[=](){
        //切换图片
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        bool ret = pix.load(str);
        if(!ret)
        {
            qDebug()<< "图片加载失败！"<<imgPath;
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min > this->max)
        {
            this->min = 1; //还原最小值下标
            this->isAnimation = false; //没有在做动画
            timer1->stop();
        }
    });

    //银币翻金币信号
    connect(timer2,&QTimer::timeout,[=](){
        //切换图片
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        bool ret = pix.load(str);
        if(!ret)
        {
            qDebug()<< "图片加载失败！"<<imgPath;
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max < this->min)
        {
            this->max = 8; //还原最大值下标
            this->isAnimation = false; //没有在做动画
            timer2->stop();
        }
    });
}

//改变标志,执行翻转效果
void MyCoin::changeFlag()
{
    if(this->flag)
    {
        //启动金币翻转的定时器
        timer1->start(30);
        this->isAnimation = true; //正在做动画

        this->flag = false; //金币改银币
    }
    else
    {
        //启动银币翻转的定时器
        timer2->start(30);
        this->isAnimation = true;

        this->flag = true; //银币改金币
    }
}

//重写鼠标按下事件(判断是否在做动画 或者 胜利)
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
