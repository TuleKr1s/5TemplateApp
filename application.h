#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>

#include "maintab.h"
#include "windowcreatetemplate.h"
#include "windowframe.h"
#include "windowerror.h"

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

    WindowError* error;

    QString dirPath = QApplication::applicationDirPath();

    void loadTemplates();
private slots:
    void showMainTab();
    void showCreateWnd();

    void slotCreate(QPixmap);
};

#endif // APPLICATION_H
