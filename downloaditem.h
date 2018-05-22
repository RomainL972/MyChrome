#ifndef DOWNLOADITEM_H
#define DOWNLOADITEM_H

#include <QWebEngineDownloadItem>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QMenu>
#include <QLabel>
#include <QDesktopServices>
#include <QFileInfo>
#include <QUrl>
#include <QMessageBox>

class DownloadItem : public QWidget
{
    Q_OBJECT
public:
    DownloadItem(QWebEngineDownloadItem *origin, QWidget *parent);

signals:

public slots:
    void displayProgress(qint64 current, qint64 total);
    void showContextMenu(QPoint pos);
    void open();
    void openInFiles();
    void pauseRequest();
    void displayState(QWebEngineDownloadItem::DownloadState state);

private:
    QWebEngineDownloadItem *m_download;
    QProgressBar *m_progress;
    QVBoxLayout *m_layout;
    QAction *m_pause;
    QLabel *m_state;
};

#endif // DOWNLOADITEM_H
