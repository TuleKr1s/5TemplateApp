#include "programlst.h"
#include "templatelist.h"

#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QBoxLayout>

ProgramLst::ProgramLst(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
#ifdef Q_OS_WIN
    // Username definition. Only windows since
    // I have not worked in other environments and
    // do not know how they work
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");

    // .lnk
    QString programPath("C:/ProgramData/Microsoft/Windows"
                        "/Start Menu/Programs");
    QDir programDir(programPath);
    QFileInfoList fileInfo = programDir.entryInfoList();
    QFileInfoList listProgram;

    foreach(QFileInfo fileDir, fileInfo) {
        if (fileDir.isDir()) {
            programPath = fileDir.filePath();
            programDir = programPath;
            fileInfo.append(programDir.entryInfoList());
        }
    }
    foreach(QFileInfo file, fileInfo) {
        if (file.isFile() && file.fileName().endsWith(".lnk")) {
            listProgram.append(file);
        }
    }

    TemplateList* programList = new TemplateList(mainWgt, TemplateList::PROGRAM_LIST_ADD);

    foreach(QFileInfo file, listProgram) {
        QFileIconProvider provider;

        QString programName = file.fileName().replace(".lnk", "");
        QPixmap programIcon = provider.icon(file).pixmap(16,16);

        programList->makeListItem(programIcon, programName);
    }

    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(programList);
    setLayout(box);

#endif
}
