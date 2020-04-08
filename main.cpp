#include "MainWindow.h"
#include <QApplication>
#include <QTextDecoder>

#include <Windows.h>

#include <tchar.h>
#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <QDir>
#include <QTextStream>
#include <DbgHelp.h>

#include <QWebEngineSettings>

int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers)
{
    typedef BOOL(WINAPI * MiniDumpWriteDumpT)(
                HANDLE,
                DWORD,
                HANDLE,
                MINIDUMP_TYPE,
                PMINIDUMP_EXCEPTION_INFORMATION,
                PMINIDUMP_USER_STREAM_INFORMATION,
                PMINIDUMP_CALLBACK_INFORMATION
                );
    MiniDumpWriteDumpT pfnMiniDumpWriteDump = NULL;
    HMODULE hDbgHelp = LoadLibrary(_T("DbgHelp.dll"));

    if (NULL == hDbgHelp)
    {
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    pfnMiniDumpWriteDump = (MiniDumpWriteDumpT)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
    if (NULL == pfnMiniDumpWriteDump)
    {
        FreeLibrary(hDbgHelp);
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    TCHAR szFileName[MAX_PATH] = { 0 };
    TCHAR szVersion[] = L"DumpFile";
    SYSTEMTIME stLocalTime;
    GetLocalTime(&stLocalTime);
    wsprintf(szFileName, L"../log/%s-%04d-%02d-%02d-%02d%02d%02d.dmp",
             szVersion, stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
             stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond);

    HANDLE hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
                                  FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
    if (INVALID_HANDLE_VALUE == hDumpFile)
    {
        FreeLibrary(hDbgHelp);
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    MINIDUMP_EXCEPTION_INFORMATION expParam;
    expParam.ThreadId = GetCurrentThreadId();
    expParam.ExceptionPointers = pExceptionPointers;
    expParam.ClientPointers = FALSE;
    pfnMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
                         hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &expParam : NULL), NULL, NULL);

    CloseHandle(hDumpFile);
    FreeLibrary(hDbgHelp);
    return EXCEPTION_EXECUTE_HANDLER;
}

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
    if (IsDebuggerPresent())
    {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    return GenerateMiniDump(lpExceptionInfo);
}

extern "C" void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }
    /* The QMessageLogContext class provides additional information about a log message.
    The class provides information about the source code location a qDebug(), qInfo(), qWarning(), qCritical() or qFatal() message was generated.
    Note: By default, this information is recorded only in debug builds. You can overwrite this explicitly by defining QT_MESSAGELOGCONTEXT or QT_NO_MESSAGELOGCONTEXT
    */
    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(current_date).arg(msg);

    QDir dirLog = QCoreApplication::applicationDirPath();
#ifdef Q_OS_MACOS
    dirLog.cdUp();
#endif
    dirLog.cdUp();
    QString strLogPath = dirLog.absolutePath() + QString("/log");
    if(!dirLog.exists(strLogPath))
    {
        dirLog.mkdir(strLogPath);
    }
    dirLog.cd("log");
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString strLogFile = dirLog.absoluteFilePath(QString("log_")+currentTime+QString(".txt"));
    QFile file(strLogFile);
    file.open(QIODevice::WriteOnly| QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream.setCodec("utf-8");
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}

int main(int argc, char *argv[]) {
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--process-per-tab");
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--disable-pinch");

#ifdef Q_OS_WIN
    SetUnhandledExceptionFilter(ExceptionFilter);
#endif

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    char cmdGpub[30] = "--ignore-gpu-blacklist";
    for(int i = argc; i > 1; i--)
    {
        argv[i] = argv[i-1];
    }
    argv[1] = cmdGpub;
    argc++;

    QApplication a(argc, argv);

    //a.setQuitOnLastWindowClosed(false);
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(codec);

#ifndef QT_NO_DEBUG
    qInstallMessageHandler(outputMessage);
#endif

    QWebEngineSettings* setting = QWebEngineSettings::defaultSettings();
    setting->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    setting->setAttribute(QWebEngineSettings::AutoLoadImages, true);
    setting->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    setting->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    setting->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard, true);
    setting->setAttribute(QWebEngineSettings::LinksIncludedInFocusChain, true);
    setting->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    setting->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    setting->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
    setting->setAttribute(QWebEngineSettings::WebGLEnabled,true);

    WebUI w;
    w.setMinimumSize(800, 800);
    w.show();
    //QString path = "file:///" + QCoreApplication::applicationDirPath() + "/H5/garden_radish/v4.1/teacher.html";
    QString path = "file:///" + QCoreApplication::applicationDirPath() + "/page/index.html";
    w.load(QUrl(path));

    return a.exec();
}
