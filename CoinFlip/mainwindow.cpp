#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QDebug>
#include <QSound>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //主场景的配置
    //设置窗口标题
    this->setWindowTitle("小帅带你翻金币");
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标(QIcon 或者 QPixmap)
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //实现退出功能
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    ///主场景音效
    QSound * mainSound = new QSound(":/res/LevelWinSound.wav",this);
    mainSound->setLoops(-1);//设置重复播放（-1代表无限播放）
    mainSound->play();

    ///开始音效准备
    QSound * startSound = new QSound(":/res/TapButtonSound.wav");
//    startSound->setLoops(5); //设置重复播放（-1代表无限播放）
//    startSound->play();


    //ChooseLevelScene选择关卡场景指针
    m_Choose = new ChooseLevelScene;

    //实例化开始按钮,并放到对象树
    MyPushbutton * startBtn = new MyPushbutton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);

    //将按钮放到适当位置
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //点击按钮 实现弹跳效果
    connect(startBtn,&MyPushbutton::clicked,[=](){

        mainSound->stop();
        ///播放音效
        startSound->play();

        startBtn->zoom1();
        startBtn->zoom2();

        //延时动画0.5秒
        //QT5.3.1不支持在QTimer::singleShot的形参列表中些lambda表达式，因此通过创建定时器对象来解决

        //        //第二种：创建定时器对象pTimer1（常用）
        //        QTimer * pTimer1 = new QTimer(this);
        //        pTimer1->start(500);
        //        //定时器发出信号timeout
        //        connect(pTimer1, &QTimer::timeout, this, [=](){
        //            this->hide();     //隐藏自身
        //            m_Choose->show(); //弹出选择关卡场景
        //        });

        //延时进入到选择关卡场景
        QTimer::singleShot(500,this,[=](){
            /////设置选择关卡场景位置(第一个与第二个场景同步)
            m_Choose->setGeometry(this->geometry());

            this->hide(); //自身隐藏
            m_Choose->show(); //选择关卡场景显示
        });

    });

    //监听选择关卡场景中的 返回按钮自定义信号
    connect(m_Choose,&ChooseLevelScene::chooseSceneBack,[=](){

        mainSound->play();

        /////设置选择关卡场景位置
        this->setGeometry(m_Choose->geometry());

        m_Choose->hide();
        this->show();
    });
}


//重写paintEvent事件
void MainWindow::paintEvent(QPaintEvent *)
{
    //设置背景图片(通过painter画家)
    //创建画家，指定绘图设备
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置标题图片
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);//缩小一半
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}
