#include "templatelist.h"
#include "mywidget.h"

#include <QListWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QFile>
#include <QVector>
#include <QMouseEvent>
#include <QProcess>
#include <QFileInfo>
#include <QFileIconProvider>

//========================= Template list class ======================

TemplateList::TemplateList(QWidget* wgt, flags flag)
    : QWidget(wgt), mainWgt(wgt), m_currentFlag(flag)
{
    m_listWidget = new QListWidget;

    m_listWidget->setFocusPolicy(Qt::NoFocus);

    if (m_currentFlag != TEMPLATE_LIST) {
        connect(m_listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                SLOT(slotSendSignal(QListWidgetItem*)));
    }
    else if (m_currentFlag == TEMPLATE_LIST) {
        connect(m_listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                SLOT(slotLaunchTemplate(QListWidgetItem*)));
    }

    if (m_currentFlag == PROGRAM_LIST_REMOVE) {
        m_listWidget->setDragDropMode(QAbstractItemView::InternalMove);
        m_listWidget->setDefaultDropAction(Qt::TargetMoveAction);
        m_listWidget->setMovement(QListView::Free);
    }


    dirPath = QApplication::applicationDirPath()+
            "/icons/";

    count = 0;

    setFixedSize(QSize(370,340));

    //======================= qss style======================
    QFile file;
    if (m_currentFlag == TEMPLATE_LIST)
        file.setFileName(dirPath+"list action icons/styleTemplate.qss");
    else if (m_currentFlag == PROGRAM_LIST_ADD ||
             m_currentFlag == PROGRAM_LIST_REMOVE)
        file.setFileName(dirPath+"list action icons/styleProgram.qss");

    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());
    setStyleSheet(str);
    // ===========================================

    QVBoxLayout* vBox = new QVBoxLayout;
    vBox->addWidget(m_listWidget);
    setLayout(vBox);
}

void TemplateList::makeListItem(QLabel* lblIcon, QLabel* lblName) {
    QPixmap pix = lblIcon->pixmap();
    QString name = lblName->text();
    makeListItem(pix, name);
}

