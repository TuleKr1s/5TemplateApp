#include <QApplication>
#include <QtWidgets>
#include <QPalette>

#include "maintab.h"
#include "templatewidgetitem.h"
#include "windowframe.h"
#include "templatelist.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QString dirPath = QApplication::applicationDirPath();

    TemplateList wf;
    wf.makeListItem(QPixmap(dirPath+"/icons/template icons/1.png"),
                    QString("Template name"));
    wf.makeListItem(QPixmap(dirPath+"/icons/template icons/1.png"),
                    QString("Template name"));
    wf.show();

    QPalette pal(wf.palette());
    pal.setColor(QPalette::Window, QColor("#121212"));
    wf.setAutoFillBackground(true);
    wf.setPalette(pal);

    return app.exec();
}
