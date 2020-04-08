#include "JSBridgeBase.h"
#include <QDebug>

JSBridgeBase::JSBridgeBase(QObject *parent) : QObject(parent)
{
}

JSBridgeBase::~JSBridgeBase()
{
    m_handlerMap.clear();
}


void JSBridgeBase::request(const QString &cmd, const QVariantMap &args, const QString &jsCallbackId) {
    qDebug()<<"request"<<cmd<<"---"<<jsCallbackId;
    Handler handler = m_handlerMap.value(cmd, nullptr);
    if (handler) {
        (this->*handler)(args, jsCallbackId);
    } else {
        qDebug()<<"!!!error to get function "<<cmd;
    }
}
