#include "maintab.h"

#include <QLabel>
#include <QBoxLayout>

MainTab::MainTab(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{
    QLabel* lbl = new QLabel("Main tab");

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(lbl);
    setLayout(box);
}
