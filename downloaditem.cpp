#include "downloaditem.h"

DownloadItem::DownloadItem(QWebEngineDownloadItem *origin, QWidget *parent) : QWidget(parent), m_download(origin), m_progress(new QProgressBar)
{
    QLabel *name = new QLabel(m_download->path());
    m_state = new QLabel();

    displayState(m_download->state());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_progress);
    layout->addWidget(name);
    layout->addWidget(m_state);

    setLayout(layout);

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_download, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(displayProgress(qint64,qint64)));
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(m_download, SIGNAL(stateChanged(QWebEngineDownloadItem::DownloadState)), this, SLOT(displayState(QWebEngineDownloadItem::DownloadState)));
}

void DownloadItem::displayProgress(qint64 current, qint64 total)
{
    m_progress->setMaximum(total);
    m_progress->setValue(current);
}

void DownloadItem::showContextMenu(QPoint pos)
{
#ifdef Q_OS_WIN
    QString openInFilesText = tr("Show in Explorer");
#elif Q_OS_MAC
    QString openInFilesText = tr("Reveal in Finder");
#else
    QString openInFilesText = tr("Open in Files");
#endif

    QAction *open = new QAction(tr("Execute"));
    QAction *openInFiles = new QAction(openInFilesText);
    m_pause = new QAction(tr("Pause"));
    QAction *cancel = new QAction(tr("Cancel"));

    connect(open, SIGNAL(triggered()), this, SLOT(open()));
    connect(openInFiles, SIGNAL(triggered()), this, SLOT(openInFiles()));
    connect(m_pause, SIGNAL(triggered()), this, SLOT(pauseRequest()));
    connect(cancel, SIGNAL(triggered()), m_download, SLOT(cancel()));

    QPoint globalPos = mapToGlobal(pos);

    QMenu contextMenu;
    contextMenu.addAction(open);
    contextMenu.addAction(openInFiles);
    contextMenu.addAction(m_pause);
    contextMenu.addAction(cancel);

    contextMenu.exec(globalPos);
}

void DownloadItem::open()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_download->path()));
}

void DownloadItem::openInFiles()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(m_download->path()).canonicalPath()));
}

void DownloadItem::pauseRequest()
{
    if(m_download->isPaused()) {
        m_download->resume();
        m_pause->setText(tr("Pause"));
    }
    else {
        m_download->pause();
        m_pause->setText(tr("Resume"));
    }
}

void DownloadItem::displayState(QWebEngineDownloadItem::DownloadState state)
{
    switch (state) {
    case QWebEngineDownloadItem::DownloadRequested:
        m_state->setText(tr("Starting..."));
        break;
    case QWebEngineDownloadItem::DownloadInProgress:
        m_state->setText(tr("Downloading..."));
        break;
    case QWebEngineDownloadItem::DownloadCompleted:
        m_state->setText(tr("Completed"));
        break;
    case QWebEngineDownloadItem::DownloadCancelled:
        m_state->setText(tr("Canceled"));
        break;
    case QWebEngineDownloadItem::DownloadInterrupted:
        m_state->setText(tr("Interrupted"));
        QMessageBox::warning(this, tr("Download Interrupted"), m_download->interruptReasonString());
    }
}
