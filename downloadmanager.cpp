#include "downloaditem.h"
#include "downloadmanager.h"

#include <QWebEngineDownloadItem>
#include <QVBoxLayout>

DownloadManager::DownloadManager(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("Downloads"));
    setLayout(new QVBoxLayout);
}

QList<DownloadItem *> DownloadManager::downloads() const
{
    return m_downloads;
}

void DownloadManager::downloadItem(QWebEngineDownloadItem *download)
{
    show();
    DownloadItem *downloadIt = new DownloadItem(download, this);
    layout()->addWidget(downloadIt);
    downloads().append(downloadIt);
    download->accept();
}
