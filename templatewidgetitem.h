#ifndef TEMPLATEWIDGETITEM_H
#define TEMPLATEWIDGETITEM_H

#include <QWidget>

class QPushButton;
class QLabel;

class TemplateWidgetItem : public QWidget
{
    Q_OBJECT
public:
    TemplateWidgetItem(QWidget* wgt = 0);

    void setIcon(QPixmap);
    void setName(QString);

private:
    bool temp;

    QWidget* mainWgt;

    QPushButton* m_btnEdit;
    QPushButton* m_btnDelete;

    QLabel* m_templateName;

    QLabel* m_lblIcon;

};

#endif // TEMPLATEWIDGETITEM_H
