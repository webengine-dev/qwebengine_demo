#ifndef JSBRIDGEBASE_H
#define JSBRIDGEBASE_H

#include <QObject>
#include <QMap>

#define BASEHANDLER void(JSBridgeBase::*)(const QVariantMap& args, const QString& callbackId)

class JSBridgeBase : public QObject
{
    Q_OBJECT

public:
    typedef void (JSBridgeBase::*Handler)(const QVariantMap& args, const QString& callbackId);

    explicit JSBridgeBase(QObject *parent = nullptr);

    virtual ~JSBridgeBase();

protected:
    virtual void init() = 0;

public slots:
    void request(const QString &cmd, const QVariantMap &args, const QString &jsCallbackId);

signals:
    void respone(const QString& callbackId, const QVariant& result);
    void onEvent(const QVariant& result);

protected:
    QMap<QString, Handler> m_handlerMap;
};

#endif // JSBRIDGEBASE_H
