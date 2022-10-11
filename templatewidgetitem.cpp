#include "templatewidgetitem.h"

#include <QPushButton>
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QFile>

TemplateWidgetItem::TemplateWidgetItem(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{

    temp = 1;
    QString dirPath = QApplication::applicationDirPath()+
            "/icons/";
    double factor = 20.0;

    setMinimumWidth(370);

    // buttons settings
    m_btnEdit = new QPushButton;
    m_btnDelete = new QPushButton;
    connect(m_btnEdit, SIGNAL(clicked()), this, SLOT(slotTest()));

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

    m_lblIcon = new QLabel;
    m_templateName = new QLabel;

    //setName("name");
    //QPixmap pix(dirPath+"template icons/free-icon-3d-view-4236727.png");
    //setIcon(pix);

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(m_lblIcon);
    box->addSpacing(5);
    box->addWidget(m_templateName);
    box->addStretch();
    box->addWidget(m_btnEdit);
    box->addSpacing(-3);
    box->addWidget(m_btnDelete);
    setLayout(box);
}


void TemplateWidgetItem::setIcon(QPixmap icon) {
    icon = icon.scaled(icon.size()/(16));
    m_lblIcon->setPixmap(icon);
}

void TemplateWidgetItem::setName(QString name) {
    m_templateName->setObjectName("templateName");
    if (name.size() > 16) {
        name.resize(16);
        name += "...";
    }
    m_templateName->setText(name);
}








