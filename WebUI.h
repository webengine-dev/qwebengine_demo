#ifndef WEBUI_H
#define WEBUI_H

#include <QWebEngineView>
#include <QObject>

class JSBridge;

class WebUI : public QWebEngineView {
    Q_OBJECT

    typedef void (WebUI::*Handler)(const QVariantMap& args, const QString& callbackId);

public:
    WebUI(QWidget* parent = nullptr);
    void load(const QUrl & url);
    ~WebUI();

public slots:
    void request(const QString &cmd, const QVariantMap &args, const QString &jsCallbackId);

private:
    void InvokeJs(const QString &js);
    bool InjectJsFile(const QString &fileName);
    void respone(const QString& callbackId, const QVariant& result);
    void init(); //add 1

private slots:
    void normalWindow(const QVariantMap& args, const QString& callbackId);//add 2
    void minimizeWindow(const QVariantMap& args, const QString& callbackId);
    void maximizeWindow(const QVariantMap& args, const QString& callbackId);

private:
    QMap<QString, Handler> m_handlerMap;
    QWebEngineView *m_devWevView = NULL;

    JSBridge *m_JSBridge = NULL;
};

class JSBridge : public QObject {
    Q_OBJECT

public:
    JSBridge(WebUI *ui);
    ~JSBridge();

public slots:
    void request(const QString &cmd, const QVariantMap &args, const QString &jsCallbackId);

signals:
    void respone(const QString& callbackId, const QVariant& result);

private:
    WebUI *m_WebUI;
};

#endif // WEBUI_H
