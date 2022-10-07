#include "appwindow.h"
#include "settingstab.h"
#include "maintab.h"
#include "windowbar.h"

#include <QTabWidget>
#include <QBoxLayout>
#include <QPropertyAnimation>
#include <QScreen>
#include <QGuiApplication>

AppWindow::AppWindow(QWidget* wgt)
    : QWidget(wgt)
{
    m_tabWidget = new QTabWidget;

    // Основные вкладки
    SettingsTab* setTab  = new SettingsTab(this);
    MainTab*     mainTab = new MainTab(this);

    QWidgetList wgtList;

    wgtList << mainTab << setTab;

    foreach(QWidget* wgt, wgtList) {
        m_tabWidget->addTab(wgt, wgt->metaObject()->className());
    }

    // Бар окна программы
    WindowBar* winBar = new WindowBar(this);


    // Компоновка с вкладками
    QHBoxLayout* boxTab = new QHBoxLayout;
    boxTab->addWidget(m_tabWidget);

    m_boxLayout = new QVBoxLayout;

    m_boxLayout->addLayout(winBar->getLayout());
    m_boxLayout->addLayout(boxTab);
    setLayout(m_boxLayout);

}


void AppWindow::slotShowMinimized() {

    // Анимация сворачивания окна
    QPropertyAnimation* anim = new QPropertyAnimation(this, "pos");

//    QRect startRect = rect();
//    startRect.moveTo(pos());
//    QRect stopRect = QRect(startRect.center(), QSize(0,0));

//    anim->setStartValue(startRect);
//    anim->setEndValue(stopRect);
//    anim->start(QAbstractAnimation::DeleteWhenStopped);

    QScreen* scr = QGuiApplication::primaryScreen();
    int x = (scr->availableGeometry().width() - width()) / 2;
    int y = (scr->availableGeometry().height() - height()) / 2;
    anim->setDuration(2000);
    anim->setStartValue(QRect(x,0,width(), height()));
    anim->setEndValue(QRect(x,y,width(), height()));
    anim->setEasingCurve(QEasingCurve::OutElastic);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    connect(anim, SIGNAL(finished()), this, SLOT(showMinimized()));
}

void AppWindow::slotClose() {

    // Анимация плавного закрытия окна
    QPropertyAnimation* anim = new QPropertyAnimation(this, "windowOpacity");
    anim->setDuration(110);
    anim->setKeyValueAt(0,1);
    anim->setKeyValueAt(1,0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    connect(anim, SIGNAL(finished()), this, SLOT(close()));
}






