#ifndef MAINWINDWOW_H
#define MAINWINDWOW_H

#include <QWidget>

class QBoxLayout;
class QGridLayout;
class QSystemTrayIcon;
class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindwow; }
QT_END_NAMESPACE

class mainWindwow : public QWidget {
    Q_OBJECT

public:
    mainWindwow(QWidget *parent = nullptr);
    ~mainWindwow();

    void addWidget(QWidget* wgt, int row, int column, int rowSpan = 1, int columnSpan = 1);
    void addLayout(QBoxLayout* lay, int row, int column);
    void showSystemTray();

private:
    Ui::mainWindwow*    ui;
    QGridLayout*        m_mainLayout;
    QSystemTrayIcon*    m_trayIcon;
    QPushButton*        m_closeWindowBtn;
    QPushButton*        m_hideWindowBtn;

private slots:
    void slotShowHide();
};
#endif // MAINWINDWOW_H
