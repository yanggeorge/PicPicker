//
// Created by 杨明 on 2023/6/29.
//

#ifndef PICPICKER_PICPICKER_H
#define PICPICKER_PICPICKER_H

#include <QMainWindow>
#include "src/controller/picpickercontroller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class PicPicker; }

class QEvent;
class PicPickerController;

QT_END_NAMESPACE


class PicPicker : public QMainWindow {
Q_OBJECT

public:
    explicit PicPicker(PicPickerController *controller, QWidget *parent = nullptr);

    ~PicPicker() override;

    void showImage(const QString &pic);

protected:

    void showEvent(QShowEvent* event);

private:
    Ui::PicPicker *ui;

    PicPickerController *m_controller;

};


#endif //PICPICKER_PICPICKER_H
