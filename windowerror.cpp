#include "windowerror.h"

#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QFile>
#include <QApplication>
#include <QFrame>
#include <QPainter>

WindowError::WindowError(QWidget* wgt, flags flag)
    : QDialog(wgt, Qt::FramelessWindowHint), mainWgt(wgt), m_currentFlag(flag)
{
    setFocus();
    setGeometry(mainWgt->pos().x(),mainWgt->pos().y(),
                mainWgt->width(), mainWgt->height());
    // transparent background
    this->setAttribute(Qt::WA_TranslucentBackground);
    // darkened background
    Background* bg = new Background(this);

    // clickedOk = QDialog::Accept, clickedCancel = QDialog::Reject
    connect(this, SIGNAL(clickedOk()), SLOT(accept()));
    connect(this, SIGNAL(clickedCancel()), SLOT(reject()));

    // qss
    QFile file(QApplication::applicationDirPath()+"/icons/window error/style.qss");
    file.open(QFile::ReadOnly);
    QString strQss = file.readAll();
    setStyleSheet(strQss);



    // ============== buttons ================
    m_btnOk = new QPushButton("Ok");
    m_btnCancel = new QPushButton("Cancel");

    m_btnOk->setObjectName("btnOk");
    m_btnCancel->setObjectName("btnCancel");

    m_btnBox = new QHBoxLayout;
    m_btnBox->addStretch();
    m_btnBox->addWidget(m_btnOk);
    m_btnBox->addWidget(m_btnCancel);

    connect(m_btnOk, SIGNAL(clicked()), SIGNAL(clickedOk()));
    connect(m_btnCancel, SIGNAL(clicked()), SIGNAL(clickedCancel()));

    slotChangeFlag();
    connect(this, SIGNAL(flagChanged()), SLOT(slotChangeFlag()));
    // ====================================

    // ================= error text =====================
    m_title = new QLabel("Error");
    m_title->setObjectName("title");

    m_text = new QLabel("Unknown error");
    m_text->setObjectName("text");
    m_text->setMaximumHeight(65);
    m_text->setWordWrap(true);
    //=======================================

    // error layout
    QVBoxLayout* errorBox = new QVBoxLayout;
    errorBox->setContentsMargins(0,0,0,0);
    errorBox->addWidget(m_title);
    errorBox->addSpacing(5);
    errorBox->addWidget(m_text);
    errorBox->addStretch();
    errorBox->addLayout(m_btnBox);

    //=================== central widget ========================
    temp = new QWidget;
    temp->setObjectName("central");
    temp->setFixedSize(400,200);
    temp->setStyleSheet("QWidget#central {"
                        "background-image: url("+
                        QApplication::applicationDirPath()+
                        "/icons/window error/error image black.png);"
                        "}");

    QPalette palette(temp->palette());
    palette.setColor(QPalette::Window, QColor("#080808"));
    temp->setAutoFillBackground(true);
    temp->setPalette(palette);

    temp->setLayout(errorBox);
    // ===================================================

    QHBoxLayout* hBox = new QHBoxLayout;
    hBox->addStretch();
    hBox->addWidget(temp);
    hBox->addStretch();

    QVBoxLayout* vBox = new QVBoxLayout;
    vBox->addStretch();
    vBox->addLayout(hBox);
    vBox->addStretch();
    setLayout(vBox);

}

void WindowError::setFlag(flags flag) {
    m_currentFlag = flag;
    emit flagChanged();
}

void WindowError::slotChangeFlag() {
    m_btnCancel->hide();
    m_btnOk->hide();
    switch(m_currentFlag) {
    case BTN_OK:
        m_btnOk->show();
        break;
    case BTN_CANCEL:
        m_btnCancel->show();
        break;
    case BTN_ALL:
        m_btnOk->show();
        m_btnCancel->show();
        break;
    }
}

void WindowError::setText(QString str) {
    m_text->setText(str);
}

void WindowError::setTitle(QString str) {
    m_title->setText(str);
}

void WindowError::mousePressEvent(QMouseEvent* me) {
    if(!(me->pos().x() > temp->pos().x() && me->pos().y() > temp->pos().y()
            && me->pos().x() < temp->pos().x()+temp->width()
            && me->pos().y() < temp->pos().y()+temp->height()))
    {
        emit clickedCancel();
    }
    QWidget::mousePressEvent(me);
}

void WindowError::keyPressEvent(QKeyEvent* ke) {
    switch(ke->key()) {
    case Qt::Key_Escape:
        emit clickedCancel();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        emit clickedOk();
        break;
    default:
        QWidget::keyPressEvent(ke);
    }
}

