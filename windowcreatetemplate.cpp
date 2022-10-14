#include "windowcreatetemplate.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QApplication>
#include <QFile>

WindowCreateTemplate::WindowCreateTemplate(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    setGeometry(QRect(QPoint(0,0), QSize(800, 600)));
    QString dirPath = QApplication::applicationDirPath();

    // qss
    QFile file(dirPath+"/icons/window create/style.qss");
    file.open(QFile::ReadOnly);
    QString strQss = file.readAll();
    setStyleSheet(strQss);

    // template name
    m_lblName = new QLabel("&Template name:");
    m_lineName = new QLineEdit;
    m_lblName->setBuddy(m_lineName);

    //================buttons settings================
    m_btnCreate = new QPushButton("&Create");
    m_btnCancel = new QPushButton("C&ancel");

    connect(m_btnCreate, SIGNAL(clicked()), SIGNAL(createClicked()));
    connect(m_btnCancel, SIGNAL(clicked()), SIGNAL(cancelClicked()));

    // btn layout
    QHBoxLayout* btnBox = new QHBoxLayout;
    btnBox->addStretch();
    btnBox->addWidget(m_btnCreate);
    btnBox->addStretch();
    btnBox->addWidget(m_btnCancel);
    btnBox->addStretch();
    //===============================================

    // main layout
    QVBoxLayout* mainBox = new QVBoxLayout;
    mainBox->addStretch();
    mainBox->addWidget(m_lblName);
    mainBox->addWidget(m_lineName);
    mainBox->addStretch();
    mainBox->addLayout(btnBox);
    mainBox->addStretch();
    setLayout(mainBox);

}

QString WindowCreateTemplate::getTemplateName() {
    return m_lineName->text();
}

void WindowCreateTemplate::setTemplateName(QString str) {
    m_lineName->setText(str);
}
