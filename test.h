#ifndef TEST_H
#define TEST_H

#include <QWidget>

#include <QtWidgets>

class test1 : public QWidget {
    Q_OBJECT
public:
    test1(QWidget* wgt = 0);

private:
    QPushButton* btn1;
    QPushButton* btn2;
    QLabel* lbl1;
    QLabel* lbl2;
    bool temp;

private slots:
    void slotChangeLbl1();
    void slotChangeLbl2();
};

#endif // TEST_H
