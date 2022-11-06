#include "windowcreatetemplate.h"
#include "programlst.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QSettings>

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

    // button add program to program list
    m_btnAddProgram = new QPushButton("&Add program...");

    connect(m_btnAddProgram, SIGNAL(clicked()),
            SLOT(slotAddProgramToList()));

    QHBoxLayout* btnAddBox = new QHBoxLayout;
    btnAddBox->addWidget(m_btnAddProgram);
    btnAddBox->addStretch();

    // buttons create template or cancel
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

    box->addLayout(btnAddBox);

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

void WindowCreateTemplate::slotAddProgramToList() {
    QStringList listPath = QFileDialog::getOpenFileNames(0,
                                                         "Choose the apps",
                                                         "", "*.exe *.lnk *.url");


    // saving the programs added to the list to the registry
    QSettings settings("5TuleKrisov", "5TemplateApp");

    int i = settings.value("/Settings/size", 0).toInt();
    bool check = 1;

    foreach(QString path, listPath) {
        for (int k = 1; k <= i; ++k) {
            QString str = settings.value(QString("/Settings/%1/Path").arg(k), "").toString();
            if (path == str) {
                check = 0;
            }
        }
    }


    if (check) {
        foreach(QString path, listPath) {
            ++i;
            m_lst->addProgramToAddList(path);
            settings.setValue(QString("/Settings/%1/Path").arg(i), path);
            settings.setValue("/Settings/size", i);
        }
    }
    else {
        // вывести ошибку и предложить дальнейшие действия
    }
    //======================================

}

QFileInfoList WindowCreateTemplate::getListPath() {
    return m_lst->getRemoveListPath();
}
