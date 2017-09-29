#include "webpage.h"

WebPage::WebPage()
{
    settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    connect(this, SIGNAL(iconChanged(QIcon)), this, SLOT(processIcon(QIcon)));
    connect(this, SIGNAL(titleChanged(QString)), this, SLOT(processTitle(QString)));
    connect(this, SIGNAL(urlChanged(QUrl)), this, SLOT(processUrl(QUrl)));
    connect(page(), SIGNAL(fullScreenRequested(QWebEngineFullScreenRequest)), this, SLOT(setFullScreen(QWebEngineFullScreenRequest)));
}

void WebPage::urlCheck(QString &url)
{
    if(QRegularExpression(" ").match(url).hasMatch())
        url = "https://www.google.com/search#q=" + url;
    else if(!QRegularExpression("(https?|ftp|file)://").match(url).hasMatch())
        url = "http://" + url;
}

void WebPage::processIcon(QIcon icon)
{
    emit reqChangeIcon(icon, this);
}

void WebPage::processTitle(QString title)
{
    emit reqChangeTitle(title, this);
}

void WebPage::processUrl(QUrl url)
{
    emit reqChangeUrlText(url.toString(), this);
}

void WebPage::load(QUrl url)
{
    load(url.toString());
}

void WebPage::load(QString url)
{
    urlCheck(url);
    QWebEngineView::load(QUrl(url));
}

void WebPage::setFullScreen(QWebEngineFullScreenRequest request)
{
    if(request.toggleOn()) {
        setParent(nullptr);
        showFullScreen();
        request.accept();
    }
    else {
        showMaximized();
        emit resetFullscreen(this);
        request.accept();
    }
}
