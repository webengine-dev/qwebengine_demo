#ifndef JSVOTEBRIDGE_H
#define JSVOTEBRIDGE_H

#include <QObject>
#include "vote/SunVoteManager.h"
#include "JSBridgeBase.h"

class JSVoteBridge : public JSBridgeBase, public VoteCallBackBase
{
    Q_OBJECT
public:
    explicit JSVoteBridge(QObject *parent = nullptr);
    void init() override;

    void onConnectEventCallBack(bool ok) override;

private:
    void anyAnswer(const QVariantMap& args, const QString& callbackId);
    void connect(const QVariantMap& args, const QString& callbackId);
};

#endif // JSVOTEBRIDGE_H
