#ifndef TEMPLATELIST_H
#define TEMPLATELIST_H

#include <QWidget>

class QListWidget;
class QLabel;
class QPushButton;

class TemplateList : public QWidget
{
    Q_OBJECT
public:
    TemplateList(QWidget* wgt = 0);

    void makeListItem(QPixmap, QString);
private:
    QWidget* mainWgt;

    QListWidget* m_listWidget;
    QPixmap m_icon;
    QLabel* m_lblName;

    QPushButton* m_btnEdit;
    QPushButton* m_btnDelete;
};

#endif // TEMPLATELIST_H
