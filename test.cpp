#include "test.h"

#include <QtWidgets>

test1::test1(QWidget* wgt)
    : QWidget(wgt)
{
    lbl1 = new QLabel("lbl1");
    lbl2 = new QLabel("lbl2");
    btn1 = new QPushButton("btn1");
    btn2 = new QPushButton("btn2");
    btn1->setCheckable(true);
    btn2->setCheckable(true);
    connect(btn1, SIGNAL(clicked()), this, SLOT(slotChangeLbl1()));
    connect(btn2, SIGNAL(clicked()), this, SLOT(slotChangeLbl2()));

    QHBoxLayout* btnBox = new QHBoxLayout;
    btnBox->addWidget(btn1);
    btnBox->addWidget(btn2);

    QVBoxLayout* box = new QVBoxLayout;
    box->addLayout(btnBox);
    box->addWidget(lbl1);
    box->addWidget(lbl2);
    slotChangeLbl1();
    setLayout(box);
}
void test1::slotChangeLbl1() {
    btn1->setChecked(true);
    btn2->setChecked(false);
    lbl2->hide();
    lbl1->show();
}

void test1::slotChangeLbl2() {
    btn1->setChecked(false);
    btn2->setChecked(true);
    lbl1->hide();
    lbl2->show();
}
