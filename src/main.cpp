
#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("VKAudioSync");
    QApplication::setApplicationVersion("0.01a");
    MainWindow w;
    w.resize(300,200);
    w.show();
    return a.exec();
}
