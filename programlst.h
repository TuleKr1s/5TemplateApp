#ifndef PROGRAMLST_H
#define PROGRAMLST_H

#include "templatelist.h"

#include <QWidget>
#include <QFileInfo>
#include <QThread>
#include <QProcess>
#include <QListWidget>

class QListWidgetItem;

class ProgramLst : public QWidget
{
    Q_OBJECT
public:
    ProgramLst(QWidget* wgt = 0);

    QPixmap getFirstItemPix();
    void getProgramList();
    void resetLists();

    bool isRemoveListEmpty();

    void addProgramToAddList(QString);

    QFileInfoList getRemoveListPath();

    friend QFileInfoList getFullDirPath(QString);
private:
    QWidget* mainWgt;

    QFileInfoList m_listProgram;
    QFileInfoList m_listPath;
    TemplateList* m_programAddList;
    TemplateList* m_programRemoveList;


private slots:
    void slotAddItem(QPushButton*);
    void slotRemoveItem(QPushButton*);

    void slotAddPath(QString);
    void slotRemovePath(QString);
};

// =========== thread program list class ========

class ThreadProgramList : public QThread
{
    Q_OBJECT
public:
    ThreadProgramList();
    ThreadProgramList(QFileInfoList& list);

    void run();

    friend QFileInfoList getFullDirPath(QString);
private:
    QFileInfoList m_list;

signals:
    void readyMakeItem(QPixmap, QString, QString);
};

// ======== thread python script class ======

class ThreadPythonScript : public QThread {
    Q_OBJECT
public:
    ThreadPythonScript(QString name = "",
                       QString path = "");

    QPixmap getPix();

    void run();
private:
    QPixmap m_pix;
    QString m_path;
    QString m_name;

signals:
    void pixDownloaded(QPixmap, QString, QString);
};

#endif // PROGRAMLST_H
