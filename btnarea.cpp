#include "btnarea.h"

#include <QPushButton>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QBoxLayout>


btnArea::btnArea(QWidget* wgt)
    : QWidget(wgt)
{
    m_launchBtn = new QPushButton("&Launch");
    m_addNewBtn = new QPushButton("&Add new app");

    connect(m_launchBtn, SIGNAL(clicked()), this, SLOT(slotLaunch()));
    connect(m_addNewBtn, SIGNAL(clicked()), this, SLOT(slotAddNew()));



    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(m_launchBtn);
    box->addWidget(m_addNewBtn);
    setLayout(box);
}

void btnArea::slotAddNew() {
    if (m_listApp.empty())
        m_listApp = QFileDialog::getOpenFileNames(0,"Select the apps");
    else
        m_listApp << QFileDialog::getOpenFileName(0, "Select the app");
}

void btnArea::slotLaunch() {

    if (m_listApp.empty()) {
        QMessageBox* messageBox = new QMessageBox(QMessageBox::Information,
                                                  "Error", "Select apps to open",
                                                  QMessageBox::Ok | QMessageBox::Cancel);
        int n = messageBox->exec();
        if (n == QMessageBox::Ok)
            slotAddNew();

    }

    foreach(QString str, m_listApp) {
        QProcess* process = new QProcess(this);
        process->start(str);
        process->waitForStarted();
    }
}













