#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtWebEngineWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:

signals:

private:
    QAction *m_addTab;
    QAction *m_deleteTab;
    QAction *m_quit;

    QAction *m_previousPage;
    QAction *m_nextPage;
    QAction *m_reload;
    QAction *m_home;
    QTextEdit *m_urlField;
    QAction *m_load;

    QAction *m_aboutMyChrome;
    QAction *m_aboutQt;
};

#endif // MAINWINDOW_H
