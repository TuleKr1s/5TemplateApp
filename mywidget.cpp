#include "mywidget.h"

MyWidget::MyWidget(int index, QWidget* wgt)
    : QWidget(wgt), m_index(index)
{
    //setMinimumHeight(50);
}


void MyWidget::enterEvent(QEnterEvent*) {
    emit mouseEnter();
}

void MyWidget::leaveEvent(QEvent*) {
    emit mouseLeave();
}

int MyWidget::getIndex() {
    return m_index;
}

void MyWidget::setIndex(int index) {
    m_index = index;
}
