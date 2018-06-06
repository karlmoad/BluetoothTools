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
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothUuid>
#include <QMap>
#include <QList>
#include <QDateTime>
#include <BluetoothToolsApplication.h>
#include "Forms/BlueToothScanForm.h"
#include "Utility.h"

class MainWindow: public QMainWindow
{

    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createMenus();

protected:
    void closeEvent(QCloseEvent *event);
    void setScanState(bool state);

public slots:
    void quitTriggered();
    void aboutTriggered();
    void startScanner();
    void stopScanner();
    void scanTypeLEChecked();
    void scanTypeClassicChecked();
    void saveData();
    void onDeviceScanned(const QBluetoothDeviceInfo &info);
    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error);
    void scanFinished();

signals:
    void notifyDeviceInfoAvailable(QString const &id);

private:
    QMenu *m_fileMenu;
    QMenu *m_helpMenu;
    QMenu *m_ScanMenu;
    QMenu *m_DataMenu;
    QAction *m_saveAction;
    QAction *m_quitAction;
    QAction *m_aboutAction;
    QAction *m_LE;
    QAction *m_Classic;
    QAction *m_startScan;
    QAction *m_stopScan;
    QActionGroup *m_scanTypeGroup;

    BlueToothScanForm *_mainForm;
    ScanType _current = ScanType::LE;
    bool _scanning = false;

    QBluetoothDeviceDiscoveryAgent *_agent;
    QMap<QString, QBluetoothDeviceInfo> _devices;
    QMap<QString, QList<RSSIData>> _rssiHistory;
};


#endif //BLUETOOTHTOOLS_MAINWINDOW_H
