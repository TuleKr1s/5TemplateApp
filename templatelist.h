#ifndef TEMPLATELIST_H
#define TEMPLATELIST_H

#include <QWidget>
#include <QListWidgetItem>

class MyWidget;
class QListWidget;
class QLabel;
class QPushButton;

class TemplateList : public QWidget
{
    Q_OBJECT
public:
    enum flags {
        TEMPLATE_LIST,
        PROGRAM_LIST_ADD,
        PROGRAM_LIST_REMOVE
    };

    TemplateList(QWidget* wgt = 0,
                 flags flag = TEMPLATE_LIST);

    void makeListItem(QPixmap, QString);
    void makeListItem(QLabel*, QLabel*);
    int getCountListItems();
    QLabel* getFirstWidget();

    bool isEmpty();

    void clear();
private:
    QWidget* mainWgt;
    QString dirPath;

    QListWidget* m_listWidget;
    QLabel* m_lblName;
    QLabel* m_lblIcon;

    QVector<QListWidgetItem*> arr;

    // for template list
    QPushButton* m_btnEdit;
    QPushButton* m_btnDelete;

    //for program list
    QPushButton* m_btnAdd;
    QPushButton* m_btnRemove;

    int count;

    flags m_currentFlag;

public slots:
    void slotMakeItem(QPixmap, QString);

private slots:
    void slotMouseEnter();
    void slotMouseLeave();

    void slotItemDelete();
    void slotItemDelete(QListWidgetItem*);

    void slotSendSignal();
    void slotSendSignal(QListWidgetItem*);


signals:
    void countListItemsChanged(int);
    void btnAddClicked(QPushButton*);
    void btnRemoveClicked(QPushButton*);
};

// for sorting items int widget list
class MyListWidgetItem : public QListWidgetItem {
public:
    MyListWidgetItem(QListWidget* list)
        : QListWidgetItem(list) {}

    bool operator<(const QListWidgetItem& item) const {
        return this->data(-1).toString() < item.data(-1).toString();
    }

};

#endif // TEMPLATELIST_H
