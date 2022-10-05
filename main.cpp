#include "mainwindwow.h"
#include "btnarea.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    mainWindwow window;

    QLabel* spacing1 = new QLabel("spacing");
    window.addWidget(spacing1, 0,0,4,3);

    btnArea* areaBtn = new btnArea;
    window.addWidget(areaBtn, 1, 3, 2, 1);


    window.setFixedSize(QSize(800,600));
    window.show();

    QApplication::setQuitOnLastWindowClosed(false);

    return app.exec();
}
