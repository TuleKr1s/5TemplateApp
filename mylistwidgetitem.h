#ifndef MYLISTWIDGETITEM_H
#define MYLISTWIDGETITEM_H

#include <QListWidget>
#include <QPushButton>

class MyListWidgetItem : public QListWidgetItem
{
public:
    MyListWidgetItem(QListWidget* wgt = 0,
                     QPushButton* btn1 = 0,
                     QPushButton* btn2 = 0);

private:
    QPushButton* m_btn1;
    QPushButton* m_btn2;


};

#endif // MYLISTWIDGETITEM_H
