#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) :
    QMainWindow(parent)
{
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建按钮菜单项
    QAction * quit = startMenu->addAction("退出");

    //点击退出 退出游戏
    connect(quit,&QAction::triggered,[=](){
        this->close();
    });



    ///选择关卡按钮音效
    QSound * chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    ///返回按钮音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);


    //创建返回按钮
    MyPushbutton * backBtn = new MyPushbutton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&MyPushbutton::clicked,this,[=](){
        //qDebug()<<"点击了返回按钮";
        ///播放音效
        backSound->play();

        //发出自定义的返回信号
        //延时0.5秒发送
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });

    pScene = nullptr;

    //一维循环 创建20个选择关卡按钮
    for(int i = 0; i<20; i++)
    {
        MyPushbutton * menuBtn = new MyPushbutton(":res/LevelIcon.png");
        menuBtn->setParent(this);
        //x坐标 (i%4) * 50
        //y坐标 (i/4) * 50
        menuBtn->move(25 + (i%4) * 70, 130 + (i/4) * 70);

        connect(menuBtn,&MyPushbutton::clicked,[=](){
            ///播放音效
            chooseSound->play();

            //qDebug()<< "你选择的是第"<<i+1<<"关";
            pScene = new PlayScene(i+1);
            /////设置游戏场景位置(第二个场景与第三个场景的同步)
            this->pScene->setGeometry(this->geometry());

            this->hide();
            pScene->show();

            //在ChooseScene选择关卡场景中，监听PlayScene的返回信号
            connect(pScene,&PlayScene::chooseSceneBack,[=](){
                /////设置游戏场景位置
                this->setGeometry(this->pScene->geometry());

                this->show(); //第二关场景显示出来
                delete pScene;
                pScene = nullptr;
            });
        });

        //menuBtn->setText(QString::number(i+1));
        //创建显示关号的label
        QLabel * label = new QLabel;
        label->setParent(this);

        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText( QString::number(i+1));
        label->move(25 + (i%4) * 70, 130 + (i/4) * 70);

        //设置居中(水平、垂直同时存在)
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置鼠标穿透 Qt::WA_TransparentForMouseEvents 51
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

//重写绘图事件
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);

}

