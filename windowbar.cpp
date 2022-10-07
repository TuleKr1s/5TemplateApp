#include "windowbar.h"
#include "qevent.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QPropertyAnimation>

WindowBar::WindowBar(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    mainWgt->setWindowFlags(Qt::FramelessWindowHint);

    m_btnHide   = new QPushButton("-");
    m_btnClose  = new QPushButton("X");

    connect(m_btnHide, SIGNAL(clicked()), mainWgt, SLOT(slotShowMinimized()));
    connect(m_btnClose, SIGNAL(clicked()), mainWgt, SLOT(slotClose()));

    // Переменные для расчета высоты области виджета
    auto dy = 21;   // Высота кнопки
    auto posDy = m_btnHide->pos().y();  //

    // Установка области виджета
    this->setGeometry(QRect(QPoint(0,0), QSize(mainWgt->width(),posDy*2+dy)));

    m_boxLayout = new QHBoxLayout;

    m_boxLayout->addStretch();
    m_boxLayout->addWidget(m_btnHide);
    m_boxLayout->addWidget(m_btnClose);


}

QHBoxLayout* WindowBar::getLayout() {
    return m_boxLayout;
}

QPoint WindowBar::prevPos() const {
    return m_prevPos;
}

void WindowBar::slotSetPrevPos(QPoint prevPos) {
    if (m_prevPos == prevPos)
        return;

    m_prevPos = prevPos;
    emit prevPosChanged(prevPos);
}

void WindowBar::mousePressEvent(QMouseEvent* pe) {
    if (pe->button() == Qt::LeftButton) {
        slotSetPrevPos(pe->pos());
    }
    return QWidget::mousePressEvent(pe);
}



void WindowBar::mouseMoveEvent(QMouseEvent* pe) {

    auto dx = pe->pos().x() - m_prevPos.x();
    auto dy = pe->pos().y() - m_prevPos.y();
    mainWgt->setGeometry(mainWgt->x() + dx, mainWgt->y() + dy, width(), height());
    return QWidget::mouseMoveEvent(pe);
}







