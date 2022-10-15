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
    int getCountListItems();
private:
    QWidget* mainWgt;
    QString dirPath;

    int countRow;

    int countListItems;

    QVector<QVector<QWidget*>> arrWgt;

    QListWidget* m_listWidget;
    QLabel* m_lblName;
    QLabel* m_lblIcon;

    QPushButton* m_btnEdit;
    QPushButton* m_btnDelete;

private slots:
    void slotMouseEnter(int index);
    void slotMouseLeave(int index);

signals:
    void countListItemsChanged(int);
};

#endif // TEMPLATELIST_H
