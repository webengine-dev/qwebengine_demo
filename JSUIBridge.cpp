#include "JSUIBridge.h"
#include "WebUI.h"

void JSUIBridge::init() {
    m_handlerMap["normal"] = (BASEHANDLER)(&JSUIBridge::normalWindow);
    m_handlerMap["minimize"] = (BASEHANDLER)(&JSUIBridge::minimizeWindow);
    m_handlerMap["maximize"] = (BASEHANDLER)(&JSUIBridge::maximizeWindow);
}

void JSUIBridge::normalWindow(const QVariantMap& args, const QString& callbackId) {
    Q_UNUSED(args);
    m_WebUI->showNormal();
    respone(callbackId, QVariantMap());
}

void JSUIBridge::minimizeWindow(const QVariantMap &args, const QString &callbackId) {
    Q_UNUSED(args);
    m_WebUI->showMinimized();
    respone(callbackId, QVariantMap());
}

void JSUIBridge::maximizeWindow(const QVariantMap &args, const QString &callbackId) {
    Q_UNUSED(args);
    m_WebUI->showMaximized();
    respone(callbackId, QVariantMap());
}

JSUIBridge::JSUIBridge(WebUI *ui)
    : JSBridgeBase(ui), m_WebUI(ui) {
}

JSUIBridge::~JSUIBridge() {
}
