#include "windowframe.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QPalette>
#include <QFile>
#include <QPropertyAnimation>
#include <QMouseEvent>

WindowFrame::WindowFrame(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    // ===========temp code for test==========
    //замена
    this->setWindowFlags(Qt::FramelessWindowHint);
    //============================================

    m_btnShowMaximize = new QPushButton;
    m_btnShowMinimize = new QPushButton;
    m_btnShowMinimize->setObjectName("minBtn");
    m_btnClose = new QPushButton;
    m_btnClose->setObjectName("closeBtn");

    connect(m_btnClose, SIGNAL(clicked()), this, SLOT(slotClose()));
    connect(m_btnShowMinimize, SIGNAL(clicked()), this, SLOT(slotMinimized()));

    // path to icons
    QString dirPath = QApplication::applicationDirPath()+
            "/icons/window frame icons/";

    QPixmap maxIcon(dirPath+"max icon.png");
    QPixmap minIcon(dirPath+"min icon white.png");
    QPixmap closeIcon(dirPath+"close icon white.png");

    // division factor
    double factor = 1.7;

    m_btnShowMaximize->setIcon(maxIcon);
    m_btnShowMaximize->setIconSize(maxIcon.size()/factor);
    m_btnShowMaximize->setFlat(true);
    m_btnShowMaximize->setEnabled(false);

    m_btnShowMinimize->setIcon(minIcon);
    m_btnShowMinimize->setIconSize(minIcon.size()/factor);
    m_btnShowMinimize->setFlat(true);

    m_btnClose->setIcon(closeIcon);
    m_btnClose->setIconSize(closeIcon.size()/factor);
    m_btnClose->setFlat(true);

    // widget geometry замена 800
    setGeometry(QRect(QPoint(0,0), QSize(800, closeIcon.height()/factor)));

    // ===========temp code for test==========

    this->move(800, 600);
    //====================================

    // settings qss style
    QFile file(dirPath+"style.qss");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());
    setStyleSheet(str);

    m_mainBox = new QHBoxLayout;
    m_mainBox->setContentsMargins(0,0,0,0);
    m_mainBox->setSpacing(0);
    m_mainBox->addStretch();
    m_mainBox->addWidget(m_btnShowMinimize);
    m_mainBox->addWidget(m_btnShowMaximize);
    m_mainBox->addWidget(m_btnClose);
    setLayout(m_mainBox);
}

void WindowFrame::slotClose() {
    //замена
    QPropertyAnimation* anim = new QPropertyAnimation(this, "windowOpacity");
    anim->setDuration(120);
    anim->setKeyValueAt(0,1);
    anim->setKeyValueAt(1,0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    //замена
    connect(anim, SIGNAL(finished()), this, SLOT(close()));
}

void WindowFrame::slotMinimized() {
    //замена
    QPropertyAnimation* animPos = new QPropertyAnimation(this, "pos");
    QPropertyAnimation* animOp = new QPropertyAnimation(this, "windowOpacity");

    int duration = 50;

    // замена
    int x = this->pos().x();
    int y = this->pos().y();
    animPos->setDuration(duration);
    animPos->setStartValue(QPoint(x,y));
    animPos->setEndValue(QPoint(x,0));

    animOp->setDuration(duration);
    animOp->setKeyValueAt(0,1);
    animOp->setKeyValueAt(1,0);

    animPos->start(QAbstractAnimation::DeleteWhenStopped);
    animOp->start(QAbstractAnimation::DeleteWhenStopped);

    // замена
    connect(animOp, SIGNAL(finished()), this, SLOT(showMinimized()));
}

QPoint WindowFrame::getPrevPos() {
    return m_prevPos;
}

void WindowFrame::slotSetPrevPos(QPoint prevPos) {
    if (m_prevPos == prevPos)
        return;
    m_prevPos = prevPos;
}

void WindowFrame::mousePressEvent(QMouseEvent* me) {
    if (me->button() == Qt::LeftButton)
        slotSetPrevPos(me->pos());
    return QWidget::mousePressEvent(me);
}

void WindowFrame::mouseMoveEvent(QMouseEvent* me) {
    auto dx = me->pos().x() - m_prevPos.x();
    auto dy = me->pos().y() - m_prevPos.y();
    //замена
    this->setGeometry(this->x()+dx, this->y()+dy,width(),height());
    return QWidget::mouseMoveEvent(me);
}


