#include "programlst.h"

#include <QFile>
#include <QDir>
#include <QFileInfo>

ProgramLst::ProgramLst(QWidget* wgt)
    : QWidget(wgt)
{
    // .lnk
    QString programPath("C:/Users/Lenovo/AppData/Roaming/Microsoft/Windows/Start Menu/Programs");
    QDir programDir(programPath);
    QFileInfoList fileInfo = programDir.entryInfoList();
    QFileInfoList programLst;

    foreach(QFileInfo fileDir, fileInfo) {
        if (fileDir.isDir()) {
            programPath = fileDir.filePath();
            programDir = programPath;
            fileInfo.append(programDir.entryInfoList());
        }
    }
    foreach(QFileInfo file, fileInfo) {
        if (file.isFile() && file.fileName().endsWith(".lnk")) {
            programLst.append(file);
        }
    }


    qDebug() << programLst;
}
