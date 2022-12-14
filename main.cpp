#include <QApplication>
#include <QtWidgets>
#include <QPalette>
#include <vector>

#include "maintab.h"
#include "windowframe.h"
#include "templatelist.h"
#include "windowcreatetemplate.h"
#include "application.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    Application wf;
    wf.show();

    QPalette pal(wf.palette());
    pal.setColor(QPalette::Window, QColor("#121212"));
    wf.setAutoFillBackground(true);
    wf.setPalette(pal);


    return app.exec();
}
