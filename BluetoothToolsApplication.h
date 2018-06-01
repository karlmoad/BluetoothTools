//
// Created by Moad, Karl on 5/31/18.
//

#ifndef BLUETOOTHTOOLS_BLUETOOTHTOOLSAPPLICATION_H
#define BLUETOOTHTOOLS_BLUETOOTHTOOLSAPPLICATION_H

#include <QString>

namespace BluetoothToolsApplication {

    const QString OrgName = "koad.io";
    const QString OrgDomain = "koad.io";
    const QString AppName = "BluetoothTools";
    const QString AppTitle = "BluetoothTools";
    const QString FileExtension = ".btt";
    const QStringList FileExtensionWildcard = QStringList("*.btt");
    const QString Scanning = "Scanning for %1 devices ...";
    const QString Stopping = "Scanner stopping ...";
    const QString Stopped ="No scanner is currently running";
}

enum class ScanType{
    CLASSIC=0,
    LE=1,
    NONE=100
};

struct RSSIData {
    qint64 epoch;
    qint16 rssi;
};


#endif //BLUETOOTHTOOLS_BLUETOOTHTOOLSAPPLICATION_H
