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

    ObjectFactory::registerClass<Test>();

    //m_JSBridge = new JSBridge(this);
    NativeBridge *bridge = new NativeBridge(this);
    QWebChannel* webChannel = new QWebChannel(this);
    //webChannel->registerObject("nativeBridge", m_JSBridge);
    webChannel->registerObject("nativeBridge", bridge);
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

NativeBridge::NativeBridge(WebUI *ui): m_WebUI(ui)
{

}

NativeBridge::~NativeBridge()
{

}

void NativeBridge::createObject(const QString &className, const QString &objectId, const QString &jsCallbackId)
{
   QObject* object = ObjectFactory::createObject(className);
   int ret = 0;
   if (!object) {
       ret = -1;
       qDebug()<<"createObject faild"<<className<<objectId<<jsCallbackId;
   } else {
       m_objects[objectId] = object;
   }
   emit onCreateObject(objectId, jsCallbackId, ret);
}

void NativeBridge::exec(const QString &objectId, const QString &functionName, const QVariantMap &args,
                        const QString &jsCallbackId)
{
    QObject *obj = m_objects[objectId];
    if (!obj) {
        qDebug()<<"exec faild"<<objectId<<functionName<<jsCallbackId;
    }


    QVariantMap retVal;
    bool ret = QMetaObject::invokeMethod(obj, functionName, Qt::DirectConnection,
                              Q_RETURN_ARG(QVariantMap, retVal),
                              Q_ARG(QVariantMap, QVariantMap),
                              Q_ARG(QString, jsCallbackId),
                              Q_ARG((void*), [objectId, jsCallbackId](QVariantMap args) {
        emit onExec(objectId, args, jsCallbackId, 0);
    }));

    if (!ret) {
        emit onExec(objectId, retVal, jsCallbackId, -1);
    }
}

Test::Test()
{

}

Test::~Test()
{

}
