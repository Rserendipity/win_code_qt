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
    void setOptions();
    void setWords();
    int getCurrentOption();
    int getUserInput();


public slots:
    void userClicked();
    void userClicked_A();
    void userClicked_B();
    void userClicked_C();
    void userClicked_D();

private:
    Ui::MainWindow *ui;

    std::fstream fin;
    QVector<QVector<QString>> ch;
    QVector<QVector<QString>> en;
    QVector<int> options;

    int cur;
    int userInput;
};
#endif // MAINWINDOW_H
