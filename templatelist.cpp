#include "templatelist.h"
#include "mylistwidgetitem.h"

#include <QListWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QFile>

TemplateList::TemplateList(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    m_listWidget = new QListWidget;

    dirPath = QApplication::applicationDirPath()+
            "/icons/";
    setMinimumWidth(370);



    // qss style
    QFile file(dirPath+"list action icons/style.qss");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());
    setStyleSheet(str);

    QVBoxLayout* vBox = new QVBoxLayout;
    vBox->addWidget(m_listWidget);
    setLayout(vBox);
}


void TemplateList::makeListItem(QPixmap icon, QString name)
{
    if (name.size() > 14) {
        name.resize(14);
        name+="...";
    }

    double factor = 20.0;

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

    // widget at widget list
    QWidget* temp = new QWidget;
    temp->setObjectName("tempWgt");

    // template icon
    icon = icon.scaled(icon.size()/16);
    m_lblIcon = new QLabel;
    m_lblIcon->setPixmap(icon);

    // template name
    m_lblName = new QLabel(name);
    m_lblName->setObjectName("templateName");

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(m_lblIcon);
    box->addSpacing(5);
    box->addWidget(m_lblName);
    box->addStretch();
    box->addWidget(m_btnEdit);
    box->addSpacing(-3);
    box->addWidget(m_btnDelete);
    temp->setLayout(box);

    //m_btnEdit->hide();
    //m_btnDelete->hide();

    MyListWidgetItem* item = new MyListWidgetItem(m_listWidget,
                                                  m_btnEdit,
                                                  m_btnDelete);
    item->setSizeHint(temp->sizeHint());
    m_listWidget->setItemWidget(item,temp);

}

//void TemplateList::enterEvent(QEnterEvent*) {
//    m_btnEdit->show();
//    m_btnDelete->show();
//}

//void TemplateList::leaveEvent(QEvent*) {
//    m_btnEdit->hide();
//    m_btnDelete->hide();
//}










