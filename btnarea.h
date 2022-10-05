#ifndef BTNAREA_H
#define BTNAREA_H

#include <QWidget>
#include <QStringList>

class QPushButton;

class btnArea : public QWidget
{
    Q_OBJECT
public:
    btnArea(QWidget* wgt = 0);

private:
    QPushButton* m_launchBtn;
    QPushButton* m_addNewBtn;

    QStringList m_listApp;

private slots:
    void slotLaunch();
    void slotAddNew();
};

#endif // BTNAREA_H
