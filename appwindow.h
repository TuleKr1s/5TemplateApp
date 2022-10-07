#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QWidget>

class QVBoxLayout;
class QTabWidget;

class AppWindow : public QWidget
{
    Q_OBJECT
public:
    AppWindow(QWidget* wgt = 0);
private:
    QTabWidget*     m_tabWidget;
    QVBoxLayout*    m_boxLayout;
};

#endif // APPWINDOW_H
