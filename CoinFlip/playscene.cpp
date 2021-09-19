#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QTimer>
#include <QLabel>
#include <mycoin.h>
#include "dataconfig.h"
#include <QPropertyAnimation> //动画
#include <QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int Index)
    :LeavlIndex(Index)
{
    qDebug()<<"你选择的是第"<<LeavlIndex+1<<"关";
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币界面");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});

    ///返回按钮音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);
    ///翻金币音效
    QSound * flipSound = new QSound(":/res/ConFlipSound.wav",this);
    ///胜利按钮音效
    QSound * winSound = new QSound(":/res/LevelWinSound.wav",this);


    //创建返回按钮
    MyPushbutton * backBtn = new MyPushbutton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&MyPushbutton::clicked,this,[=](){
        //qDebug()<<"点击了返回按钮";

        backSound->play();

        //发出自定义的返回信号
        //延时0.5秒发送
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //创建用户选择关卡的标签
    QLabel * label = new QLabel;
    label->setParent(this);

    QString str = QString("leavel: %1").arg(this->LeavlIndex);
    label->setText(str);

    //设置字体、字号
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(17);
    label->setFont(font);

    //设置位置、大小
    label->setGeometry(QRect(30,this->height()-50,120,50));

    //胜利图片显示
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());

    //创建金币背景图
    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            QLabel * lb = new QLabel;
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            lb->setGeometry(0,0,pix.width(),pix.height());
            lb->setPixmap(pix);
            lb->setParent(this);
            lb->move(57+i*pix.width(),200+j*pix.height());

            dataConfig config;
            for(int i = 0; i<4; ++i)
            {
                for(int j = 0; j<4; ++j)
                {
                    this->gameArray[i][j] = config.mData[this->LeavlIndex][i][j];
                }
            }

            //根据关卡来创建不同的金币场景
            QString str;
            if(gameArray[i][j] == 1)
            {
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }

            //创建金币
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            coin->posX = i; //记录x坐标
            coin->posY = j; //记录y坐标
            coin->flag =gameArray[i][j]; //记录正反标志

            //将金币放到二维数组
            coinBtn[i][j] = coin;

            //监听点击按钮信号
            connect(coin,&MyCoin::clicked,[=](){

                ////将所有按钮都屏蔽掉
                for(int i = 0; i<4; ++i)
                {
                    for(int j = 0; j<4; ++j)
                    {
                        coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();
                //同步二维数组,可以扩展保存功能
                this->gameArray[i][j] = this->gameArray[i][j] == 1 ? 0 : 1;

                //延时 翻转周围硬币
                QTimer::singleShot(300,this,[=](){

                    ///播放音效
                    flipSound->play();

                    //翻转周围硬币 检测右侧金币是否可以翻转
                    if(coin->posX + 1 <=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 1 ? 0 : 1;
                    }

                    //翻转周围硬币 检测左侧金币是否可以翻转
                    if(coin->posX-1 >= 0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 1 ? 0 : 1;
                    }

                    //翻转周围硬币 检测下侧金币是否可以翻转
                    if(coin->posY+1 <= 3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 1 ? 0 : 1;
                    }

                    //翻转周围硬币 检测上侧金币是否可以翻转
                    if(coin->posY-1 >= 0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 1 ? 0 : 1;
                    }

                    ////开启所有按钮
                    for(int i = 0; i<4; ++i)
                    {
                        for(int j = 0; j<4; ++j)
                        {
                            coinBtn[i][j]->isWin = false;
                        }
                    }

                    //检测是否胜利
                    isWin = true;
                    for(int i = 0; i<4; ++i)
                    {
                        for(int j = 0; j<4; ++j)
                        {
                            if(coinBtn[i][j]->flag == false)
                            {
                                this->isWin = false; //有一个为银币就失败
                                break;
                            }
                        }
                    }

                    if(isWin)
                    {
                        qDebug()<< "游戏胜利";

                        ///播放音效
                        winSound->play();

                        //游戏胜利 不允许点击其它按钮
                        for(int i = 0; i<4; ++i)
                        {
                            for(int j = 0; j<4; ++j)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        //将胜利图片做成动画
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000); //时间间隔1秒
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height())); //起始位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));//结束位置
                        animation->setEasingCurve(QEasingCurve::OutBounce); //动画效果
                        animation->start(QAbstractAnimation::DeleteWhenStopped);
                    }
                });

            });
        }
    }
}

//重写绘图事件
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);


}
