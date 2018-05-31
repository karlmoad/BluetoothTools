//
// Created by Moad, Karl on 5/31/18.
//

#ifndef BLUETOOTHTOOLS_MAINWINDOW_H
#define BLUETOOTHTOOLS_MAINWINDOW_H


#include <QMainWindow>
#include <QtWidgets>
#include <QString>
#include <QSettings>
#include <QCloseEvent>
#include <QSignalMapper>
#include <BluetoothToolsApplication.h>

class MainWindow: public QMainWindow
{

    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initPrimaryInterface();
    void createMenus();
    void manageMenu(bool);


protected:
    void closeEvent(QCloseEvent *event);


public slots:
    void quitTriggered();
    void aboutTriggered();



private:
    QMenu *m_fileMenu;
    QMenu *m_helpMenu;
    QAction *m_quitAction;
    QAction *m_aboutAction;
};


#endif //BLUETOOTHTOOLS_MAINWINDOW_H
