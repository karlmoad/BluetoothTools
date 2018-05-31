//
// Created by Moad, Karl on 5/31/18.
//

#ifndef BLUETOOTHTOOLS_BLUETOOTHSCANFORM_H
#define BLUETOOTHTOOLS_BLUETOOTHSCANFORM_H


#include <QWidget>


namespace Ui {
    class BlueToothScanForm;
}


class BlueToothScanForm : public QWidget
{
    Q_OBJECT

public:
    BlueToothScanForm(QWidget *parent=0);
    ~BlueToothScanForm();

public slots:



signals:


private:
    Ui::BlueToothScanForm *ui;


};


#endif //BLUETOOTHTOOLS_BLUETOOTHSCANFORM_H
