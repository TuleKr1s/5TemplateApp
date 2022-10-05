#include "mainwindwow.h"
#include "ui_mainwindwow.h"

#include <QBoxLayout>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QPushButton>

mainWindwow::mainWindwow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWindwow) {

    ui->setupUi(this);

    //setWindowFlags(Qt::FramelessWindowHint);
    showSystemTray();

    m_closeWindowBtn = new QPushButton("X");
    m_hideWindowBtn = new QPushButton("-");

    connect(m_closeWindowBtn, SIGNAL(clicked()), this, SLOT(hide()));
    connect(m_hideWindowBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));



    QHBoxLayout* frameBtnBox = new QHBoxLayout;
    frameBtnBox->addWidget(m_hideWindowBtn);
    frameBtnBox->addWidget(m_closeWindowBtn);

    m_mainLayout = new QGridLayout;
    setLayout(m_mainLayout);

    addLayout(frameBtnBox, 0, 3);
}

mainWindwow::~mainWindwow()
{
    delete ui;
}

void mainWindwow::addWidget(QWidget* wgt, int row, int column, int rowSpan, int columnSpan) {
    m_mainLayout->addWidget(wgt, row, column, rowSpan, columnSpan);
    setLayout(m_mainLayout);
}

void mainWindwow::addLayout(QBoxLayout* lay, int row, int column) {
    m_mainLayout->addLayout(lay, row, column);
}

void mainWindwow::showSystemTray() {
    setWindowTitle("5Template");

    QAction* actShowHide    = new QAction("&Show/Hide", this);
    QAction* actQuit        = new QAction("&Quit", this);

    connect(actShowHide, SIGNAL(triggered()), this, SLOT(slotShowHide()));
    connect(actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu* trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(actShowHide);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(actQuit);

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setContextMenu(trayIconMenu);
    m_trayIcon->setToolTip("5Template");
    m_trayIcon->setIcon(QPixmap("C:/Users/TuleKr1s/Downloads/brave_VK7BRanXWH.png"));

    m_trayIcon->show();
}

void mainWindwow::slotShowHide() {
    setVisible(!isVisible());
}

