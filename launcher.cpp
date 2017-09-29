#include "launcher.h"

Launcher::Launcher(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.showMaximized();
    exit(app.exec());
}
