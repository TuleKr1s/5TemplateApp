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
    QString dirPath;

    QListWidget* m_listWidget;
    QLabel* m_lblName;
    QLabel* m_lblIcon;

    QPushButton* m_btnEdit;
    QPushButton* m_btnDelete;

protected:
    //virtual void enterEvent(QEnterEvent*);
    //virtual void leaveEvent(QEvent*);
};

#endif // TEMPLATELIST_H
