#include <QApplication>
#include <QtWidgets>

#include "appwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    AppWindow window;

    window.setFixedSize(QSize(800,600));
    window.show();

    return app.exec();
}
