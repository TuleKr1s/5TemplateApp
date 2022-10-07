#ifndef MAINTAB_H
#define MAINTAB_H

#include <QWidget>

class MainTab : public QWidget
{
    Q_OBJECT
public:
    MainTab(QWidget* wgt = 0);
private:
    QWidget* mainWgt;
};

#endif // MAINTAB_H
