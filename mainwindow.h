#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QProgressBar;
class QLineEdit;
class WebPage;
class DownloadManager;
class QCompleter;

#define HOME_URL "http://www.lebbadi.fr"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    WebPage *currentPage();

public slots:
    WebPage* addTab(bool select = 1);
    void removeTab(int index);
    DownloadManager *downloadManager();
    void showToolBar();
    void hideToolBar();
    void askGoForward();
    void askGoBack();
    void checkForwardBack();
    void askReload();
    void askGoHome();
    void askLoad(const QString & url="");
    void changeUrlField(QString newText);
    void urlSuggest(QString text);

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
    QCompleter *m_urlCompleter;
    QAction *m_load;

    QAction *m_aboutMyChrome;

    QProgressBar *m_progress;
    QAction *m_aboutQt;
    DownloadManager *m_downloadManager;
};

#endif // MAINWINDOW_H
