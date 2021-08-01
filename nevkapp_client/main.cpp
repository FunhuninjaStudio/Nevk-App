#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QSplashScreen>

#include<thread>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QPixmap pixmap("splash.png");//875,500
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();

    QTcpSocket* check = new QTcpSocket();
    check->connectToHost("localhost",80);

    if(!check->waitForConnected(10000))
    {
        QMessageBox::critical(nullptr,"Error","Could not connect to the server.");
        exit(0);
    }

    check->close();
    MainWindow w;
    QFile theme("theme.qss");
    theme.open(QFile::ReadOnly);
    QString theme_s = theme.readAll();
    w.setStyleSheet(theme_s);

    theme.close();
    w.show();
    splash.finish(&w);
    return a.exec();
}