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


WebPage::WebPage(QWebEnginePage::WebWindowType page_type): type(page_type)
{
    settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);

    connect(this, &QWebEngineView::iconChanged, this, &WebPage::changeIcon);
    connect(this, &QWebEngineView::titleChanged, this, &WebPage::changeTitle);
    connect(this, &QWebEngineView::urlChanged, this, &WebPage::changeUrl);
    connect(page(), &QWebEnginePage::fullScreenRequested, this, &WebPage::setFullScreen);
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
        page = new WebPage(page_type);
        layout()->addWidget(page);
        dialog->show();
        page->load(HOME_URL);
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
    return qobject_cast<MainWindow*>(parentWidget()->parentWidget()->parentWidget());
}

QTabWidget* WebPage::tabs() const
{
    if(type == QWebEnginePage::WebBrowserTab)
        return qobject_cast<QTabWidget*>(parentWidget()->parentWidget());
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
    QTabWidget *parent = tabs();
    if(!parent)
        return;
    if(parent->indexOf(this) == parent->currentIndex())
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

void WebPage::load(const QString &url)
{
    QUrl final = QUrl::fromUserInput(url);
    QWebEngineView::load(final.isEmpty() ? QUrl("https://duckduckgo.com/" + url) : final);
}
