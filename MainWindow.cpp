//
// Created by Moad, Karl on 5/31/18.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {


    this->_devices = QMap<QString, QBluetoothDeviceInfo>();
    this->_rssiHistory = QMap<QString, QList<RSSIData>>();

    this->setMinimumSize(1366, 768);
    this->setWindowTitle(BluetoothToolsApplication::AppTitle);
    this->setWindowIcon(QIcon(":/images/bluetooth_32.png"));
    this->menuBar()->setNativeMenuBar(true);
    this->menuBar()->setEnabled(true);
    this->setStatusBar(new QStatusBar(this));
    this->_mainForm = new BlueToothScanForm(&_devices, &_rssiHistory,this);
    this->setCentralWidget(_mainForm);
    this->createMenus();
    this->setScanState(false);

    this->_agent = new QBluetoothDeviceDiscoveryAgent();
    this->_agent->setLowEnergyDiscoveryTimeout(0); //continually scan until stopped
}

MainWindow::~MainWindow() {
    delete(_agent);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    _agent->stop();
    event->accept();
}

void MainWindow::quitTriggered() {
    this->close();
}

void MainWindow::aboutTriggered() {
    QMessageBox::information(this, "About", "BlueToothTools   By Karl Moad");
}

void MainWindow::createMenus() {

    this->m_scanTypeGroup = new QActionGroup(this);
    this->m_scanTypeGroup->setExclusive(true);

    ///File-App menu
    //Quit
    this->m_quitAction = new QAction("Quit", this);
    this->m_quitAction->setShortcut(QKeySequence::Quit);
    this->m_quitAction->setMenuRole(QAction::QuitRole);
    connect(this->m_quitAction, &QAction::triggered, this, &MainWindow::quitTriggered);

    this->m_fileMenu = this->menuBar()->addMenu("App");
    this->m_fileMenu->addAction(this->m_quitAction);

    //Help menu
    //About
    this->m_aboutAction = new QAction("About", this);
    this->m_aboutAction->setMenuRole(QAction::AboutRole);
    connect(this->m_aboutAction, &QAction::triggered, this, &MainWindow::aboutTriggered);

    this->m_helpMenu = this->menuBar()->addMenu("Help");
    this->m_helpMenu->addAction(this->m_aboutAction);

    //Data Menu
    this->m_saveAction = new QAction("Save",this);
    this->m_saveAction->setShortcut(QKeySequence::Save);
    connect(this->m_saveAction, &QAction::triggered, this, &MainWindow::saveData);

    this->m_DataMenu = this->menuBar()->addMenu("Data");
    this->m_DataMenu->addAction(m_saveAction);

    //Scanner menu
    this->m_startScan = new QAction("Start Scanner", this);
    this->m_stopScan = new QAction("Stop Scanner", this);
    this->m_LE = new QAction("BlueTooth LE Scan", this);
    this->m_LE->setCheckable(true);
    this->m_LE->setChecked(false);
    this->m_scanTypeGroup->addAction(m_LE);
    this->m_Classic = new QAction("BlueTooth classic scan", this);
    this->m_Classic->setCheckable(true);
    this->m_Classic->setChecked(false);
    this->m_scanTypeGroup->addAction(m_Classic);

    connect(this->m_Classic, &QAction::triggered, this, &MainWindow::scanTypeClassicChecked);
    connect(this->m_LE, &QAction::triggered, this, &MainWindow::scanTypeLEChecked);
    connect(this->m_startScan, &QAction::triggered, this, &MainWindow::startScanner);
    connect(this->m_stopScan, &QAction::triggered, this, &MainWindow::stopScanner);

    this->m_ScanMenu = this->menuBar()->addMenu("Device Scanner");
    this->m_ScanMenu->addAction(m_Classic);
    this->m_ScanMenu->addAction(m_LE);
    this->m_ScanMenu->addSeparator();
    this->m_ScanMenu->addAction(m_startScan);
    this->m_ScanMenu->addAction(m_stopScan);
}

void MainWindow::startScanner() {
    if(!_scanning) {
        if (_current != ScanType::NONE) {
            setScanState(true);
        } else {
            QMessageBox::critical(this, "Error", "You must first select a scan type and try again");
        }
    }
}

void MainWindow::stopScanner() {
    if(_scanning) {
        setStatusTip(BluetoothToolsApplication::Stopping);
        _agent->stop();
    }
}

void MainWindow::scanTypeLEChecked() {
    if(_scanning) {
        QMessageBox::critical(this, "Error", "You must first stop the current scan to change the scan type");
    }else {
        _current = ScanType::LE;
    }
}

void MainWindow::scanTypeClassicChecked() {
    if(_scanning) {
        QMessageBox::critical(this, "Error", "You must first stop the current scan to change the scan type");
    }else {
        _current = ScanType::CLASSIC;
    }
}

void MainWindow::saveData() {

}

void MainWindow::setScanState(bool state) {
    m_startScan->setEnabled(!state);
    m_stopScan->setEnabled(state);
    setStatusTip( state ?
                  (BluetoothToolsApplication::Scanning.arg((_current == ScanType::LE ? "BlueTooth LE" : "BlueTooth Classic")))
                        : BluetoothToolsApplication::Stopped);
    _scanning=state;

}

void MainWindow::onDeviceScanned(const QBluetoothDeviceInfo &info) {
    QString id = Utility::getDeviceId(info);
    _devices[id] = info;
    RSSIData rssi = {QDateTime::currentMSecsSinceEpoch(), info.rssi()};

    if(!_rssiHistory.contains(id)) {
        _rssiHistory.insert(id, QList<RSSIData>());
    }
    _rssiHistory[id].append(rssi);
    emit notifyDeviceInfoAvailable(id);
};

void MainWindow::deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error) {
    setStatusTip(QString("Discovery Agent Error: %1").arg(_agent->errorString()));
}

void MainWindow::scanFinished() {
    setScanState(false);
}

