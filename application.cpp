#include "application.h"

#include <QBoxLayout>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QPropertyAnimation>
#include <QListWidget>
#include <QSettings>

Application::Application(QWidget* wgt)
    : QWidget(wgt)
{

    setGeometry(QRect(QPoint(590,236), QSize(800, 600)));

    // initial program settings in the registry
    QSettings settings("5TuleKrisov", "5TemplateApp");
    if (!settings.contains("/Settings/size")) {
        settings.setValue("/Settings/size", 0);
    }

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
    m_mainBox = new QVBoxLayout;
    m_mainBox->addWidget(m_frame);
    m_mainBox->addWidget(m_mainTab);
    m_mainBox->addWidget(m_wndCreate);

    m_wndCreate->hide();

    loadTemplates();
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

    QString name = m_wndCreate->getTemplateName();
    // check for existing template name
    QStringList existingNames = m_mainTab->getNames();
    foreach(QString existName, existingNames) {
        if (name == existName) {
            // вывести ошибку и предложить дальнейшие действия
            WindowError* m_errorWnd = new WindowError(this);
            QString errorText("A template with the same name already"
                              " exists. Do you want to overwrite it?");
            QString titleText("Creation error");
            m_errorWnd->setTitle(titleText);
            m_errorWnd->setText(errorText);
            if (m_errorWnd->exec() == QDialog::Rejected)
                return;
            else {

                m_mainTab->removeItem(name);
            }

        }
    }



    // save template to .tff (template file format)
    QFile fileSaveTemplate(QApplication::applicationDirPath()
                           +QString("/Saves/%1.tff").arg(name));
    if (!fileSaveTemplate.open(QFile::WriteOnly)) {
        return;
    }

    QDataStream stream(&fileSaveTemplate);
    stream.setVersion(QDataStream::Qt_6_2);
    stream << name << pix;

    QFileInfoList fileInfoList = m_wndCreate->getListPath();
    foreach(QFileInfo file, fileInfoList) {
        stream << file.absoluteFilePath();
    }

    fileSaveTemplate.close();
    //=====================================    

    m_mainTab->makeListItem(pix, name);
    showMainTab();
    m_wndCreate->setTemplateName("");



}


void Application::loadTemplates() {
    QDir savesDir(dirPath+"/Saves");

    QFileInfoList existingFiles = savesDir.entryInfoList(QDir::Files, QDir::Time);
    foreach(QFileInfo fileInfo, existingFiles) {
        QFile file(fileInfo.filePath());
        file.open(QFile::ReadOnly);
        QDataStream stream(&file);

        QString name;
        QPixmap pix;

        stream >> name >> pix;
        m_mainTab->makeListItem(pix,name);
        file.close();
    }
}

