// Simple project to scan, monitor, and log Bluetooth Antenna data
// Created by Moad, Karl on 5/31/18.
// ---------------------------------------------------------------


#include <QApplication>
#include <MainWindow.h>
#include <BluetoothToolsApplication.h>

int main(int argc, char *argv[]) {

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    QCoreApplication::setOrganizationDomain(BluetoothToolsApplication::OrgDomain);
    QCoreApplication::setOrganizationName(BluetoothToolsApplication::OrgName);
    QCoreApplication::setApplicationName(BluetoothToolsApplication::AppName);

    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/images/bluetooth_512.png"));

    MainWindow w;
    w.show();
    a.setActiveWindow(&w);

    int ret = a.exec();
    return ret;
}

