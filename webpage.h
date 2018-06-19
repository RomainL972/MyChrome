#ifndef WEBPAGE_H
#define WEBPAGE_H


#include <QIcon>
#include <QWebEngineFullScreenRequest>
#include <QWebEngineView>
class QTabWidget;
class MainWindow;

class WebPage : public QWebEngineView
{
    Q_OBJECT
public:
    WebPage(QWebEnginePage::WebWindowType page_type = QWebEnginePage::WebBrowserTab);
    WebPage* createWindow(QWebEnginePage::WebWindowType page_type);
    MainWindow* mainWindow() const;
    QTabWidget* tabs() const;

public slots:
    void changeTitle(const QString &title);
    void changeIcon(QIcon icon);
    void changeUrl(QUrl url);
    void setFullScreen(QWebEngineFullScreenRequest request);
    void load(const QString &url);
private:
    QWebEnginePage::WebWindowType type;
};

#endif // WEBPAGE_H
