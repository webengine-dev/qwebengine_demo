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

class ObjectFactory
{
public:
    template<typename T>
    static void registerClass()
    {
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
    }

    static QObject* createObject( const QByteArray& className, QObject* parent = NULL )
    {
        Constructor constructor = constructors().value( className );
        if ( constructor == NULL )
            return NULL;
        return (*constructor)( parent );
    }

private:
    typedef QObject* (*Constructor)( QObject* parent );

    template<typename T>
    static QObject* constructorHelper( QObject* parent )
    {
        return new T( parent );
    }

    static QHash<QByteArray, Constructor>& constructors()
    {
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }
};

class NativeBridge : public QObject {
    Q_OBJECT

public:
    NativeBridge(WebUI *ui);
    ~NativeBridge();

public slots:
    void createObject(const QString &className, const QString &objectId, const QString &jsCallbackId);
    void exec(const QString &objectId, const QString &functionName, const QVariantMap &args, const QString &jsCallbackId);

signals:
    void onCreateObject(const QString &objectId, const QString& callbackId, const QVariant& result);
    void onExec(const QString &objectId, const QVariantMap &args, const QString &jsCallbackId, const QVariant& result=0);
    void onMessage(const QString &objectId, const QVariantMap &args);

private:
    WebUI *m_WebUI;

    QMap<QString, QObject*> m_objects;
};

class Test: public QObject {
   Q_OBJECT
public:
    Test(QObject *parent=0);
    ~Test();

    void TestAPI(const QVariantMap &args,
                 const QString &jsCallbackId);
};

#endif // WEBUI_H
