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
#include <QSettings>

// ============================== Program list class ============================

ProgramLst::ProgramLst(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    m_programAddList = new TemplateList(mainWgt, TemplateList::PROGRAM_LIST_ADD);
    m_programRemoveList = new TemplateList(mainWgt, TemplateList::PROGRAM_LIST_REMOVE);

    // connect for interaction with items
    connect(m_programAddList, SIGNAL(btnAddClicked(QPushButton*)),
            SLOT(slotAddItem(QPushButton*)));
    connect(m_programRemoveList, SIGNAL(btnRemoveClicked(QPushButton*)),
            SLOT(slotRemoveItem(QPushButton*)));

    // connect for add/remove program path to list
    connect(m_programRemoveList, SIGNAL(programAdd(QString)),
            SLOT(slotAddPath(QString)));
    connect(m_programRemoveList, SIGNAL(programRemove(QString)),
            SLOT(slotRemovePath(QString)));


    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(m_programAddList);
    box->addWidget(m_programRemoveList);
    setLayout(box);

}

void ProgramLst::getProgramList() {

    ThreadProgramList* thread = new ThreadProgramList(m_listProgram);
    connect(thread, SIGNAL(readyMakeItem(QPixmap, QString, QString)),
            m_programAddList, SLOT(slotMakeItem(QPixmap, QString, QString)));
    thread->start();
}

void ProgramLst::slotAddItem(QPushButton* btn) {
    MyWidget* wgt = (MyWidget*)btn->parent();
    QLabel* pix = wgt->findChild<QLabel*>("icon");
    QLabel* name = wgt->findChild<QLabel*>("templateName");
    QLabel* path = wgt->findChild<QLabel*>("path");
    m_programRemoveList->makeListItem(pix->pixmap(), name->text(), path->text());
}

void ProgramLst::slotRemoveItem(QPushButton* btn) {
    MyWidget* wgt = (MyWidget*)btn->parent();
    QLabel* pix = wgt->findChild<QLabel*>("icon");
    QLabel* name = wgt->findChild<QLabel*>("templateName");
    QLabel* path = wgt->findChild<QLabel*>("path");
    m_programAddList->makeListItem(pix->pixmap(), name->text(), path->text());
}

QPixmap ProgramLst::getFirstItemPix() {
    QLabel* lblPix = m_programRemoveList->getFirstWidgetPix();
    QPixmap pix = lblPix->pixmap();
    return pix;
}

void ProgramLst::resetLists() {
    m_programAddList->clear();
    m_programRemoveList->clear();
    m_listPath.clear();
    m_listProgram.clear();
}

bool ProgramLst::isRemoveListEmpty() {
    return m_programRemoveList->isEmpty();
}

void ProgramLst::addProgramToAddList(QString path) {
    QFileInfo file(path);


    QPixmap pix;
    if (!file.fileName().endsWith(".url")) {
        file.setFile(file.canonicalFilePath());

        QFileIconProvider provider;
        pix = provider.icon(file).pixmap(QSize(100,100),
                                         QIcon::Normal, QIcon::On);
    } else {
        ThreadPythonScript* script = new ThreadPythonScript(path);
        script->start();
        pix = script->getPix();
    }

    QString name = file.fileName();
    name = name.replace(".lnk", "");
    name = name.replace(".exe", "");
    name = name.replace(".url", "");

    m_programAddList->makeListItem(pix, name, file.filePath());
}

void ProgramLst::slotAddPath(QString path) {
    m_listPath.append(QFileInfo(path));
}

void ProgramLst::slotRemovePath(QString path) {
    for (int i = 0; i < m_listPath.size(); ++i) {
        if (m_listPath.at(i).filePath() == path) {
            m_listPath.erase(m_listPath.begin() + i);
        }
    }
}

QFileInfoList ProgramLst::getRemoveListPath() {
    return m_listPath;
}

// ===========================================================================
// ============================= friend functions ==============================

