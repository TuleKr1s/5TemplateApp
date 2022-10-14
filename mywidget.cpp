#include "mywidget.h"

MyWidget::MyWidget(int index, QWidget* wgt)
    : QWidget(wgt), m_index(index)
{
    //setMinimumHeight(50);
}


void MyWidget::enterEvent(QEnterEvent*) {
    emit mouseEnter(m_index);
}

void MyWidget::leaveEvent(QEvent*) {
    emit mouseLeave(m_index);
}