void TemplateList::makeListItem(QPixmap icon, QString name, QString path)
{

    arr.resize(count+1);
    // widget at widget list
    MyWidget* temp = new MyWidget(count);
    temp->setObjectName("tempWgt");

    connect(temp,
            SIGNAL(mouseEnter()), SLOT(slotMouseEnter()));
    connect(temp,
            SIGNAL(mouseLeave()), SLOT(slotMouseLeave()));

// ===============buttons settings==============================
    m_btnEdit = new QPushButton(temp);
    m_btnDelete = new QPushButton(temp);
    m_btnEdit->setObjectName("btnEdit");
    m_btnDelete->setObjectName("btnDelete");

    m_btnAdd = new QPushButton(temp);
    m_btnRemove = new QPushButton(temp);
    m_btnAdd->setObjectName("btnAdd");
    m_btnRemove->setObjectName("btnRemove");

    connect(m_btnAdd, SIGNAL(clicked()),
            SLOT(slotSendSignal()));
    connect(m_btnRemove, SIGNAL(clicked()),
            SLOT(slotSendSignal()));

    connect(m_btnAdd, SIGNAL(clicked()),
            SLOT(slotItemDelete()));
    connect(m_btnRemove, SIGNAL(clicked()),
            SLOT(slotItemDelete()));

    connect(m_btnDelete, SIGNAL(clicked()),
            SLOT(slotItemDelete()));


    double factor = 20.0;

    // ================== template list buttons ==============
    QPixmap editIcon;
    QPixmap deleteIcon;
    editIcon.load(dirPath+"list action icons/edit.png");
    deleteIcon.load(dirPath+"list action icons/delete3.png");

    m_btnEdit->setFlat(true);
    m_btnEdit->setIcon(editIcon);
    m_btnEdit->setIconSize(editIcon.size()/factor);

    m_btnDelete->setFlat(true);
    m_btnDelete->setIcon(deleteIcon);
    m_btnDelete->setIconSize(deleteIcon.size()/factor);
    // ======================================

    // ============ program list buttons =============
    QPixmap addIcon;
    QPixmap removeIcon;
    addIcon.load(dirPath+"list action icons/plus.png");
    removeIcon.load(dirPath+"list action icons/minus.png");

    m_btnAdd->setFlat(true);
    m_btnAdd->setIcon(addIcon);
    m_btnAdd->setIconSize(addIcon.size()/1.4);

    m_btnRemove->setFlat(true);
    m_btnRemove->setIcon(removeIcon);
    m_btnRemove->setIconSize(removeIcon.size()/1.4);
    //=====================================


//====================================================


    // template icon
    QIcon templateIcon(icon.scaled(QSize(100,100)));
    QPixmap pixIcon = templateIcon.pixmap(m_currentFlag == TEMPLATE_LIST
                                  ? QSize(32,32) : QSize(16,16),
                                  QIcon::Normal, QIcon::On);
    m_lblIcon = new QLabel(temp);
    m_lblIcon->setPixmap(pixIcon);
    m_lblIcon->setObjectName("icon");


    // template name
    m_lblName = new QLabel(name, temp);
    m_lblName->setObjectName("templateName");

    //======================= layout settings ===========================
    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(m_lblIcon);
    box->addSpacing(5);
    box->addWidget(m_lblName);
    box->addStretch();
    if (m_currentFlag == TEMPLATE_LIST) {
        box->addWidget(m_btnEdit);
        box->addSpacing(-2);
        box->addWidget(m_btnDelete);
    }
    else if (m_currentFlag == PROGRAM_LIST_ADD) {
        box->addWidget(m_btnAdd);
    }
    else if (m_currentFlag == PROGRAM_LIST_REMOVE) {
        box->addWidget(m_btnRemove);
    }
    temp->setLayout(box);

    m_btnEdit->hide();
    m_btnDelete->hide();
    m_btnAdd->hide();
    m_btnRemove->hide();
    //==============================================

    // ==================== list widget settings ====================
    MyListWidgetItem* item = new MyListWidgetItem(m_listWidget);
    // what is the sorting parameter
    item->setData(-1, m_lblName->text());

    item->setSizeHint(temp->sizeHint());
    m_listWidget->setItemWidget(item, temp);
    arr[count] = item;

    if (m_currentFlag == PROGRAM_LIST_ADD)
        m_listWidget->sortItems();
    //========================================================

    // program path
    m_programPath = new QLabel(temp);
    if (!path.isEmpty()) {
        m_programPath->setText(path);
        m_programPath->setObjectName("path");

        emit programAdd(m_programPath->text());
    }
    emit countListItemsChanged(m_listWidget->count());
    ++count;
}

void TemplateList::slotMouseEnter() {
    setCursor(Qt::PointingHandCursor);
    QWidget* wgt = (QWidget*)sender();
    if (m_currentFlag == TEMPLATE_LIST) {
        QPushButton* btnEdit = wgt->findChild<QPushButton*>("btnEdit");
        QPushButton* btnDelete = wgt->findChild<QPushButton*>("btnDelete");
        btnEdit->show();
        btnDelete->show();
    }
    else if (m_currentFlag == PROGRAM_LIST_ADD) {
        QPushButton* btnAdd = wgt->findChild<QPushButton*>("btnAdd");
        btnAdd->show();
    }
    else if (m_currentFlag == PROGRAM_LIST_REMOVE) {
        QPushButton* btnRemove = wgt->findChild<QPushButton*>("btnRemove");
        btnRemove->show();
    }
}

void TemplateList::slotMouseLeave() {
    setCursor(Qt::ArrowCursor);
    QWidget* wgt = (QWidget*)sender();
    if (m_currentFlag == TEMPLATE_LIST) {
        QPushButton* btnEdit = wgt->findChild<QPushButton*>("btnEdit");
        QPushButton* btnDelete = wgt->findChild<QPushButton*>("btnDelete");
        btnEdit->hide();
        btnDelete->hide();
    }
    else if (m_currentFlag == PROGRAM_LIST_ADD) {
        QPushButton* btnAdd = wgt->findChild<QPushButton*>("btnAdd");
        btnAdd->hide();
    }
    else if (m_currentFlag == PROGRAM_LIST_REMOVE) {
        QPushButton* btnRemove = wgt->findChild<QPushButton*>("btnRemove");
        btnRemove->hide();
    }
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

    if (m_currentFlag == TEMPLATE_LIST) {
        // delete template file
        QString name = wgt->findChild<QLabel*>("templateName")->text();
        QFile file(QApplication::applicationDirPath()+QString("/Saves/%1.tff").arg(name));
        file.remove();
    }

    if (!m_programPath->text().isEmpty()) {
        emit programRemove(wgt->findChild<QLabel*>("path")->text());
    }
    delete m_listWidget->takeItem(row);
    emit countListItemsChanged(m_listWidget->count());
}

