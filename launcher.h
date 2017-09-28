#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include "mainwindow.h"

class Launcher : public QObject
{
    Q_OBJECT
public:
    Launcher(int argc, char *argv[]);

signals:

public slots:

private:
};

#endif // LAUNCHER_H
