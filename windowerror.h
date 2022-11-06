#ifndef WINDOWERROR_H
#define WINDOWERROR_H

#include <QWidget>

class QPushButton;
class QLabel;
class QHBoxLayout;

class WindowError : public QWidget
{
    Q_OBJECT
public:
    enum flags {
        BTN_OK,
        BTN_CANCEL,
        BTN_ALL
    };

    WindowError(QWidget* wgt = 0, flags flag = BTN_ALL);

    void setFlag(flags);
    void setText(QString);

private:
    QWidget* mainWgt;
    QWidget* temp;

    flags m_currentFlag;

    QLabel* m_text;

    QPushButton* m_btnOk;
    QPushButton* m_btnCancel;

    QHBoxLayout* m_btnBox;

protected:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void keyPressEvent(QKeyEvent*);

private slots:
    void slotChangeFlag();

signals:
    void flagChanged();
    void clickedOk();
    void clickedCancel();
};

#endif // WINDOWERROR_H
