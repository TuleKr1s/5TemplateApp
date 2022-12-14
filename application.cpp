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
        m_wndCreate->hideEvent();
    }
}

void Application::showCreateWnd() {
    m_wndCreate->showEvent();
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
            // display an error about an existing template with the name
            WindowError* errorWnd = new WindowError(this, WindowError::WARNING_WND);
            QString errorText("A template with the same name already"
                              " exists. Do you want to overwrite it?");
            QString titleText("Warning");
            errorWnd->setTitle(titleText);
            errorWnd->setText(errorText);
            if (errorWnd->exec() == QDialog::Rejected)
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

