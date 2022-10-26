#include "windowcreatetemplate.h"
#include "programlst.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QApplication>
#include <QFile>
#include <QFileDialog>

WindowCreateTemplate::WindowCreateTemplate(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    setGeometry(QRect(QPoint(0,0), QSize(800, 600)));
    QString dirPath = QApplication::applicationDirPath();

    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor("#121212"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

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

    connect(m_btnCreate,
            SIGNAL(clicked()), SLOT(slotSendCreateSignal()));
    connect(m_btnCancel,
            SIGNAL(clicked()), SIGNAL(cancelClicked()));

    // btn layout
    QHBoxLayout* btnBox = new QHBoxLayout;
    btnBox->addStretch();
    btnBox->addWidget(m_btnCreate);
    btnBox->addStretch();
    btnBox->addWidget(m_btnCancel);
    btnBox->addStretch();
    //===============================================

    // text input errors==========================
    strError0 = new QLabel("Enter a template name!");
    strError15 = new QLabel("Template name must not exceed 16 characters!");
    strErrorNoItem = new QLabel("Choose apps!");

    strError0->setObjectName("error0");
    strError15->setObjectName("error15");
    strErrorNoItem->setObjectName("errorNoItem");
    //===================================

    m_lst = new ProgramLst(mainWgt);

    QVBoxLayout* box = new QVBoxLayout;
    //temp
    box->addWidget(m_lst);

    box->addStretch();
    box->addWidget(m_lblName);
    box->addWidget(m_lineName);
    box->addWidget(strError0);
    box->addWidget(strError15);
    box->addWidget(strErrorNoItem);
    box->addStretch();
    box->addLayout(btnBox);
    box->addStretch();
    // temp
    setLayout(box);

    // main layout
    //QHBoxLayout* mainBox = new QHBoxLayout;

    //setLayout(mainBox);

    strError0->hide();
    strError15->hide();
    strErrorNoItem->hide();
}

QString WindowCreateTemplate::checkError() {
    strError0->hide();
    strError15->hide();
    strErrorNoItem->hide();
    if (m_lineName->text().size() == 0) {
        strError0->show();
        return "error";
    }
    if (m_lineName->text().size() > 16) {
        strError15->show();
        return "error";
    }
    if (m_lst->isRemoveListEmpty()) {
        strErrorNoItem->show();
        return "error";
    }

    return "";
}

QString WindowCreateTemplate::getTemplateName() {
    return m_lineName->text();
}

void WindowCreateTemplate::setTemplateName(QString str) {
    strError0->hide();
    strError15->hide();
    strErrorNoItem->hide();
    m_lineName->setText(str);
}

void WindowCreateTemplate::slotSendCreateSignal() {
    if (!checkError().isEmpty()) {
        return;
    }

    QPixmap pix = m_lst->getFirstItemPix();
    emit createClicked(pix);
}

void WindowCreateTemplate::showEvent(QShowEvent*) {
    m_lst->getProgramList();
}

void WindowCreateTemplate::hideEvent(QHideEvent*) {
    m_lst->resetLists();
}
