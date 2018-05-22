#include "mainwindow.h"

MainWindow::MainWindow() :
    m_downloadManager(new DownloadManager),
    m_tabs(new QTabWidget),
    //Init Actions
    //File
    m_addTab(new QAction(tr("Add a Tab"))),
    m_deleteTab(new QAction(tr("Delete current Tab"))),
    m_quit(new QAction(tr("Quit"))),
    //Navigate
    m_previousPage(new QAction(QIcon(":/icones/prec.png"), tr("Previous Page"))),
    m_nextPage(new QAction(QIcon(":/icones/suiv.png"), tr("Next Page"))),
    m_reload(new QAction(QIcon(":/icones/actu.png"), tr("Reload"))),
    m_home(new QAction(QIcon(":/icones/home.png"), tr("Home Page"))),
    m_urlField(new QLineEdit),
    m_load(new QAction(QIcon(":/icones/go.png"), tr("Load the page"))),
    //About
    m_aboutMyChrome(new QAction(tr("About MyChrome"))),
    m_aboutQt(new QAction(tr("About Qt")))

{
    //Init central widget and window settings
    m_tabs->setTabsClosable(true);
    setCentralWidget(m_tabs);
    setWindowIcon(QIcon(":/icones/web.png"));

    //Customizing actions
    m_addTab->setShortcut(QKeySequence(QKeySequence::AddTab));
    m_deleteTab->setShortcut(QKeySequence(QKeySequence::Close));
    m_previousPage->setShortcut(QKeySequence(QKeySequence::Back));
    m_nextPage->setShortcut(QKeySequence(QKeySequence::Forward));
    m_reload->setShortcut(QKeySequence(QKeySequence::Refresh));

    m_previousPage->setEnabled(false);
    m_nextPage->setEnabled(false);

    //Init menus and tool bars
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(m_addTab);
    fileMenu->addAction(m_deleteTab);
    fileMenu->addAction(m_quit);

    QMenu *navigateMenu = menuBar()->addMenu(tr("Navigate"));
    navigateMenu->addAction(m_previousPage);
    navigateMenu->addAction(m_nextPage);
    navigateMenu->addAction(m_reload);
    navigateMenu->addAction(m_home);

    QMenu *aboutMenu = menuBar()->addMenu(tr("About"));
    aboutMenu->addAction(m_aboutMyChrome);
    aboutMenu->addAction(m_aboutQt);

    m_toolBar = addToolBar(tr("Navigate"));
    m_toolBar->addAction(m_previousPage);
    m_toolBar->addAction(m_nextPage);
    m_toolBar->addAction(m_reload);
    m_toolBar->addAction(m_home);
    m_toolBar->addWidget(m_urlField);
    m_toolBar->addAction(m_load);

    //Add status bar
    m_progress = new QProgressBar;
    statusBar()->addPermanentWidget(m_progress, 1);

    connect(m_addTab, SIGNAL(triggered()), this, SLOT(addTab()));
    connect(m_deleteTab, SIGNAL(triggered()), this, SLOT(removeTab()));
    connect(m_tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(removeTab(int)));
    connect(m_quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_reload, SIGNAL(triggered()), this, SLOT(askReload()));
    connect(m_home, SIGNAL(triggered()), this, SLOT(askGoHome()));
    connect(m_urlField, SIGNAL(returnPressed()), this, SLOT(askLoad()));
    connect(m_load, SIGNAL(triggered()), this, SLOT(askLoad()));
    connect(m_aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(m_tabs, SIGNAL(currentChanged(int)), this, SLOT(checkForwardBack()));
    connect(m_previousPage, SIGNAL(triggered()), this, SLOT(askGoBack()));
    connect(m_nextPage, SIGNAL(triggered()), this, SLOT(askGoForward()));

    //Add first tab
    addTab();
}

WebPage* MainWindow::currentPage() const
{
    return (WebPage*)m_tabs->currentWidget();
}

DownloadManager* MainWindow::downloadManager() const
{
    return m_downloadManager;
}

void MainWindow::addTab()
{
    WebPage *page = new WebPage(m_tabs);
    m_tabs->addTab(page, tr("Tab"));
    m_tabs->setCurrentIndex(m_tabs->indexOf(page));
    page->load(QUrl(HOME_URL));
    connect(page, SIGNAL(loadProgress(int)), m_progress, SLOT(setValue(int)));
}

void MainWindow::removeTab(int index)
{
    if(m_tabs->count() == 1)
        qApp->quit();
    if(index == -1)
        index = m_tabs->currentIndex();
    m_tabs->removeTab(index);
}

void MainWindow::changeUrlField(QString newText)
{
    m_urlField->setText(newText);
}

void MainWindow::askLoad(QString url)
{
    if(url == 0)
        url = m_urlField->text();
    currentPage()->load(url);
}

void MainWindow::askGoHome()
{
    askLoad(HOME_URL);
}

void MainWindow::askReload()
{
    currentPage()->reload();
}

void MainWindow::checkForwardBack()
{
    m_previousPage->setEnabled(currentPage()->history()->canGoBack());
    m_nextPage->setEnabled(currentPage()->history()->canGoForward());
}

void MainWindow::askGoBack()
{
    currentPage()->history()->back();
}

void MainWindow::askGoForward()
{
    currentPage()->history()->forward();
}

void MainWindow::hideToolBar()
{
    m_toolBar->hide();
}

void MainWindow::showToolBar()
{
    m_toolBar->show();
}
