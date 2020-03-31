#include "WebUI.h"
#include <qwebenginescript.h>
#include <QtWebChannel>
#include <QWebEngineScriptCollection>
#include <QWebEngineSettings>

void WebUI::init() {//add new functions here
    m_handlerMap["normal"] = &WebUI::normalWindow;
    m_handlerMap["minimize"] = &WebUI::minimizeWindow;
    m_handlerMap["maximize"] = &WebUI::maximizeWindow;
}

void WebUI::normalWindow(const QVariantMap& args, const QString& callbackId) {
    Q_UNUSED(args);
    showNormal();
    respone(callbackId, QVariantMap());
}

void WebUI::minimizeWindow(const QVariantMap &args, const QString &callbackId) {
    Q_UNUSED(args);
    showMinimized();
    respone(callbackId, QVariantMap());
}

void WebUI::maximizeWindow(const QVariantMap &args, const QString &callbackId) {
    Q_UNUSED(args);
    showMaximized();
    respone(callbackId, QVariantMap());
}

WebUI::WebUI(QWidget* parent):
    QWebEngineView (parent) {
    init();

    m_JSBridge = new JSBridge(this);
    QWebChannel* webChannel = new QWebChannel(this);
    webChannel->registerObject("nativeBridge", m_JSBridge);
    page()->setWebChannel(webChannel);

    InjectJsFile(":/resource/js/qwebchannel");
    InjectJsFile(":/resource/js/bridge");

    //setContextMenuPolicy(Qt::NoContextMenu);
    //page()->setBackgroundColor(Qt::transparent);

    QWebEngineSettings* setting = page()->settings();
    setting->setAttribute(QWebEngineSettings::WebGLEnabled,true);
}

void WebUI::load(const QUrl &url) {
    if (!m_devWevView) {
        m_devWevView = new QWebEngineView();
        m_devWevView->setMinimumSize(600, 600);
        m_devWevView->show();
    }
    page()->setDevToolsPage(m_devWevView->page());

    QWebEngineView::load(url);
}

void WebUI::request(const QString &cmd, const QVariantMap &args, const QString &jsCallbackId) {
    qDebug()<<"request"<<cmd<<"---"<<jsCallbackId;
    Handler handler = m_handlerMap.value(cmd, nullptr);
    if (handler) {
        (this->*handler)(args, jsCallbackId);
    } else {
        qDebug()<<"!!!error to get function "<<cmd;
    }
}

void WebUI::InvokeJs(const QString &js) {
    QWebEngineScript script;
    script.setSourceCode(js);
    script.setInjectionPoint(QWebEngineScript::DocumentCreation);
    script.setRunsOnSubFrames(true);
    script.setWorldId(QWebEngineScript::MainWorld);
    page()->scripts().insert(script);
}

bool WebUI::InjectJsFile(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        QString result = in.readAll();
        InvokeJs(result);
        file.close();
        return true;
    } else {
        qDebug()<<"error:open file "<<fileName<<"failed!!";
        assert(false);
    }

    return false;
}

void WebUI::respone(const QString& callbackId, const QVariant& result) {
    emit m_JSBridge->respone(callbackId, result);
}

WebUI::~WebUI() {

}

JSBridge::JSBridge(WebUI *ui)
    : QObject(ui), m_WebUI(ui) {
}

JSBridge::~JSBridge() {
}

void JSBridge::request(const QString &cmd, const QVariantMap &args, const QString &jsCallbackId) {
    m_WebUI->request(cmd, args, jsCallbackId);
}
