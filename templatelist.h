#ifndef TEMPLATELIST_H
#define TEMPLATELIST_H

#include <QWidget>

class QListWidget;
class QListWidgetItem;
class QLabel;
class QPushButton;

class TemplateList : public QWidget
{
    Q_OBJECT
public:
    TemplateList(QWidget* wgt = 0);

    void makeListItem(QPixmap, QString);
    int getCountListItems();
private:
    QWidget* mainWgt;
    QString dirPath;

    QListWidget* m_listWidget;
    QLabel* m_lblName;
    QLabel* m_lblIcon;

    QVector<QListWidgetItem*> arr;

    QPushButton* m_btnEdit;
    QPushButton* m_btnDelete;

    int count;

private slots:
    void slotMouseEnter();
    void slotMouseLeave();
    void slotItemDelete();

signals:
    void countListItemsChanged(int);
};

#endif // TEMPLATELIST_H
