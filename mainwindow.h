#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "webpage.h"
#define HOME_URL "http://www.lebbadi.fr"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    WebPage* currentPage();

public slots:
    void addTab();
    void removeTab(int index=-1);
    void changeUrlField(QString newText);
    void askLoad(QString url = 0);
    void askGoHome();
    void askReload();
    void checkForwardBack();
    void askGoBack();
    void askGoForward();
    void hideToolBar();
    void showToolBar();

signals:

private:
    QTabWidget *m_tabs;

    QAction *m_addTab;
    QAction *m_deleteTab;
    QAction *m_quit;

    QToolBar *m_toolBar;

    QAction *m_previousPage;
    QAction *m_nextPage;
    QAction *m_reload;
    QAction *m_home;
    QLineEdit *m_urlField;
    QAction *m_load;

    QAction *m_aboutMyChrome;
    QAction *m_aboutQt;

    QProgressBar *m_progress;
};

#endif // MAINWINDOW_H
