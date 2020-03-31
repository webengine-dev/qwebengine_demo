#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    m_webUI = new WebUI(this);

    //console page
    QWebEngineView * pdev = new QWebEngineView();
    pdev->setMinimumSize(600, 600);
    pdev->show();
    m_webUI->page()->setDevToolsPage(pdev->page());

    m_webUI->setUrl(QUrl("file:///D:/workspace/code/demos/qwebengine_demo/bin/page/index.html"));
    //m_webUI->setUrl(QUrl("page/index.html"));
}

void MainWindow::resizeEvent(QResizeEvent *) {
    m_webUI->setFixedSize(width(), height());

}

MainWindow::~MainWindow() {

}
