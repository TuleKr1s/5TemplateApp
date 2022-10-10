#include <QApplication>
#include <QtWidgets>

#include "maintab.h"
#include "templatewidgetitem.h"
#include <QPalette>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    TemplateWidgetItem wf;
    wf.show();

    QPalette pal(wf.palette());
    pal.setColor(QPalette::Window, QColor("#121212"));
    wf.setAutoFillBackground(true);
    wf.setPalette(pal);

    return app.exec();
}
