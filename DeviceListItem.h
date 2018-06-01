//
// Created by Moad, Karl on 6/1/18.
//

#ifndef BLUETOOTHTOOLS_DEVICELISTITEM_H
#define BLUETOOTHTOOLS_DEVICELISTITEM_H

#include <QWidget>
#include <QString>
#include <QListWidgetItem>

class DeviceListItem : public QListWidgetItem{

public:
    DeviceListItem(QString const &id, QListWidget *view=0);
    ~DeviceListItem();

    const QString &getIdentifier() const;


private:
    QString _id;

};


#endif //BLUETOOTHTOOLS_DEVICELISTITEM_H
