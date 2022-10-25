#include "programlst.h"
#include "templatelist.h"
#include "mywidget.h"

#include <QFile>
#include <QDir>
#include <QFileIconProvider>
#include <QBoxLayout>
#include <QApplication>
#include <QList>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

ProgramLst::ProgramLst(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    m_programAddList = new TemplateList(mainWgt, TemplateList::PROGRAM_LIST_ADD);
    m_programRemoveList = new TemplateList(mainWgt, TemplateList::PROGRAM_LIST_REMOVE);

    connect(m_programAddList, SIGNAL(btnAddClicked(QPushButton*)),
            SLOT(slotAddItem(QPushButton*)));
    connect(m_programRemoveList, SIGNAL(btnRemoveClicked(QPushButton*)),
            SLOT(slotRemoveItem(QPushButton*)));


    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(m_programAddList);
    box->addWidget(m_programRemoveList);
    setLayout(box);

}

void ProgramLst::getProgramList() {

    // path to programs at windows start menu
    QString winDirPath("C:/ProgramData/Microsoft"
                       "/Windows/Start Menu/Programs");

    // Username definition. Only windows since
    // I have not worked in other environments and
    // do not know how they work
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");

    // path to programs at user start menu
    QString userDirPath(QString("C:/Users/%1/AppData"
                                "/Roaming/Microsoft/Windows"
                                "/Start Menu/Programs").arg(name));

    QDir dir(winDirPath);

    QFileInfoList fileInfoList = dir.entryInfoList();
    fileInfoList.pop_front();
    fileInfoList.pop_front();

    int i = 0;
    foreach(QFileInfo fileDir, fileInfoList) {
        if (fileDir.isDir()) {
            fileInfoList.erase(fileInfoList.begin()+i);
            fileInfoList.append(getFullDirPath(fileDir.filePath()));
            --i;
        }
        ++i;
    }

    //========= filter for programs===============
    QStringList filter;
    QString pathFilter(QApplication::applicationDirPath()+
                       "/icons/Filter.txt");
    QFile file(pathFilter);
    file.open(QFile::ReadOnly);

    filter << QString(file.readAll()).split(' ');
    //qDebug() << filter;
    //===========================================


    foreach(QFileInfo file, fileInfoList) {
        if (file.isFile() && file.fileName().endsWith(".lnk")) {
            QFileIconProvider provider;

            QString programName = file.fileName().replace(".lnk", "");

            bool check = 1;
            foreach(QString str, filter) {
                if (programName.toLower().contains(str)) {
                    check = 0;
                    break;
                }
            }
            if (!check)
                continue;

            file.setFile(file.canonicalFilePath());
            QPixmap programIcon = provider.icon(file).pixmap(16,16);

            if (programName.size() > 40)
                programName.resize(40);

            m_programAddList->makeListItem(programIcon, programName);
        }
    }


    //dir.setPath(userDirPath);
    //fileInfoList = dir.entryInfoList();
}

void ProgramLst::slotAddItem(QPushButton* btn) {
    MyWidget* wgt = (MyWidget*)btn->parent();
    QLabel* pix = wgt->findChild<QLabel*>("icon");
    QLabel* name = wgt->findChild<QLabel*>("templateName");
    m_programRemoveList->makeListItem(pix, name);
}

void ProgramLst::slotRemoveItem(QPushButton* btn) {
    MyWidget* wgt = (MyWidget*)btn->parent();
    QLabel* pix = wgt->findChild<QLabel*>("icon");
    QLabel* name = wgt->findChild<QLabel*>("templateName");
    m_programAddList->makeListItem(pix, name);
}

QPixmap ProgramLst::getFirstItemPix() {
    QLabel* lblPix = m_programRemoveList->getFirstWidget();
    QPixmap pix = lblPix->pixmap();
    return pix;
}

QFileInfoList ProgramLst::getFullDirPath(QString path) {
    QFileInfoList strList;

    QDir dir(path);
    QFileInfoList fileList = dir.entryInfoList();
    fileList.pop_front();
    fileList.pop_front();
    foreach(QFileInfo file, fileList) {
        if (file.isDir()) {
            strList.append(getFullDirPath(file.filePath()));
        }
        else {
            strList.append(QDir(file.path()).entryInfoList());
            strList.pop_front();
            strList.pop_front();
        }
        break;
    }
    return strList;
}
