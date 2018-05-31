//
// Created by Moad, Karl on 5/31/18.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    this->setMinimumSize(1366, 768);
    this->setWindowTitle(BluetoothToolsApplication::AppTitle);
    this->setWindowIcon(QIcon(":/images/bluetooth_32.png"));
    this->menuBar()->setNativeMenuBar(true);
    this->menuBar()->setEnabled(true);
    this->createMenus();
}

MainWindow::~MainWindow() {}

void MainWindow::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    event->accept();
}

void MainWindow::quitTriggered() {
    this->close();
}

void MainWindow::aboutTriggered() {
    QMessageBox::information(this, "About", "BlueToothTools   By Karl Moad\n\nUse at your own caution!!");
}

void MainWindow::initPrimaryInterface() {

}

void MainWindow::createMenus() {

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

}

void MainWindow::manageMenu(bool) {

}
