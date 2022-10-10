#ifndef TEMPLATEWIDGETITEM_H
#define TEMPLATEWIDGETITEM_H

#include <QWidget>

class QPushButton;

class TemplateWidgetItem : public QWidget
{
    Q_OBJECT
public:
    TemplateWidgetItem(QWidget* wgt = 0);

    void setIcon(QPixmap);

private:
    QWidget* mainWgt;

    QPushButton* m_btnEdit;
    QPushButton* m_btnDelete;

    QPixmap m_icon;
};

#endif // TEMPLATEWIDGETITEM_H
