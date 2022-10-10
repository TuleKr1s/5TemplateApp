#include "templatewidgetitem.h"

#include <QPushButton>
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>

TemplateWidgetItem::TemplateWidgetItem(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    QString dirPath = QApplication::applicationDirPath()+
            "/icons/";
    double factor = 10.0;

    QPixmap pix(dirPath+"template icons/free-icon-3d-view-4236727.png");
    QLabel* lbl = new QLabel;
    pix = pix.scaled(pix.size()/(factor-5.0));
    lbl->setPixmap(pix);

    m_btnEdit = new QPushButton;
    m_btnDelete = new QPushButton;

    QPixmap editIcon(dirPath+"list action icons/edit.png");
    QPixmap deleteIcon(dirPath+"list action icons/delete.png");


    m_btnEdit->setFlat(true);
    m_btnEdit->setIcon(editIcon);
    m_btnEdit->setIconSize(editIcon.size()/factor);

    m_btnDelete->setFlat(true);
    m_btnDelete->setIcon(deleteIcon);
    m_btnDelete->setIconSize(deleteIcon.size()/factor);

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(lbl);
    box->addStretch();
    box->addWidget(m_btnEdit);
    box->addWidget(m_btnDelete);
    setLayout(box);
}


void TemplateWidgetItem::setIcon(QPixmap icon) {
    m_icon = icon;
}
