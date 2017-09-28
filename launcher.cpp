#include "launcher.h"

Launcher::Launcher(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    exit(app.exec());
}
