#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include "downloaditem.h"
#include <QWebEngineDownloadItem>
#include <QVBoxLayout>

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
