#ifndef WEBUI_H
#define WEBUI_H

#include <QWebEngineView>
#include <QObject>
#include "JSBridgeBase.h"

class JSUIBridge;
class JSVoteBridge;

class WebUI : public QWebEngineView {
    Q_OBJECT

public:
    WebUI(QWidget* parent = nullptr);
    void load(const QUrl & url);
    ~WebUI();

private:
    void InvokeJs(const QString &js);
    bool InjectJsFile(const QString &fileName);

private:
    QWebEngineView *m_devWevView = nullptr;

    JSUIBridge *m_JSUIBridge = nullptr;
    JSVoteBridge *m_JSVoteBridge = nullptr;
};

#endif // WEBUI_H
