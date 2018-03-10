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
    DownloadItem *downloadIt = new DownloadItem(download);
    m_layout->addWidget(downloadIt);
    m_downloads.append(downloadIt);
    download->accept();
}

DownloadItem::DownloadItem(QWebEngineDownloadItem *download) : m_download(download)
{
    m_progress = new QProgressBar;
    QLabel *label = new QLabel(m_download->path());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_progress);
    layout->addWidget(label);

    setLayout(layout);

    connect(m_download, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(displayProgress(qint64,qint64)));
}

void DownloadItem::displayProgress(qint64 current, qint64 total)
{
    m_progress->setMaximum(total);
    m_progress->setValue(current);
}
