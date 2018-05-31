//
// Created by Moad, Karl on 5/31/18.
//

#include "BlueToothScanForm.h"
#include "ui_BlueToothScanForm.h"

BlueToothScanForm::BlueToothScanForm(QMap<QString, QBluetoothDeviceInfo> *devices, QMap<QString, QList<RSSIData>> *rssi, QWidget *parent): QWidget(parent), ui(new Ui::BlueToothScanForm){
    ui->setupUi(this);
    _devices = devices;
    _rssi = rssi;
}

BlueToothScanForm::~BlueToothScanForm() {
    delete ui;
}

void BlueToothScanForm::onDeviceInformationAvailable(QString const &id) {








}
