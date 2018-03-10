#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QtWidgets>
#include <QtWebEngineWidgets>

class DownloadItem : public QWidget
{
    Q_OBJECT
public:
    DownloadItem(QWebEngineDownloadItem *download);

signals:

public slots:
    void displayProgress(qint64 current, qint64 total);

private:
    QProgressBar *m_progress;
    QWebEngineDownloadItem *m_download;
    QVBoxLayout *m_layout;
};

class DownloadManager : public QWidget
{
    Q_OBJECT
public:
    DownloadManager();

signals:

public slots:
    void downloadItem(QWebEngineDownloadItem *download);

private:
    QList<DownloadItem*> m_downloads;
    QVBoxLayout *m_layout;
};

#endif // DOWNLOADMANAGER_H
