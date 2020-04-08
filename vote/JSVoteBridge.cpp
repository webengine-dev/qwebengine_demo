#include "JSVoteBridge.h"
#include <QVariantMap>
#include <QDebug>

void JSVoteBridge::init()
{
    m_handlerMap["anyAnswer"] = (BASEHANDLER)(&JSVoteBridge::anyAnswer);
    m_handlerMap["connect"] = (BASEHANDLER)(&JSVoteBridge::connect);
}

void JSVoteBridge::anyAnswer(const QVariantMap& args, const QString& callbackId)
{
    Q_UNUSED(args);
    QVariantMap map;
    map.insert("test", 1);
    emit respone(callbackId, map);
}

void JSVoteBridge::connect(const QVariantMap &args, const QString &callbackId)
{
    Q_UNUSED(args);
    SunVoteManager::instance()->setCallBack(this);
    if (!SunVoteManager::instance()->init()) {
        QVariantMap map;
        map.insert("error", "init failed");
        emit respone(callbackId, map);
        return;
    }

    if (!SunVoteManager::instance()->connect()){
        QVariantMap map;
        map.insert("error", "connect failed");
        emit respone(callbackId, map);
        return;
    }
}

void JSVoteBridge::onConnectEventCallBack(bool ok)
{
    qDebug()<<"onConnectEventCallBack:"<<ok<<endl;

    QVariantMap map;
    map.insert("event", "ConnectEvent");
    map.insert("return", ok);
    emit onEvent(map);
}

JSVoteBridge::JSVoteBridge(QObject *parent) : JSBridgeBase(parent)
{
}
