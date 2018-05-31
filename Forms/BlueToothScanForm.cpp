//
// Created by Moad, Karl on 5/31/18.
//

#include "BlueToothScanForm.h"
#include "ui_BlueToothScanForm.h"

BlueToothScanForm::BlueToothScanForm(QWidget *parent): QWidget(parent), ui(new Ui::BlueToothScanForm){
    ui->setupUi(this);
}

BlueToothScanForm::~BlueToothScanForm() {
    delete ui;
}
