#ifndef PROGRAMLST_H
#define PROGRAMLST_H

#include "templatelist.h"

#include <QWidget>
#include <QFileInfo>

class ProgramLst : public QWidget
{
    Q_OBJECT
public:
    ProgramLst(QWidget* wgt = 0);

    QPixmap getFirstItemPix();
    void getProgramList();
private:
    QWidget* mainWgt;

    QFileInfoList m_listProgram;
    TemplateList* m_programAddList;
    TemplateList* m_programRemoveList;

    QFileInfoList getFullDirPath(QString);

private slots:
    void slotAddItem(QPushButton*);
    void slotRemoveItem(QPushButton*);
};

#endif // PROGRAMLST_H
