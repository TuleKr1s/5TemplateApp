#include "templatelist.h"
#include "mywidget.h"

#include <QListWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QFile>
#include <QVector>

#define WIDGET_ITEM(x)  arrWgt[x][0]
#define BTN_DELETE(x)   arrWgt[x][1]
#define BTN_EDIT(x)     arrWgt[x][2]
#define ICON(x)         arrWgt[x][3]
#define NAME(x)         arrWgt[x][4]

TemplateList::TemplateList(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    m_listWidget = new QListWidget;
    countListItems = 0;

    dirPath = QApplication::applicationDirPath()+
            "/icons/";


    setFixedSize(QSize(370,340));


    countRow = 0;

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

    // initialization of array by widgets in widget list
    arrWgt.resize(countRow+1);
    arrWgt[countRow].resize(5);


    // widget at widget list
    MyWidget* temp = new MyWidget(countRow);
    temp->setObjectName("tempWgt");
    connect(temp,
            SIGNAL(mouseEnter(int)), SLOT(slotMouseEnter(int)));
    connect(temp,
            SIGNAL(mouseLeave(int)), SLOT(slotMouseLeave(int)));

    // ===============buttons settings================
    m_btnEdit = new QPushButton;
    m_btnDelete = new QPushButton;
    m_btnEdit->setObjectName("btnEdit");
    m_btnDelete->setObjectName("btnDelete");

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
    m_lblIcon = new QLabel;
    m_lblIcon->setPixmap(icon);

    // template name
    m_lblName = new QLabel(name);
    m_lblName->setObjectName("templateName");

    WIDGET_ITEM(countRow) = temp;
    BTN_EDIT(countRow) = m_btnEdit;
    BTN_DELETE(countRow) = m_btnDelete;
    ICON(countRow) = m_lblIcon;
    NAME(countRow) = m_lblName;


    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(ICON(countRow)); // icon
    box->addSpacing(5);
    box->addWidget(NAME(countRow)); // name
    box->addStretch();
    box->addWidget(BTN_EDIT(countRow)); // btn edit
    box->addSpacing(-2);
    box->addWidget(BTN_DELETE(countRow)); // btn delete
    WIDGET_ITEM(countRow)->setLayout(box); // set lay to wgt

    m_btnEdit->hide();
    m_btnDelete->hide();

    QListWidgetItem* item = new QListWidgetItem(m_listWidget);
    item->setSizeHint(WIDGET_ITEM(countRow)->sizeHint());
    m_listWidget->setItemWidget(item,WIDGET_ITEM(countRow));

    ++countListItems;
    emit countListItemsChanged(countListItems);
    ++countRow;
}

void TemplateList::slotMouseEnter(int index) {
    setCursor(Qt::PointingHandCursor);
    BTN_DELETE(index)->show();
    BTN_EDIT(index)->show();
}

void TemplateList::slotMouseLeave(int index) {
    setCursor(Qt::ArrowCursor);
    BTN_DELETE(index)->hide();
    BTN_EDIT(index)->hide();
}

int TemplateList::getCountListItems() {
    return countListItems;
}





