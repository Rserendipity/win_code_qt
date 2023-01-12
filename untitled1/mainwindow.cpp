#include "mainwindow.h"      // 主窗口类的实现
#include "./ui_mainwindow.h" // ui
#include "myinfo.h"          // 自己写的菜单栏窗口
#include <QMenuBar>          // 菜单栏的头文件
#include <QAction>
#include <QDebug>

#define DEBUG

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 设置ui
    ui->setupUi(this);

    // 设置主窗口的标题
    this->setWindowTitle("背单词");
    // 设置主窗口中textBrowser的字体、信息、居中对齐
    ui->textBrowser->setFont(QFont(tr("Consolas"), 20));
    // ui->textBrowser->setText("text");
    ui->textBrowser->setAlignment(Qt::AlignCenter);

    // 设置菜单栏
    this->initMenu();

    // 设置用户点击后的响应、把按键A到D全部连接到userClicked槽上
    connect(ui->btn_A, &QPushButton::clicked, this, &MainWindow::userClicked);
    connect(ui->btn_B, &QPushButton::clicked, this, &MainWindow::userClicked);
    connect(ui->btn_C, &QPushButton::clicked, this, &MainWindow::userClicked);
    connect(ui->btn_D, &QPushButton::clicked, this, &MainWindow::userClicked);

    // 读取文件里的单词信息、找不到文件就报错
    this->readWordFile();
}


void MainWindow::initMenu()
{
    // 创建并设置菜单栏
    QMenuBar *menu = new QMenuBar(this);
    this->setMenuBar(menu);
    // 菜单
    QMenu *menu_help = new QMenu("帮助", menu);
    menu->addMenu(menu_help);
    // 菜单项
    QAction *menu_help_info = new QAction("作者信息", menu_help);
    menu_help->addAction(menu_help_info);

    // 创建我的信息窗口
    MyInfo *myInfo = new MyInfo();
    // 设置菜单项点击后的显示菜单
    connect(menu_help_info, &QAction::triggered, [=]()
            { myInfo->show(); });
    // 窗口返回后隐藏菜单
    connect(myInfo, &MyInfo::back, [=]()
            { myInfo->hide(); });
}

void MainWindow::readWordFile()
{
    char* tmp = new char[1000];
    // 读取所有的中文含义
    ch.resize(4);
    qDebug() << "***********************" << endl;
    for (int i = 0; i < 4; i++)
    {
        std::string s;
#ifdef DEBUG
        s += "E:\\code\\win_code_qt\\untitled1\\data\\ch";
#else
        //s += "./data/ch";
#endif
        s += std::to_string(i);
        s += ".txt";
        ch[i].resize(4449);
        fin.open(s, std::ios::in);
        for (int j = 0; j < 4449; j++)
        {
            fin.getline(tmp, 1000);
            ch[i][j] = tmp;
        }
        fin.close();
    }
    delete[] tmp;
}

void MainWindow::userClicked()
{
}

MainWindow::~MainWindow()
{
    delete ui;
}






