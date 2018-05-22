#include "webpage.h"

WebPage::WebPage(QTabWidget *parent):
    QWebEngineView(parent)
{
    settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    connect(this, SIGNAL(iconChanged(QIcon)), this, SLOT(changeIcon(QIcon)));
    connect(this, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
    connect(this, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));
    connect(page(), SIGNAL(fullScreenRequested(QWebEngineFullScreenRequest)), this, SLOT(setFullScreen(QWebEngineFullScreenRequest)));
    connect(page()->profile(), SIGNAL(downloadRequested(QWebEngineDownloadItem*)), mainWindow()->downloadManager(), SLOT(downloadItem(QWebEngineDownloadItem*)));
    connect(this, SIGNAL(loadProgress(int)), mainWindow(), SLOT(checkForwardBack()));
}

void WebPage::changeIcon(QIcon icon)
{
    parent()->setTabIcon(parent()->indexOf(this), icon);
}

void WebPage::changeTitle(QString title)
{
    parent()->setTabText(parent()->indexOf(this), title);
}

void WebPage::changeUrl(QUrl url)
{
    if(parent()->indexOf(this) == parent()->currentIndex())
        mainWindow()->changeUrlField(url.toString());
}

void WebPage::load(QUrl url)
{
    QWebEngineView::load(url);
}

void WebPage::load(QString urlString)
{
    QUrl url(QUrl::fromUserInput(urlString));
    if(url == QUrl())
        url = QUrl::fromUserInput("duckduckgo.com/" + urlString);
    load(url);
}

void WebPage::setFullScreen(QWebEngineFullScreenRequest request)
{
    MainWindow *main = mainWindow();
    if(request.toggleOn() && main->isFullScreen()){
        qDebug("Already fullscreen");
        request.reject();
        return;
    }
    if(request.toggleOn()) {
        parent()->tabBar()->hide();

        main->menuBar()->hide();
        main->statusBar()->hide();
        main->hideToolBar();
        main->showFullScreen();

        request.accept();
    }
    else {
        parent()->tabBar()->show();

        main->menuBar()->show();
        main->statusBar()->show();
        main->showToolBar();
        main->showMaximized();

        request.accept();
    }
}

MainWindow* WebPage::mainWindow() const
{
    return (MainWindow*)parent()->parent();
}

QTabWidget* WebPage::parent() const
{
    return (QTabWidget*)parent();
}
