//
// Created by Moad, Karl on 5/31/18.
//

#include "BlueToothScanForm.h"
#include "ui_BlueToothScanForm.h"

BlueToothScanForm::BlueToothScanForm(QMap<QString, QBluetoothDeviceInfo> *devices, QMap<QString, QList<RSSIData>> *rssi, QWidget *parent): QWidget(parent), ui(new Ui::BlueToothScanForm){
    ui->setupUi(this);
    _devices = devices;
    _rssi = rssi;

    connect(ui->listDevices, &QListWidget::itemDoubleClicked, this, &BlueToothScanForm::onOpenDevice);
}

BlueToothScanForm::~BlueToothScanForm() {
    delete ui;
}

void BlueToothScanForm::onDeviceInformationAvailable(QString const &id) {

    if(_index.contains(id)) {
        if(id.compare(_currentDeviceIdentifier,Qt::CaseSensitive) ==0) {
            loadDeviceData(id);
        }
        else {
            _index[id]->setBackgroundColor(QColor(0,0,255,125));
        }
    }
    else {
        _index[id] = new DeviceListItem(id, ui->listDevices);
        ui->listDevices->addItem(_index[id]);
    }
}

void BlueToothScanForm::onOpenDevice(const QListWidgetItem *clicked) {
    if(clicked != nullptr) {
        DeviceListItem *item = dynamic_cast<DeviceListItem*>(clicked);
        bool locked = _mutex.try_lock();
        if(locked) {
            _currentDeviceIdentifier = item->getIdentifier();
            _mutex.unlock();

            loadDeviceData(item->getIdentifier());
        }
    }
}

void BlueToothScanForm::loadDeviceData(QString const &id) {
    _index[id]->setBackgroundColor(QColor(255,255,255,255));


}