QFileInfoList getFullDirPath(QString path) {
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



//===================================================================
//========================== Thread class ===============================

ThreadProgramList::ThreadProgramList(QFileInfoList& list)
    : m_list(list) {

}

ThreadProgramList::ThreadProgramList() {

}

void ThreadProgramList::run() {
    // path to programs at windows start menu
    QString winDirPath("C:/ProgramData/Microsoft"
                       "/Windows/Start Menu/Programs");

    // Username definition. Only windows since
    // I have not worked in other environments and
    // do not know how they work
//    QString name = qgetenv("USER");
//    if (name.isEmpty())
//        name = qgetenv("USERNAME");

    // path to programs at user start menu
//    QString userDirPath(QString("C:/Users/%1/AppData"
//                                "/Roaming/Microsoft/Windows"
//                                "/Start Menu/Programs").arg(name));

    QDir dir(winDirPath);

    m_list = dir.entryInfoList();
    m_list.pop_front();
    m_list.pop_front();

    int i = 0;
    foreach(QFileInfo fileDir, m_list) {
        if (fileDir.isDir()) {
            m_list.erase(m_list.begin()+i);
            m_list.append(getFullDirPath(fileDir.filePath()));
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
    //===========================================

    // adding programs already added by the user before
    QSettings settings("5TuleKrisov", "5TemplateApp");
    settings.beginGroup("/Settings");
        int size = settings.value("/size", 0).toInt();
        for (int i = 1; i <= size; ++i) {
            QString path = settings.value(QString("/%1/Path").arg(i), "").toString();
            m_list.append(QFileInfo(path));
        }
    settings.endGroup();
    //======================


    foreach(QFileInfo file, m_list) {
        if (file.isFile() && (file.fileName().endsWith(".lnk")
                              || file.fileName().endsWith(".exe")
                              || file.fileName().endsWith(".url"))) {
            QFileIconProvider provider;

            QString programPath = file.filePath();
            QString programName = file.fileName().replace(".lnk", "");
            programName = programName.replace(".exe", "");

            bool check = 1;
            foreach(QString str, filter) {
                if (programName.toLower().contains(str)) {
                    check = 0;
                    break;
                }
            }
            if (!check)
                continue;

            QPixmap programIcon;
            if (!file.fileName().endsWith(".url")) {
                file.setFile(file.canonicalFilePath());
                programIcon = provider.icon(file).pixmap(QSize(100,100),
                                                         QIcon::Normal, QIcon::On);
            }
            else {
                QString dirPath = QApplication::applicationDirPath();

                programName = programName.replace(".url", "");
                programIcon = dirPath + "/Python/downloaded icons/"+programName+".png";
                QIcon icon(programIcon.scaled(100,100));
                programIcon = icon.pixmap(QSize(100,100), QIcon::Normal, QIcon::On);
            }



            if (programName.size() > 40)
                programName.resize(40);

            emit readyMakeItem(programIcon, programName, programPath);
        }
    }


    //dir.setPath(userDirPath);
    //fileInfoList = dir.entryInfoList();
}
// ==============================================================
// ========================= thread python script class =========

ThreadPythonScript::ThreadPythonScript(QString path)
    : m_path(path) {

}

void ThreadPythonScript::run() {
    QFileInfo file(m_path);
    QString dirPath = QApplication::applicationDirPath();
    QFile file1(dirPath +"/Python/program name.txt");
    file1.open(QFile::WriteOnly);
    QTextStream stream(&file1);
    QString name = file.fileName().replace(".url", "");
    stream << name;
    file1.close();

    QProcess* process = new QProcess;
    QStringList arg = {dirPath + "/Python/download icon.py"};
    process->start("python", arg);
    process->waitForFinished();

    m_pix = dirPath + "/Python/downloaded icons/"+name+".png";
}

QPixmap ThreadPythonScript::getPix() {
    return m_pix;
}
