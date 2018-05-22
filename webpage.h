#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QtWebEngineWidgets>
#include "downloadmanager.h"

class MainWindow;

class WebPage : public QWebEngineView
{
    Q_OBJECT

public:
    WebPage(QTabWidget *parent);
    MainWindow* mainWindow() const;
    QTabWidget* parent() const;

signals:

public slots:
    void changeTitle(QString title);
    void changeUrl(QUrl url);
    void changeIcon(QIcon icon);
    void load(QUrl url);
    void load(QString urlString);
    void setFullScreen(QWebEngineFullScreenRequest request);

private:
};

#include "mainwindow.h"

#endif // WEBPAGE_H
