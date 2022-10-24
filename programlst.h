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

private:
    QWidget* mainWgt;

    QFileInfoList m_listProgram;
    TemplateList* m_programAddList;
    TemplateList* m_programRemoveList;

    void getProgramList();

private slots:
    void slotAddItem(QPushButton*);
    void slotRemoveItem(QPushButton*);
};

#endif // PROGRAMLST_H
