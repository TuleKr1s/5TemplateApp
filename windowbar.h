#ifndef WINDOWBAR_H
#define WINDOWBAR_H

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class QBoxLayout;

class WindowBar : public QWidget
{
    Q_OBJECT
public:
    WindowBar(QWidget* wgt = 0);

    QHBoxLayout* getLayout();
    QPoint prevPos() const;

private:
    QWidget* mainWgt;

    // Кнопки виджета
    QPushButton* m_btnHide;
    QPushButton* m_btnClose;

    // Компоновка виджета
    QHBoxLayout* m_boxLayout;

    // Предыдущая позиция указателя
    QPoint m_prevPos;

protected:
    virtual void mouseMoveEvent(QMouseEvent* pe);
    virtual void mousePressEvent(QMouseEvent* pe);


public slots:
    void slotSetPrevPos(QPoint prevPos);


signals:
    void prevPosChanged(QPoint prevPos);
};

#endif // WINDOWBAR_H
