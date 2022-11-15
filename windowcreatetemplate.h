#ifndef WINDOWCREATETEMPLATE_H
#define WINDOWCREATETEMPLATE_H

#include <QWidget>
#include <QFileInfoList>

class QListWidgetItem;
class ProgramLst;
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

    QFileInfoList getListPath();

    QString checkError();

    void hideEvent();
    void showEvent();
private:
    QWidget* mainWgt;

    QLineEdit* m_lineName;
    QLabel* m_lblName;

    QPushButton* m_btnAddProgram;

    QPushButton* m_btnCreate;
    QPushButton* m_btnCancel;

    QLabel* strError0;
    QLabel* strError15;
    QLabel* strErrorNoItem;

    ProgramLst* m_lst;



private slots:
    void slotSendCreateSignal();

    void slotAddProgramToList();

signals:
    void createClicked(QPixmap);
    void cancelClicked();


};

#endif // WINDOWCREATETEMPLATE_H
