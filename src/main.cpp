#include <QtGui/QApplication>
#include <QSettings>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName(""); //no organization
    QApplication::setApplicationName("VKAudioSync");
    QApplication::setApplicationVersion("0.01a");

    QSettings settings(QApplication::organizationName(), QApplication::applicationName());

    MainWindow w;
    w.show();
    return a.exec();
}
