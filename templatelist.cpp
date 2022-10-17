#include "templatelist.h"
#include "mywidget.h"

#include <QListWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QFile>
#include <QVector>


TemplateList::TemplateList(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    m_listWidget = new QListWidget;

    dirPath = QApplication::applicationDirPath()+
            "/icons/";

    count = 0;

    setFixedSize(QSize(370,340));


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

    arr.resize(count+1);
    // widget at widget list
    MyWidget* temp = new MyWidget(count);
    temp->setObjectName("tempWgt");
    connect(temp,
            SIGNAL(mouseEnter()), SLOT(slotMouseEnter()));
    connect(temp,
            SIGNAL(mouseLeave()), SLOT(slotMouseLeave()));

    // ===============buttons settings================
    m_btnEdit = new QPushButton(temp);
    m_btnDelete = new QPushButton(temp);
    m_btnEdit->setObjectName("btnEdit");
    m_btnDelete->setObjectName("btnDelete");

    connect(m_btnDelete, SIGNAL(clicked()),
            SLOT(slotItemDelete()));

    QPixmap editIcon(dirPath+"list action icons/edit.png");
    QPixmap deleteIcon(dirPath+"list action icons/delete3.png");

    double factor = 20.0;

    m_btnEdit->setFlat(true);
    m_btnEdit->setIcon(editIcon);
    m_btnEdit->setIconSize(editIcon.size()/factor);

    m_btnDelete->setFlat(true);
    m_btnDelete->setIcon(deleteIcon);
    m_btnDelete->setIconSize(deleteIcon.size()/factor);
    //====================================================


    // template icon
    icon = icon.scaled(icon.size()/16);
    m_lblIcon = new QLabel(temp);
    m_lblIcon->setPixmap(icon);

    // template name
    m_lblName = new QLabel(name, temp);
    m_lblName->setObjectName("templateName");

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(m_lblIcon);
    box->addSpacing(5);
    box->addWidget(m_lblName);
    box->addStretch();
    box->addWidget(m_btnEdit);
    box->addSpacing(-2);
    box->addWidget(m_btnDelete);
    temp->setLayout(box);

    m_btnEdit->hide();
    m_btnDelete->hide();

    QListWidgetItem* item = new QListWidgetItem(m_listWidget);
    item->setSizeHint(temp->sizeHint());
    m_listWidget->setItemWidget(item, temp);
    arr[count] = item;

    emit countListItemsChanged(m_listWidget->count());
    ++count;
}

void TemplateList::slotMouseEnter() {
    setCursor(Qt::PointingHandCursor);
    QWidget* wgt = (QWidget*)sender();
    QPushButton* btnEdit = wgt->findChild<QPushButton*>("btnEdit");
    QPushButton* btnDelete = wgt->findChild<QPushButton*>("btnDelete");
    btnEdit->show();
    btnDelete->show();
}

void TemplateList::slotMouseLeave() {
    setCursor(Qt::ArrowCursor);
    QWidget* wgt = (QWidget*)sender();
    QPushButton* btnEdit = wgt->findChild<QPushButton*>("btnEdit");
    QPushButton* btnDelete = wgt->findChild<QPushButton*>("btnDelete");
    btnEdit->hide();
    btnDelete->hide();
}

int TemplateList::getCountListItems() {
    return m_listWidget->count();
}

void TemplateList::slotItemDelete() {

    QPushButton* btn = (QPushButton*)sender();
    MyWidget* wgt = (MyWidget*)btn->parent();
    int index = wgt->getIndex();
    QListWidgetItem* item = arr[index];

    int row = m_listWidget->row(item);
    delete m_listWidget->takeItem(row);



    emit countListItemsChanged(m_listWidget->count());
}




