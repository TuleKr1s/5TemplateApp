#include "appwindow.h"
#include "settingstab.h"
#include "maintab.h"
#include "windowbar.h"

#include <QTabWidget>
#include <QBoxLayout>

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








