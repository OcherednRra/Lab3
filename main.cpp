#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication applicaton(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return applicaton.exec();
}
