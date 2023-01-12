#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <QString>
#include <QVector>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initMenu();
    void readWordFile();

public slots:
    void userClicked();

private:
    Ui::MainWindow *ui;

    std::fstream fin;
    QVector<QVector<QString>> ch;
    QVector<QVector<QString>> en;
};
#endif // MAINWINDOW_H
