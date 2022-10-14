#ifndef MAINTAB_H
#define MAINTAB_H

#include <QWidget>

#include "templatelist.h"

class QPushButton;
class QHBoxLayout;
class QListWidget;

class MainTab : public QWidget
{
    Q_OBJECT
public:
    MainTab(QWidget* wgt = 0);

private:
    QWidget* mainWgt;

    QPushButton* m_btnCreate;
    QPushButton* m_btnAddExisting;

    QHBoxLayout* m_mainBox;

    TemplateList* m_listWidget;

};

#endif // MAINTAB_H
