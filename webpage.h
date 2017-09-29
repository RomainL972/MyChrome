#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QtWebEngineWidgets>

class WebPage : public QWebEngineView
{
    Q_OBJECT

public:
    WebPage();
    void urlCheck(QString &url);

signals:
    void reqChangeTitle(QString newTitle, WebPage *sender);
    void reqChangeUrlText(QString newUrlText, WebPage *sender);
    void reqChangeIcon(QIcon newIcon, WebPage *sender);
    void resetFullscreen(QWidget *currentWidget);

public slots:
    void processTitle(QString title);
    void processUrl(QUrl url);
    void processIcon(QIcon icon);
    void load(QUrl url);
    void load(QString url);
    void setFullScreen(QWebEngineFullScreenRequest request);

private:
};

#endif // WEBPAGE_H
