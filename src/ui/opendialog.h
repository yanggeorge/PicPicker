//
// Created by 杨明 on 2023/7/3.
//

#ifndef PICPICKER_OPENDIALOG_H
#define PICPICKER_OPENDIALOG_H

#include <QDialog>
#include "../controller/opendialogcontroller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class OpenDialog; }
QT_END_NAMESPACE

class OpenDialog : public QDialog {
Q_OBJECT

public:
    explicit OpenDialog(OpenDialogController *controller, QWidget *parent = nullptr);

    ~OpenDialog() override;

    void accept() override;

    void reject() override;

private:
    Ui::OpenDialog *ui;

    OpenDialogController *m_controller;
};


#endif //PICPICKER_OPENDIALOG_H