void TemplateList::slotItemDelete(QListWidgetItem* item) {

    MyWidget* wgt = (MyWidget*)m_listWidget->itemWidget(item);
    QLabel* path = wgt->findChild<QLabel*>("path");

    if (!path->text().isEmpty()) {
        emit programRemove(path->text());
    }

    delete m_listWidget->takeItem(m_listWidget->row(item));

    emit countListItemsChanged(m_listWidget->count());

}

void TemplateList::slotSendSignal(QListWidgetItem* item) {

    MyWidget* wgt = (MyWidget*)m_listWidget->itemWidget(item);
    QPushButton* btn;
    if (m_currentFlag == PROGRAM_LIST_ADD) {
        btn = wgt->findChild<QPushButton*>("btnAdd");
        emit btnAddClicked(btn);
    }
    else if (m_currentFlag == PROGRAM_LIST_REMOVE) {
        btn = wgt->findChild<QPushButton*>("btnRemove");
        emit btnRemoveClicked(btn);
    }
    slotItemDelete(item);
}

void TemplateList::slotSendSignal() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        if (btn->objectName() == "btnAdd")
            emit btnAddClicked(btn);
        else if (btn->objectName() == "btnRemove")
            emit btnRemoveClicked(btn);
    }
}

QLabel* TemplateList::getFirstWidgetPix() {
    MyWidget* wgt = (MyWidget*)m_listWidget->itemWidget(m_listWidget->item(0));
    QLabel* lblPath = wgt->findChild<QLabel*>("path");
    QLabel* lblName = wgt->findChild<QLabel*>("templateName");
    QPixmap pix;

    QFileInfo file(lblPath->text());

    if (file.filePath().endsWith(".url")) {
        pix = QApplication::applicationDirPath()+
                QString("/Python/downloaded icons/%1.png").arg(lblName->text());
        QIcon icon(pix.scaled(QSize(100,100)));
        pix = icon.pixmap(QSize(100,100), QIcon::Normal, QIcon::On);
    }
    else {
        QFileIconProvider provider;
        file.setFile(file.canonicalFilePath());
        pix = provider.icon(file).pixmap(QSize(100,100),
                                         QIcon::Normal, QIcon::On);
    }


    QLabel* lblPix = new QLabel;
    lblPix->setPixmap(pix);
    //QLabel* lblPix = wgt->findChild<QLabel*>("icon");
    return lblPix;
}

void TemplateList::slotMakeItem(QPixmap pix, QString str, QString path) {
    makeListItem(pix, str, path);
}

void TemplateList::clear() {
    m_listWidget->clear();
}

bool TemplateList::isEmpty() {
    return !m_listWidget->count();
}

void TemplateList::slotLaunchTemplate(QListWidgetItem* item) {
    MyWidget* wgt = (MyWidget*)m_listWidget->itemWidget(item);
    QString name = wgt->findChild<QLabel*>("templateName")->text();

    QFile file(QApplication::applicationDirPath()
               +QString("/Saves/%1.tff").arg(name));

    file.open(QFile::ReadOnly);
    QDataStream stream(&file);

    QPixmap pix;

    stream >> name >> pix;


    while(!stream.atEnd()) {
        QString str;
        stream >> str;
        QFileInfo fileInfo(str);
        QProcess* process = new QProcess;
        process->startDetached("cmd", QStringList() << "/c" << fileInfo.filePath());
        process->waitForStarted();
    }
    qApp->closeAllWindows();
}

QStringList TemplateList::getNames() {
    QStringList names;
    for (int i = 0; i < arr.size(); ++i) {
        MyWidget* wgt = (MyWidget*)m_listWidget->itemWidget(arr[i]);
        QString name = wgt->findChild<QLabel*>("templateName")->text();
        names << name;
    }
    return names;
}
// ==============================================================
















