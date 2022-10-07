#include "settingstab.h"

#include <QLabel>
#include <QBoxLayout>

SettingsTab::SettingsTab(QWidget* wgt)
    : QWidget(wgt), mainWgt(wgt)
{

    QLabel* lbl = new QLabel("Settings tab");

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(lbl);
    setLayout(box);
}
