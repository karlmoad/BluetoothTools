//
// Created by Moad, Karl on 6/1/18.
//

#include "DeviceListItem.h"

DeviceListItem::DeviceListItem(QString const &id, QListWidget *view):QListWidgetItem(id,view,QListWidgetItem::UserType) {
    _id = id;
}

DeviceListItem::~DeviceListItem() {}

const QString &DeviceListItem::getIdentifier() const {
    return _id;
}
