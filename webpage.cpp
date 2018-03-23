#include "webpage.h"

WebPage::WebPage(QTabWidget *parent):
    m_parent(parent),
    m_downloadManager(new DownloadManager)
{
    settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    connect(this, SIGNAL(iconChanged(QIcon)), this, SLOT(changeIcon(QIcon)));
    connect(this, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
    connect(this, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));
    connect(page(), SIGNAL(fullScreenRequested(QWebEngineFullScreenRequest)), this, SLOT(setFullScreen(QWebEngineFullScreenRequest)));
    connect(page()->profile(), SIGNAL(downloadRequested(QWebEngineDownloadItem*)), m_downloadManager, SLOT(downloadItem(QWebEngineDownloadItem*)));
    connect(this, SIGNAL(loadProgress(int)), (MainWindow*)m_parent->parent(), SLOT(checkForwardBack()));
}

void WebPage::urlCheck(QString &url)
{
    if(QRegularExpression(" ").match(url).hasMatch())
        url = "https://www.duckduckgo.com/?q=" + url;
    else if(!QRegularExpression("(https?|ftp|file)://").match(url).hasMatch())
        url = "http://" + url;
}

void WebPage::changeIcon(QIcon icon)
{
    m_parent->setTabIcon(m_parent->indexOf(this), icon);
}

void WebPage::changeTitle(QString title)
{
    m_parent->setTabText(m_parent->indexOf(this), title);
}

void WebPage::changeUrl(QUrl url)
{
    if(m_parent->indexOf(this) == m_parent->currentIndex())
        ((MainWindow *)m_parent->parentWidget())->changeUrlField(url.toString());
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
    MainWindow *parent = (MainWindow*) m_parent->parentWidget();
    if(request.toggleOn() && parent->isFullScreen()){
        qDebug("Already fullscreen");
        request.reject();
        return;
    }
    if(request.toggleOn()) {
        m_parent->tabBar()->hide();

        parent->menuBar()->hide();
        parent->statusBar()->hide();
        parent->hideToolBar();
        parent->showFullScreen();

        request.accept();
    }
    else {
        m_parent->tabBar()->show();

        parent->menuBar()->show();
        parent->statusBar()->show();
        parent->showToolBar();
        parent->showMaximized();

        request.accept();
    }
}
