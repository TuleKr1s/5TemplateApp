#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>

#include "maintab.h"
#include "windowcreatetemplate.h"
#include "windowframe.h"

#include <QFileInfo>
#include <QApplication>

class Application : public QWidget
{
    Q_OBJECT
public:
    Application(QWidget* wgt = 0);

private:
    MainTab* m_mainTab;
    WindowCreateTemplate* m_wndCreate;
    WindowFrame* m_frame;

    QFileInfoList lstIcons;

    int countIcon;

    QString dirPath = QApplication::applicationDirPath();

private slots:
    void showMainTab();
    void showCreateWnd();

    void slotCreate();
};

#endif // APPLICATION_H
