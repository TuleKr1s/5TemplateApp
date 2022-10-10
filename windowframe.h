#ifndef WINDOWFRAME_H
#define WINDOWFRAME_H

#include <QWidget>

class QPushButton;
class QHBoxLayout;

class WindowFrame : public QWidget
{
    Q_OBJECT
public:
    WindowFrame(QWidget* wgt = 0);

    QPoint getPrevPos();

private:
    QWidget* mainWgt;

    QPushButton* m_btnShowMinimize;
    QPushButton* m_btnShowMaximize;
    QPushButton* m_btnClose;

    QHBoxLayout* m_mainBox;

    QPoint m_prevPos;

protected:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

private slots:
    void slotMinimized();
    void slotClose();
    void slotSetPrevPos(QPoint prevPos);
};

#endif // WINDOWFRAME_H
