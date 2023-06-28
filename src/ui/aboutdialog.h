//
// Created by 杨明 on 2023/6/28.
//

#ifndef PICPICKER_ABOUTDIALOG_H
#define PICPICKER_ABOUTDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class AboutDialog; }
QT_END_NAMESPACE

class AboutDialog : public QDialog {
Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);

    ~AboutDialog() override;

private:
    Ui::AboutDialog *ui;
};


#endif //PICPICKER_ABOUTDIALOG_H
