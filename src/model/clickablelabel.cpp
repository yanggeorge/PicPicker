//
// Created by 杨明 on 2023/8/26.
//

#include "clickablelabel.h"
#include <QDebug>

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f) : QLabel(parent) {
    qDebug() << "new ClickableLabel";
}

ClickableLabel::~ClickableLabel() {

}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    qDebug() << "mouse pressed";
    emit clicked();
}

