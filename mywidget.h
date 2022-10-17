#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(int index, QWidget* wgt = 0);

    int getIndex();
    void setIndex(int index);
protected:
    virtual void enterEvent(QEnterEvent*);
    virtual void leaveEvent(QEvent*);

signals:
    void mouseEnter();
    void mouseLeave();

private:
    int m_index;
};

#endif // MYWIDGET_H
