#include "maintab.h"

#include <QPushButton>
#include <QApplication>
#include <QBoxLayout>
#include <QFile>
#include <QListWidget>

MainTab::MainTab(QWidget* wgt)
    :QWidget(wgt), mainWgt(wgt)
{
    // ================buttons part=====================
    m_btnCreate = new QPushButton("&Create new \ntemplate");
    m_btnAddExisting = new QPushButton("&Add an existing \ntemplate...");

    QString dirPath = QApplication::applicationDirPath()+
            "/icons/main action icons/";

    QPixmap AddIcon(dirPath+"open.png");
    QPixmap createIcon(dirPath+"create.png");

    // division factor
    double factor = 11.0;

    // buttons settings
    m_btnCreate->setIcon(createIcon);
    m_btnCreate->setIconSize(createIcon.size()/factor);
    m_btnCreate->setFlat(true);

    m_btnAddExisting->setIcon(AddIcon);
    m_btnAddExisting->setIconSize(AddIcon.size()/factor);
    m_btnAddExisting->setFlat(true);

    // list widget settings
    QString dirPathIcons = QApplication::applicationDirPath();
    m_listWidget = new TemplateList(this);
    m_listWidget->makeListItem(QPixmap(dirPathIcons+"/icons/template icons/1.png"),
                               QString("123456789qwertyuiopasdfghjk"));
    m_listWidget->makeListItem(QPixmap(dirPathIcons+"/icons/template icons/1.png"),
                               QString("123456789qwertyuiopasdfghjk"));
    m_listWidget->makeListItem(QPixmap(dirPathIcons+"/icons/template icons/1.png"),
                               QString("123456789qwertyuiopasdfghjk"));

    setGeometry(QRect(QPoint(590,236), QSize(800, 600)));

    // qss style
    QFile file(dirPath+"style.qss");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());
    setStyleSheet(str);

    // layout with main buttons
    QVBoxLayout* btnBox = new QVBoxLayout;
    btnBox->addStretch();
    btnBox->setSpacing(0);
    btnBox->addWidget(m_btnCreate);
    btnBox->addWidget(m_btnAddExisting);
    btnBox->addStretch();

    // main layout
    m_mainBox = new QHBoxLayout;
    m_mainBox->addWidget(m_listWidget);
    m_mainBox->addStretch();
    m_mainBox->addLayout(btnBox);
    //m_mainBox->setContentsMargins(0,0,0,0);
    setLayout(m_mainBox);


}










