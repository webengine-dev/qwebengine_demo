#include "WebUI.h"
#include <qwebenginescript.h>
#include <QtWebChannel>
#include <QWebEngineScriptCollection>
#include <QWebEngineSettings>
#include "vote/JSVoteBridge.h"
#include "JSBridgeBase.h"
#include "JSUIBridge.h"

WebUI::WebUI(QWidget* parent):
    QWebEngineView (parent) {

    QHash<QString, QObject*> channelObjects;

    m_JSUIBridge = new JSUIBridge(this);
    m_JSUIBridge->init();

    m_JSVoteBridge = new JSVoteBridge(this);
    m_JSVoteBridge->init();

    channelObjects.insert("jsBridgeUICef", m_JSUIBridge);
    channelObjects.insert("jsBridgeAnswerCef", m_JSVoteBridge);

    QWebChannel* webChannel = new QWebChannel(this);
    webChannel->registerObjects(channelObjects);
    page()->setWebChannel(webChannel);

    InjectJsFile(":/resource/js/qwebchannel");
    InjectJsFile(":/resource/js/bridge");

    //setContextMenuPolicy(Qt::NoContextMenu);
    //page()->setBackgroundColor(Qt::transparent);

    QWebEngineSettings* setting = page()->settings();
    setting->setAttribute(QWebEngineSettings::WebGLEnabled, true);

    //透明效果
    /*
    page()->setBackgroundColor(Qt::transparent);
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(true);
    setWindowFlags(Qt::FramelessWindowHint);*/
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

WebUI::~WebUI() {

}
