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
    void urlCheck(QString &url);

signals:

public slots:
    void changeTitle(QString title);
    void changeUrl(QUrl url);
    void changeIcon(QIcon icon);
    void load(QUrl url);
    void load(QString url);
    void setFullScreen(QWebEngineFullScreenRequest request);

private:
    DownloadManager *m_downloadManager;
    QTabWidget *m_parent;
};

#include "mainwindow.h"

#endif // WEBPAGE_H
