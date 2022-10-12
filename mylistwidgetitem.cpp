#include "mylistwidgetitem.h"

#include <QObject>

MyListWidgetItem::MyListWidgetItem(QListWidget* wgt,
                                   QPushButton* btn1,
                                   QPushButton* btn2)
    : QListWidgetItem(wgt), m_btn1(btn1), m_btn2(btn2)
{

}

bool MyListWidgetItem::eventFilter(QObject* obj, QEvent* event) {
    bool result = QObject::eventFilter(obj, event)
}
