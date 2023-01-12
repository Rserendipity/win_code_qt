#include "myinfo.h"
#include "./ui_myinfo.h"

MyInfo::MyInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyInfo)
{
    ui->setupUi(this);

    // 设置标题
    this->setWindowTitle("作者信息");

    // 发出返回的信号
    connect(ui->btn_return, &QPushButton::clicked, [=](){
        emit this->back();
    });
}
