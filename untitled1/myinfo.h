#ifndef MyInfo_H
#define MyInfo_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MyInfo; }
QT_END_NAMESPACE


class MyInfo : public QWidget
{
    Q_OBJECT
public:
    MyInfo(QWidget *parent = nullptr);

signals:
    void back();

public:
    Ui::MyInfo *ui;
};

#endif // MyInfo_H
