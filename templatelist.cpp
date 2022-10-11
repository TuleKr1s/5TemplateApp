#include "templatelist.h"

#include <QListWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QFile>

TemplateList::TemplateList(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{

}


void TemplateList::makeListItem(QPixmap icon, QString name)
{
    QWidget* temp = new QWidget;
    temp->setObjectName("tempWgt");
    m_listWidget = new QListWidget;

    QString dirPath = QApplication::applicationDirPath()+
            "/icons/";
    double factor = 20.0;
    setMinimumWidth(370);
    // buttons settings
    m_btnEdit = new QPushButton;
    m_btnDelete = new QPushButton;
    m_btnEdit->setObjectName("btnEdit");
    m_btnDelete->setObjectName("btnDelete");

    QPixmap editIcon(dirPath+"list action icons/edit.png");
    QPixmap deleteIcon(dirPath+"list action icons/delete3.png");

    m_btnEdit->setFlat(true);
    m_btnEdit->setIcon(editIcon);
    m_btnEdit->setIconSize(editIcon.size()/factor);

    m_btnDelete->setFlat(true);
    m_btnDelete->setIcon(deleteIcon);
    m_btnDelete->setIconSize(deleteIcon.size()/factor);

    // qss style
    QFile file(dirPath+"list action icons/style.qss");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());
    setStyleSheet(str);

    m_icon = icon;
    m_icon = m_icon.scaled(m_icon.size()/16);
    QLabel* lblIcon = new QLabel;
    lblIcon->setPixmap(m_icon);

    m_lblName = new QLabel(name);
    m_lblName->setObjectName("templateName");

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(lblIcon);
    box->addSpacing(5);
    box->addWidget(m_lblName);
    box->addStretch();
    box->addWidget(m_btnEdit);
    box->addSpacing(-3);
    box->addWidget(m_btnDelete);
    temp->setLayout(box);

    QListWidgetItem* item = new QListWidgetItem(m_listWidget);
    item->setSizeHint(temp->sizeHint());
    m_listWidget->setItemWidget(item,temp);

    QVBoxLayout* vBox = new QVBoxLayout;
    vBox->addWidget(m_listWidget);
    setLayout(vBox);
}












