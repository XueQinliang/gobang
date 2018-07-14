//by liang_jk
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void on_start_clicked();

private:
    QLineEdit username;
    QPushButton start;
    QLabel label;
};

#endif // MAINWINDOW_H
