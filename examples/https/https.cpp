#include "https.h"

#include <QCoreApplication>

#include <qhttprequest.h>
#include <qhttpresponse.h>
#include <qhttpsserver.h>

/// HelloWorld

HttpsHelloWorld::HttpsHelloWorld()
{
    QHttpsServer *server = new QHttpsServer(this);
    server->setSslPrivateKey(QString(":/localhost.key"));
    server->setSslLocalCertificate(QString(":/localhost.pem"));
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handleRequest(QHttpRequest*, QHttpResponse*)));

    quint16 port = 8888;
    if (server->listen(QHostAddress::LocalHost, port))
        qDebug() << "https server started on port" << port;
}

void HttpsHelloWorld::handleRequest(QHttpRequest *req, QHttpResponse *resp)
{
    Q_UNUSED(req);

    QByteArray body = "Hello World " + req->url().path().toUtf8();
    resp->setHeader("Content-Length", QString::number(body.size()));
    resp->writeHead(200);
    resp->end(body);
}

/// main

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    HttpsHelloWorld hello;
    app.exec();
}
