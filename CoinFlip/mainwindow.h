#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chooselevelscene.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    //维护选择关卡场景
    ChooseLevelScene * m_Choose;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
