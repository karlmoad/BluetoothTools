//
// Created by Moad, Karl on 5/31/18.
//

#ifndef BLUETOOTHTOOLS_UTILITY_H
#define BLUETOOTHTOOLS_UTILITY_H

#include <QString>
#include <QBluetoothDeviceInfo>
#include <QBluetoothUuid>
#include <QBluetoothAddress>

class Utility {
public:
    static const QString getDeviceId(QBluetoothDeviceInfo const &device);
};


#endif //BLUETOOTHTOOLS_UTILITY_H
