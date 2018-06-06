//
// Created by Moad, Karl on 5/31/18.
//

#include "BlueToothScanForm.h"
#include "ui_BlueToothScanForm.h"

BlueToothScanForm::BlueToothScanForm(QMap<QString, QBluetoothDeviceInfo> *devices, QMap<QString, QList<RSSIData>> *rssi, QWidget *parent): QWidget(parent), ui(new Ui::BlueToothScanForm){
    ui->setupUi(this);
    _devices = devices;
    _rssi = rssi;

    ui->btnScan->setIcon(QIcon(":/images/bluetooth_16.png"));
    ui->btnScan->setEnabled(false);
    QStringList headers = { "Field", "Value"};
    ui->treeInfo->setHeaderLabels(headers);
    connect(ui->listDevices, &QListWidget::itemDoubleClicked, this, &BlueToothScanForm::onOpenDevice);
    connect(ui->btnScan, &QPushButton::clicked, this, &BlueToothScanForm::onScanServices);
    ui->scanProgress->setValue(0);
}

BlueToothScanForm::~BlueToothScanForm() {
    delete ui;
}

void BlueToothScanForm::onDeviceInformationAvailable(QString const &id) {

    if(_index.contains(id)) {
        if(id.compare(_currentDeviceIdentifier,Qt::CaseSensitive) ==0) {
            loadRSSIData(id);
        }
        else {
            _index[id]->setBackgroundColor(QColor(0,255,0,75));
        }
    }
    else {
        _index[id] = new DeviceListItem(id, ui->listDevices);
        ui->listDevices->addItem(_index[id]);
    }
}

void BlueToothScanForm::onOpenDevice(const QListWidgetItem *clicked) {
    if(clicked != nullptr) {
        const DeviceListItem *item = dynamic_cast<const DeviceListItem*>(clicked);
        bool locked = _mutex.try_lock();
        if(locked) {
            _currentDeviceIdentifier = item->getIdentifier();
            _mutex.unlock();

            loadDeviceData(item->getIdentifier());
        }
    }
}

void BlueToothScanForm::loadDeviceData(QString const &id) {
    ui->scanProgress->reset();
    ui->treeInfo->clear();
    ui->btnScan->setEnabled(true);
    _index[id]->setBackgroundColor(QColor(255,255,255,255));  //set it back to white so we know if new data arrives

    loadRSSIData(id);
    QBluetoothDeviceInfo device = (*_devices)[id];

    QBluetoothDeviceInfo::CoreConfigurations core = device.coreConfigurations();
    QBluetoothDeviceInfo::ServiceClasses classes = device.serviceClasses();

    Utility::addTreeItem("Address", Utility::getDeviceId(device), ui->treeInfo, nullptr);


    //Configuration
    QString configuration;

    if(core.testFlag(QBluetoothDeviceInfo::CoreConfiguration::LowEnergyCoreConfiguration)) {
        configuration.append(QString("%1%2").arg((configuration.length() > 0 ? ",":""),"BTLE"));
    }

    if(core.testFlag(QBluetoothDeviceInfo::CoreConfiguration::BaseRateCoreConfiguration)) {
        configuration.append(QString("%1%2").arg((configuration.length() > 0 ? ",":""),"Standard"));
    }

    if(core.testFlag(QBluetoothDeviceInfo::CoreConfiguration::BaseRateAndLowEnergyCoreConfiguration)) {
        configuration.append(QString("%1%2").arg((configuration.length() > 0 ? ",":""),"BTLE & Standard"));
    }

    if(configuration.length() == 0)
        configuration = "Unknown";

    Utility::addTreeItem("Configuration",configuration, ui->treeInfo, nullptr);

    QString deviceClass;
    //Major device class
    switch(device.majorDeviceClass()) {
        case QBluetoothDeviceInfo::MajorDeviceClass::MiscellaneousDevice:
            deviceClass = "Miscellaneous";
            break;
        case QBluetoothDeviceInfo::MajorDeviceClass::AudioVideoDevice:
            deviceClass = "Audio/Video";
            break;
        case QBluetoothDeviceInfo::MajorDeviceClass::ComputerDevice:
            deviceClass = "Computer";
            break;
        case QBluetoothDeviceInfo::MajorDeviceClass::HealthDevice:
            deviceClass = "Health";
            break;
        case QBluetoothDeviceInfo::MajorDeviceClass::ImagingDevice:
            deviceClass = "Imaging";
            break;
        case QBluetoothDeviceInfo::MajorDeviceClass::LANAccessDevice:
            deviceClass = "LAN Access";
            break;
        case QBluetoothDeviceInfo::MajorDeviceClass::PeripheralDevice:
            deviceClass = "Peripheral";
            break;
        case QBluetoothDeviceInfo::MajorDeviceClass::PhoneDevice:
            deviceClass = "Phone";
            break;
        case QBluetoothDeviceInfo::MajorDeviceClass::ToyDevice:
            deviceClass = "Toy";
            break;
        case QBluetoothDeviceInfo::MajorDeviceClass::WearableDevice:
            deviceClass = "Wearable";
            break;
        default:
            deviceClass = "Unspecified";
            break;
    }

    Utility::addTreeItem("Device Class", deviceClass, ui->treeInfo, nullptr);
    resize();
}

void BlueToothScanForm::resize() {
    ui->treeInfo->resizeColumnToContents(0);
}

void BlueToothScanForm::onScanServices() {

}

void BlueToothScanForm::loadRSSIData(QString const &id) {

    if(_rssi->contains(id)) {
        ui->tableRSSI->clear();

        QList<RSSIData> rssi = (*_rssi)[id];
        ui->tableRSSI->setColumnCount(2);
        ui->tableRSSI->setRowCount(rssi.size());
        ui->tableRSSI->setHorizontalHeaderLabels({"Epoch","RSSI"});
        ui->tableRSSI->verticalHeader()->hide();
        ui->tableRSSI->setShowGrid(true);

        for(int i=0; i< rssi.size(); i++) {
            QTableWidgetItem *itemEpoch  = new QTableWidgetItem(QString::number(rssi[i].epoch));
            QTableWidgetItem *itemRSSI = new QTableWidgetItem(QString::number(rssi[i].rssi));

            ui->tableRSSI->setItem(i,0,itemEpoch);
            ui->tableRSSI->setItem(i,1,itemRSSI);
        }

        ui->tableRSSI->resizeColumnToContents(0);
        ui->tableRSSI->resizeColumnToContents(1);
    }
}
