#include "mainwindow.h"
#include "webpage.h"
#include "downloadmanager.h"

#include <QTabWidget>
#include <QWebEngineSettings>
#include <QWebEnginePage>
#include <QWebEngineFullScreenRequest>
#include <QWebEngineProfile>
#include <QMenuBar>
#include <QStatusBar>
#include <QTabBar>
#include <QDialog>
#include <QVBoxLayout>


WebPage::WebPage(QWidget *parent, QWebEnginePage::WebWindowType page_type): QWebEngineView(parent), type(page_type)
{
    settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);

    connect(this, &QWebEngineView::iconChanged, this, &WebPage::changeIcon);
    connect(this, &QWebEngineView::titleChanged, this, &WebPage::changeTitle);
    connect(this, &QWebEngineView::urlChanged, this, &WebPage::changeUrl);
    connect(page(), &QWebEnginePage::fullScreenRequested, this, &WebPage::setFullScreen);
    connect(page()->profile(), &QWebEngineProfile::downloadRequested, mainWindow()->downloadManager(), &DownloadManager::downloadItem);
    connect(this, &QWebEngineView::loadProgress, mainWindow(), &MainWindow::checkForwardBack);
}

WebPage* WebPage::createWindow(QWebEnginePage::WebWindowType page_type)
{
    QDialog* dialog;
    WebPage* page;
    switch (page_type) {
    case QWebEnginePage::WebBrowserWindow:
        return (new MainWindow())->currentPage();
        break;
    case QWebEnginePage::WebBrowserTab:
        return mainWindow()->addTab();
        break;
    case QWebEnginePage::WebDialog:
        dialog = new QDialog(mainWindow());
        dialog->setLayout(new QVBoxLayout());
        page = new WebPage(mainWindow(), page_type);
        layout()->addWidget(page);
        return page;
        break;
    case QWebEnginePage::WebBrowserBackgroundTab:
        return mainWindow()->addTab(0);
        break;
    }
    return nullptr;
}

MainWindow* WebPage::mainWindow() const
{
    return qobject_cast<MainWindow*>(parentWidget()->parentWidget());
}

QTabWidget* WebPage::tabs() const
{
    if(type == QWebEnginePage::WebBrowserTab)
        return qobject_cast<QTabWidget*>(parentWidget());
    return nullptr;
}

void WebPage::changeTitle(const QString &title)
{
    if(tabs())
        tabs()->setTabText(tabs()->indexOf(this), title);
}

void WebPage::changeIcon(QIcon icon)
{
    if(tabs())
    tabs()->setTabIcon(tabs()->indexOf(this), icon);
}

void WebPage::changeUrl(QUrl url)
{
    if(!tabs())
        return;
    if(tabs()->indexOf(this) == tabs()->currentIndex())
        mainWindow()->changeUrlField(url.toString());
}

void WebPage::setFullScreen(QWebEngineFullScreenRequest request)
{

    if(request.toggleOn() && (mainWindow()->isFullScreen() || parentWidget()->isFullScreen())){
        qDebug("Already fullscreen");
        request.reject();
        return;
    }
    if(request.toggleOn()) {
        if(type == QWebEnginePage::WebBrowserTab) {
            qobject_cast<QTabWidget*>(parentWidget())->tabBar()->hide();

            mainWindow()->menuBar()->hide();
            mainWindow()->statusBar()->hide();
            mainWindow()->hideToolBar();
            mainWindow()->showFullScreen();
        }
        else {
            parentWidget()->showFullScreen();
        }

        request.accept();
    }
    else {
        if(type == QWebEnginePage::WebBrowserTab) {
            qobject_cast<QTabWidget*>(parentWidget())->tabBar()->show();

            mainWindow()->menuBar()->show();
            mainWindow()->statusBar()->show();
            mainWindow()->showToolBar();
            mainWindow()->showMaximized();
        }
        else {
            parentWidget()->showFullScreen();
        }

        request.accept();
    }
}
