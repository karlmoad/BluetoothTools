//
// Created by Moad, Karl on 5/31/18.
//

#ifndef BLUETOOTHTOOLS_BLUETOOTHSCANFORM_H
#define BLUETOOTHTOOLS_BLUETOOTHSCANFORM_H


#include <QMainWindow>
#include <QtWidgets>
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QBluetoothDeviceInfo>
#include <QBluetoothUuid>
#include <QMutex>
#include <QMap>
#include <QList>
#include <QDateTime>
#include <BluetoothToolsApplication.h>
#include "DeviceListItem.h"
#include "Utility.h"


namespace Ui {
    class BlueToothScanForm;
}


class BlueToothScanForm : public QWidget
{
    Q_OBJECT

public:
    BlueToothScanForm(QMap<QString, QBluetoothDeviceInfo> *devices, QMap<QString, QList<RSSIData>> *rssi, QWidget *parent=0);
    ~BlueToothScanForm();

public slots:
    void onDeviceInformationAvailable(QString const &id);
    void onOpenDevice(const QListWidgetItem *clicked);

private:
    Ui::BlueToothScanForm *ui;
    QMap<QString, QBluetoothDeviceInfo> *_devices;
    QMap<QString, QList<RSSIData>> *_rssi;
    QMap<QString, DeviceListItem*> _index;
    QString _currentDeviceIdentifier;
    QMutex _mutex;


    void loadDeviceData(QString const &id);
    void resize();



};


#endif //BLUETOOTHTOOLS_BLUETOOTHSCANFORM_H
