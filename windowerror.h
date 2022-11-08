#ifndef WINDOWERROR_H
#define WINDOWERROR_H

#include <QWidget>
#include <QDialog>

class QPushButton;
class QLabel;
class QHBoxLayout;

class WindowError : public QDialog
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
    void setTitle(QString);

private:
    QWidget* mainWgt;
    QWidget* temp;

    flags m_currentFlag;

    QLabel* m_title;
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


class Background : public QWidget {
    Q_OBJECT
public:
    Background(QWidget* wgt = 0)
        : QWidget(wgt), mainWgt(wgt)
    {
        setGeometry(0,0,mainWgt->width(),
                    mainWgt->height());
        QPalette pal(this->palette());
        pal.setColor(QPalette::Window,
                     QColor(0,0,0,100));
        setAutoFillBackground(true);
        setPalette(pal);

    }

private:
    QWidget* mainWgt;
};


#endif // WINDOWERROR_H
