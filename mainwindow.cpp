#include "mainwindow.h"

MainWindow::MainWindow()
{
    //Init window settings
    setWindowIcon(QIcon(":/icones/web.png"));

    //Init actions
    m_addTab = new QAction(tr("Add a Tab"));
    m_deleteTab = new QAction(tr("Delete current Tab"));
    m_quit = new QAction(tr("Quit"));

    m_previousPage = new QAction(QIcon(":/icones/prec.png"), tr("Previous Page"));
    m_nextPage = new QAction(QIcon(":/icones/suiv.png"), tr("Next Page"));
    m_reload = new QAction(QIcon(":/icones/actu.png"), tr("Reload"));
    m_home = new QAction(QIcon(":/icones/home.png"), tr("Home Page"));
    m_urlField = new QTextEdit;
    m_load = new QAction(QIcon(":/icones/go.png"), tr("Load the page"));

    m_aboutMyChrome = new QAction(tr("About MyChrome"));
    m_aboutQt = new QAction(tr("About Qt"));

    //Customizing actions
    m_addTab->setShortcut(QKeySequence(QKeySequence::AddTab));
    m_deleteTab->setShortcut(QKeySequence(QKeySequence::Close));
    m_previousPage->setShortcut(QKeySequence(QKeySequence::Back));
    m_nextPage->setShortcut(QKeySequence(QKeySequence::Forward));
    m_reload->setShortcut(QKeySequence(QKeySequence::Refresh));

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

    QToolBar *navigateToolBar = addToolBar(tr("Navigate"));
    navigateToolBar->addAction(m_previousPage);
    navigateToolBar->addAction(m_nextPage);
    navigateToolBar->addAction(m_reload);
    navigateToolBar->addAction(m_home);
    navigateToolBar->addWidget(m_urlField);
    navigateToolBar->addAction(m_load);


}
