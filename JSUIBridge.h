#ifndef JSUIBRIDGE_H
#define JSUIBRIDGE_H

#include <QObject>
#include "JSBridgeBase.h"

class WebUI;
class JSUIBridge : public JSBridgeBase
{
    Q_OBJECT
public:
    JSUIBridge(WebUI *ui);
    ~JSUIBridge() override;

    void init() override;

private slots:
    void normalWindow(const QVariantMap& args, const QString& callbackId);
    void minimizeWindow(const QVariantMap& args, const QString& callbackId);
    void maximizeWindow(const QVariantMap& args, const QString& callbackId);

private:
    WebUI *m_WebUI;
};

#endif // JSUIBRIDGE_H
