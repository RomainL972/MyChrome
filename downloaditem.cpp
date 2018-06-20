#include "downloaditem.h"

#include <QDesktopServices>
#include <QFileInfo>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QProgressBar>
#include <QUrl>
#include <QVBoxLayout>
#include <QWebEnginePage>
#include "downloadmanager.h"

DownloadItem::DownloadItem(QWebEngineDownloadItem *origin, QWidget *parent) :
    QWidget(parent),
    m_download(origin),
    m_progress(new QProgressBar),
    m_pause(new QAction(tr("Pause"))),
    m_state(new QLabel)
{
    QLabel *name = new QLabel(QFileInfo(m_download->path()).fileName());

    displayState(download()->state());

    setLayout(new QVBoxLayout);
    layout()->addWidget(progress());
    layout()->addWidget(name);
    layout()->addWidget(state());

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_download, &QWebEngineDownloadItem::downloadProgress, this, &DownloadItem::displayProgress);
    connect(m_download, &QWebEngineDownloadItem::stateChanged, this, &DownloadItem::displayState);
    connect(this, &QWidget::customContextMenuRequested, this, &DownloadItem::showContextMenu);
}

QWebEngineDownloadItem* DownloadItem::download() const
{
    return m_download;
}

QProgressBar* DownloadItem::progress() const
{
    return m_progress;
}

QAction* DownloadItem::pause() const
{
    return m_pause;
}

QLabel* DownloadItem::state() const
{
    return m_state;
}

void DownloadItem::displayProgress(qint64 current, qint64 total)
{
    progress()->setMaximum(total);
    progress()->setValue(current);
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
    QAction *cancel = new QAction(tr("Cancel"));
    QAction *remove = new QAction(tr("Remove"));
    QAction *retry = new QAction(tr("Retry"));

    connect(open, &QAction::triggered, this, &DownloadItem::open);
    connect(openInFiles, &QAction::triggered, this, &DownloadItem::openInFiles);
    connect(m_pause, &QAction::triggered, this, &DownloadItem::pauseRequest);
    connect(cancel, &QAction::triggered, m_download, &QWebEngineDownloadItem::cancel);
    connect(remove, &QAction::triggered, this, &DownloadItem::deleteLater);
    connect(retry, &QAction::triggered, this, &DownloadItem::retryDownload);

    QPoint globalPos = mapToGlobal(pos);

    QMenu contextMenu;

    switch(download()->state()) {
        case QWebEngineDownloadItem::DownloadInProgress:
            contextMenu.addAction(pause());
            contextMenu.addAction(cancel);
        break;
        case QWebEngineDownloadItem::DownloadCancelled:
        case QWebEngineDownloadItem::DownloadInterrupted:
            contextMenu.addAction(retry);
            contextMenu.addAction(remove);
        break;
        case QWebEngineDownloadItem::DownloadCompleted:
            contextMenu.addAction(open);
            contextMenu.addAction(openInFiles);
            contextMenu.addAction(remove);
        break;
        default:
        break;
    }

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
        download()->resume();
        pause()->setText(tr("Pause"));
    }
    else {
        download()->pause();
        pause()->setText(tr("Resume"));
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

void DownloadItem::retryDownload()
{
    QWebEnginePage *downloader = new QWebEnginePage();
    downloader->download(download()->url(), download()->path());
    deleteLater();
}

void DownloadItem::deleteLater()
{
    parentWidget()->layout()->removeWidget(this);
    qobject_cast<DownloadManager*>(parentWidget())->downloads().removeOne(this);
    if(!qobject_cast<DownloadManager*>(parentWidget())->downloads().count())
        parentWidget()->hide();
    QWidget::deleteLater();
}
