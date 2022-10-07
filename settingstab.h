#ifndef SETTINGSTAB_H
#define SETTINGSTAB_H

#include <QWidget>

class SettingsTab : public QWidget
{
    Q_OBJECT
public:
    SettingsTab(QWidget* wgt = 0);

private:
    QWidget* mainWgt;
};

#endif // SETTINGSTAB_H
