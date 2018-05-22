#include "downloadmanager.h"

DownloadManager::DownloadManager()
{
    setWindowTitle(tr("Downloads"));
    m_layout = new QVBoxLayout;
    setLayout(m_layout);
}

void DownloadManager::downloadItem(QWebEngineDownloadItem *download)
{
    show();
    DownloadItem *downloadIt = new DownloadItem(download, this);
    m_layout->addWidget(downloadIt);
    m_downloads.append(downloadIt);
    download->accept();
}
