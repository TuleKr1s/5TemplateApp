#include "application.h"

#include <QBoxLayout>
#include <QDir>
#include <QFile>
#include <QFileInfo>

Application::Application(QWidget* wgt)
    : QWidget(wgt)
{

    setGeometry(QRect(QPoint(590,236), QSize(800, 600)));

    // variable for icons
    countIcon = 0;

    m_mainTab = new MainTab(this);
    m_wndCreate = new WindowCreateTemplate(this);
    m_frame = new WindowFrame(this);

    connect(m_mainTab,SIGNAL(createClicked()),SLOT(showCreateWnd()));
    connect(m_wndCreate, SIGNAL(cancelClicked()), SLOT(showMainTab()));
    connect(m_wndCreate, SIGNAL(createClicked()), SLOT(slotCreate()));

    // initialization list with icons
    lstIcons = QDir(dirPath+"/icons/template icons").entryInfoList();
    lstIcons.pop_front();
    lstIcons.pop_front();


    // main layout
    QVBoxLayout* mainBox = new QVBoxLayout;
    mainBox->addWidget(m_frame);
    mainBox->addWidget(m_mainTab);
    mainBox->addWidget(m_wndCreate);

    m_wndCreate->hide();
}

void Application::showMainTab() {
    m_wndCreate->hide();
    m_mainTab->show();
}

void Application::showCreateWnd() {
    m_mainTab->hide();
    m_wndCreate->show();
}

void Application::slotCreate() {
    QPixmap pix(dirPath+"/icons/template icons/"+lstIcons[countIcon].fileName());
    QString name = m_wndCreate->getTemplateName();
    if (name != "error") {
        m_mainTab->makeListItem(pix, name);
        ++countIcon;
        showMainTab();
        m_wndCreate->setTemplateName("");
    }
}







