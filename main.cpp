//by liang_jk
#include "mainwindow.h"
#include <QApplication>

QSize size(800,600);
QFont font(QString("仿宋"),16);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
