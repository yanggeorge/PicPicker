//
// Created by 杨明 on 2023/8/26.
//

#ifndef PICPICKER_CLICKABLELABEL_H
#define PICPICKER_CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class ClickableLabel : public QLabel {
Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

    ~ClickableLabel();

signals:

    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

};


#endif //PICPICKER_CLICKABLELABEL_H
