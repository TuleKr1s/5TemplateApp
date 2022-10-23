#ifndef PROGRAMLST_H
#define PROGRAMLST_H

#include <QWidget>

class ProgramLst : public QWidget
{
    Q_OBJECT
public:
    ProgramLst(QWidget* wgt = 0);

private:
    QWidget* mainWgt;
};

#endif // PROGRAMLST_H
