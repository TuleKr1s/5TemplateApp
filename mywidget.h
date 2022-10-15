#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(int index, QWidget* wgt = 0);

protected:
    virtual void enterEvent(QEnterEvent*);
    virtual void leaveEvent(QEvent*);

signals:
    void mouseEnter(int index);
    void mouseLeave(int index);

private:
    int m_index;
};

#endif // MYWIDGET_H
