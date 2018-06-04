//
// Created by Moad, Karl on 5/31/18.
//

#ifndef BLUETOOTHTOOLS_UTILITY_H
#define BLUETOOTHTOOLS_UTILITY_H

#include <QString>
#include <QBluetoothDeviceInfo>
#include <QBluetoothUuid>
#include <QBluetoothAddress>
#include <QTreeWidgetItem>

class Utility {
public:
    static const QString getDeviceId(QBluetoothDeviceInfo const &device);
    static QTreeWidgetItem* addTreeItem(QString const &name, QString const &value, QTreeWidget *tree = nullptr,QTreeWidgetItem *parent=nullptr);
};


#endif //BLUETOOTHTOOLS_UTILITY_H
