#include <QtGui>
#include <QMessageBox>
#include <QApplication>


#include "window.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(timetracker);

    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Time tracker"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    Window window;
    window.show();
    return app.exec();
}
