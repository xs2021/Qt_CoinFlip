#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QPushButton>

//MyPushbutton::MyPushbutton(QPushButton *parent) :
//    QWidget(parent)
//{
//}

MyPushbutton::MyPushbutton(QString normalImg, QString pressImg)
//     :m_NormalImg(normalImg),m_PressImg(pressImg)
{
    //成员变量normalImgPath保存正常显示图片路径
    m_NormalImg = normalImg;
    //成员变量pressedImgPath保存按下后显示的图片
    m_PressImg = pressImg;

    //创建QPixmap对象
    QPixmap pix;
    //判断是否能够加载正常显示的图片，若不能提示加载失败
    bool ret = pix.load(m_NormalImg);
    if(!ret)
    {
        QString str = QString("图片加载失败 %1").arg(normalImg);
        qDebug()<< str;
        return;
    }

    //设置图片的固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片的样式表(设置边框透明)
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

//向下弹起
void  MyPushbutton::zoom1()
{
    //创建动画对象(并没有放到对象树)
    QPropertyAnimation  * animation = new QPropertyAnimation(this,"geometry");

    //设置时间间隔，单位毫秒
    animation->setDuration(200);
    //创建起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //创建缓和曲线
    animation->setEasingCurve(QEasingCurve::InOutElastic);
    //开始执行动画(执行完后释放堆区数据)
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void  MyPushbutton::zoom2()
{
    //创建动画对象(并没有放到对象树)
    QPropertyAnimation  * animation = new QPropertyAnimation(this,"geometry");

    //设置时间间隔，单位毫秒
    animation->setDuration(200);
    //创建起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //创建结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建缓和曲线
    animation->setEasingCurve(QEasingCurve::InOutElastic);
    //开始执行动画(执行完后释放堆区数据)
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

//重写按下
void MyPushbutton::mousePressEvent(QMouseEvent * e)
{
    //如果按下图片的路径不为空，代表需要切换图片
    if(m_PressImg != "")
    {
        //创建QPixmap对象
        QPixmap pix;
        //判断是否能够加载正常显示的图片，若不能提示加载失败
        bool ret = pix.load(m_PressImg);
        if(!ret)
        {
            QString str = QString("图片加载失败 %1").arg(m_PressImg);
            qDebug()<< str;
            return;
        }

        //设置图片的固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式表(设置边框透明)
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}

//重写释放
void MyPushbutton::mouseReleaseEvent(QMouseEvent * e)
{
    if(m_NormalImg != "")
    {
        //创建QPixmap对象
        QPixmap pix;
        //判断是否能够加载正常显示的图片，若不能提示加载失败
        bool ret = pix.load(m_NormalImg);
        if(!ret)
        {
            QString str = QString("图片加载失败 %1").arg(m_NormalImg);
            qDebug()<< str;
            return;
        }

        //设置图片的固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式表(设置边框透明)
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
