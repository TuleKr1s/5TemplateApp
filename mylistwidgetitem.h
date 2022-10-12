#ifndef MYLISTWIDGETITEM_H
#define MYLISTWIDGETITEM_H

#include <QListWidget>
#include <QPushButton>

class MyListWidgetItem : public QListWidgetItem
{
    Q_OBJECT
public:
    MyListWidgetItem(QListWidget* wgt = 0,
                     QPushButton* btn1 = 0,
                     QPushButton* btn2 = 0);

private:
    QPushButton* m_btn1;
    QPushButton* m_btn2;

signals:
    void MouseEnterSignal();
    void MouseLeaveSignal();

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // MYLISTWIDGETITEM_H
