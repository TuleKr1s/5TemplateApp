#ifndef WINDOWCREATETEMPLATE_H
#define WINDOWCREATETEMPLATE_H

#include <QWidget>

class QLineEdit;
class QLabel;
class QPushButton;

class WindowCreateTemplate : public QWidget
{
    Q_OBJECT
public:
    WindowCreateTemplate(QWidget* wgt = 0);

    QString getTemplateName();
    void setTemplateName(QString);
private:
    QWidget* mainWgt;

    QLineEdit* m_lineName;
    QLabel* m_lblName;


    QPushButton* m_btnCreate;
    QPushButton* m_btnCancel;

    QLabel* strError0;
    QLabel* strError15;

signals:
    void createClicked();
    void cancelClicked();

};

#endif // WINDOWCREATETEMPLATE_H
