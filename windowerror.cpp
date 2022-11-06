#include "windowerror.h"

#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QFile>
#include <QApplication>
#include <QFrame>

WindowError::WindowError(QWidget* wgt, flags flag)
    : QWidget(wgt), mainWgt(wgt), m_currentFlag(flag)
{
    setFocus();
    setGeometry(0,0,mainWgt->width(), mainWgt->height());

    // qss
    QFile file(QApplication::applicationDirPath()+"/icons/window error/style.qss");
    file.open(QFile::ReadOnly);
    QString strQss = file.readAll();
    setStyleSheet(strQss);

    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor(0,0,0,75 ));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    // ============== buttons ================
    m_btnOk = new QPushButton("Ok");
    m_btnCancel = new QPushButton("Cancel");

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
    m_text = new QLabel;
    m_text->setText("Unknown error");

    QHBoxLayout* textBox = new QHBoxLayout;
    textBox->addStretch();
    textBox->addWidget(m_text);
    textBox->addStretch();
    //=======================================

    QFrame* line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    // error layout
    QVBoxLayout* errorBox = new QVBoxLayout;
    errorBox->addLayout(textBox);
    errorBox->addWidget(line);
    errorBox->addStretch();
    errorBox->addLayout(m_btnBox);

    //=================== central widget ========================
    temp = new QWidget;
    temp->setFixedSize(300,200);

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
