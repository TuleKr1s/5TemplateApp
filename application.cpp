#include "application.h"

#include <QBoxLayout>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QPropertyAnimation>
#include <QListWidget>

Application::Application(QWidget* wgt)
    : QWidget(wgt)
{

    setGeometry(QRect(QPoint(590,236), QSize(800, 600)));

    m_mainTab = new MainTab(this);
    m_wndCreate = new WindowCreateTemplate(this);
    m_frame = new WindowFrame(this);

    connect(m_mainTab,SIGNAL(createClicked()),SLOT(showCreateWnd()));
    connect(m_wndCreate, SIGNAL(cancelClicked()), SLOT(showMainTab()));
    connect(m_wndCreate, SIGNAL(createClicked(QPixmap)),
            SLOT(slotCreate(QPixmap)));

    //qss style
    QFile file(dirPath+"/icons/appStyle.qss");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());
    setStyleSheet(str);

    // main layout
    QVBoxLayout* mainBox = new QVBoxLayout;
    mainBox->addWidget(m_frame);
    mainBox->addWidget(m_mainTab);
    mainBox->addWidget(m_wndCreate);

    m_wndCreate->hide();
}

void Application::showMainTab() {


    m_mainTab->show();

    if (!m_wndCreate->isHidden()) {
        QPropertyAnimation* anim = new QPropertyAnimation(m_wndCreate,"pos");
        int x = width();
        int y = 0;
        anim->setDuration(125);
        anim->setStartValue(QPoint(x-m_wndCreate->width(), y));
        anim->setEndValue(QPoint(x,y));
        anim->start(QAbstractAnimation::DeleteWhenStopped);

        m_wndCreate->setTemplateName("");
        connect(anim, SIGNAL(finished()), m_wndCreate, SLOT(hide()));
    }
}

void Application::showCreateWnd() {
    m_wndCreate->show();

    QPropertyAnimation* anim = new QPropertyAnimation(m_wndCreate,"pos");
    int x = width();
    int y = 0;
    anim->setDuration(125);
    anim->setStartValue(QPoint(x,y));
    anim->setEndValue(QPoint(x-m_wndCreate->width(), y));
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    connect(anim, SIGNAL(finished()), m_mainTab, SLOT(hide()));
}

void Application::slotCreate(QPixmap pix) {
    QString error = m_wndCreate->checkError();
    if (!error.isEmpty()) {
        return;
    }

    //QPixmap pix(dirPath+"/icons/template icons/"+lstIcons[countIcon].fileName());
    QString name = m_wndCreate->getTemplateName();

    // save template to .tff (template file format)
    QFile fileSaveTemplate(QApplication::applicationDirPath()
                           +QString("/Saves/%1.tff").arg(name));
    if (!fileSaveTemplate.open(QFile::WriteOnly)) {
        return;
    }

    QDataStream stream(&fileSaveTemplate);
    stream.setVersion(QDataStream::Qt_6_2);
    stream << name << pix;

    fileSaveTemplate.close();
    fileSaveTemplate.open(QFile::ReadOnly);

    QString newName;
    QPixmap newPix;

    stream >> newName >> newPix;

    m_mainTab->makeListItem(newPix, newName);
    showMainTab();
    m_wndCreate->setTemplateName("");



}







