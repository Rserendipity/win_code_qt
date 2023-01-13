#include "mainwindow.h"      // 主窗口类的实现
#include "./ui_mainwindow.h" // ui
#include "myinfo.h"          // 自己写的菜单栏窗口
#include <QMenuBar>          // 菜单栏的头文件
#include <QAction>
#include <QDebug>
#include <time.h>
#include <stdlib.h>

// #define DEBUG

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cur(0)
    , userInput(-1)
{
    // 初始化随机种子
    srand((size_t)time(nullptr));

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

    // 设置用户点击后的响应：把按键A到D连接到对应的槽上
    connect(ui->btn_A, &QPushButton::clicked, this, &MainWindow::userClicked_A);
    connect(ui->btn_B, &QPushButton::clicked, this, &MainWindow::userClicked_B);
    connect(ui->btn_C, &QPushButton::clicked, this, &MainWindow::userClicked_C);
    connect(ui->btn_D, &QPushButton::clicked, this, &MainWindow::userClicked_D);

    // 读取文件里的单词信息、找不到文件就报错并退出主程序
    this->readWordFile();

    // 初始化完成设置读取完成的单词
    setWords();
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
    for (int i = 0; i < 4; i++)
    {
        std::string s;
#ifdef DEBUG
        s += "E:\\code\\win_code_qt\\untitled1\\data\\ch";
#else
        s += "./data/ch";
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

    // 读取英文的信息
    en.resize(4);
    for (int i = 0; i < 4; i++)
    {
        std::string s;
#ifdef DEBUG
        s += "E:\\code\\win_code_qt\\untitled1\\data\\en";
#else
        s += "./data/en";
#endif
        s += std::to_string(i);
        s += ".txt";
        en[i].resize(4449);
        fin.open(s, std::ios::in);
        for (int j = 0; j < 4449; j++)
        {
            fin.getline(tmp, 1000);
            en[i][j] = tmp;
        }
        fin.close();
    }

    // 读取记录信息
#ifdef DEBUG
    fin.open("E:\\code\\win_code_qt\\untitled1\\data\\info.txt");
#else
    fin.open("./data/info.txt");
#endif
    fin >> cur;
    fin.close();

    // 给选项开辟空间
    options.resize(4);
    delete[] tmp;
}

void MainWindow::userClicked()
{
    int currentOption = getCurrentOption();
    qDebug() << userInput << endl;
    qDebug() << currentOption << endl;
    if (currentOption != userInput) {
        return;
    } else {
        setWords();
    }
}

void MainWindow::userClicked_A()
{
    userInput = 0;
    userClicked();
}
void MainWindow::userClicked_B()
{
    userInput = 1;
    userClicked();
}
void MainWindow::userClicked_C()
{
    userInput = 2;
    userClicked();
}
void MainWindow::userClicked_D()
{
    userInput = 3;
    userClicked();
}

void MainWindow::setOptions()
{
    // 获取0~3的不重复的随机数，作为选项
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        options[i] = -1; // 先给上-1，以免重复
    }
    i = 0;
    while (i < 4)
    {
        int temp = rand() % 4;
        if (options[0] != temp && options[1] != temp && options[2] != temp && options[3] != temp)
        {
            // 获取到的随机值和数组的其他值都不同的时候给数组赋值，然后 i++
            options[i] = temp;
            i++;
        }
    }
}

void MainWindow::setWords()
{
    setOptions();
    ui->textBrowser->setText(en[0][cur]);
    ui->textBrowser->setAlignment(Qt::AlignCenter);
    ui->btn_A->setText(ch[options[0]][cur]);
    ui->btn_B->setText(ch[options[1]][cur]);
    ui->btn_C->setText(ch[options[2]][cur]);
    ui->btn_D->setText(ch[options[3]][cur]);
    cur++;
}

int MainWindow::getUserInput()
{
//    if (ui->btn_A->) {
//        return 0;
//    }
//    if (ui->btn_B->isChecked()) {
//        return 1;
//    }
//    if (ui->btn_C->isChecked()) {
//        return 2;
//    }
//    if (ui->btn_D->isChecked()) {
//        return 3;
//    }
    return -1;
}

int MainWindow::getCurrentOption()
{
    for (int i = 0; i < 4; i++) {
        if (options[i] == 0)
            return i;
    }
    return -1;
}

MainWindow::~MainWindow()
{
    delete ui;
#ifndef DEBUG    //没有定义debug的时候才保存信息，为了调试方便
    fin.open("E:\\code\\win_code_qt\\untitled1\\data\\info.txt", std::ios::out);
    fin << cur;
    fin.close();
#endif
}






