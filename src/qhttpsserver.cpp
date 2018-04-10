/*
 * Copyright 2018 Zakharov Vitaliy <zavitaliy@yandex.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "qhttpsserver.h"

#include "sslserver.h"

QHttpsServer::QHttpsServer(QObject *parent) : QHttpServer(parent)
{
    m_tcpServer = new SslServer(this);
    SslServer *sslServer = static_cast<SslServer*>(m_tcpServer);
    connect(sslServer, SIGNAL(newConnection()),
            this, SLOT(newConnection()));
}

QHttpsServer::~QHttpsServer()
{
}

const QSslCertificate &QHttpsServer::sslLocalCertificate() const
{
    SslServer *sslServer = static_cast<SslServer*>(m_tcpServer);
    return sslServer->sslLocalCertificate();
}

const QSslKey &QHttpsServer::sslPrivateKey() const
{
    SslServer *sslServer = static_cast<SslServer*>(m_tcpServer);
    return sslServer->sslPrivateKey();
}

QSsl::SslProtocol QHttpsServer::sslProtocol() const
{
    SslServer *sslServer = static_cast<SslServer*>(m_tcpServer);
    return sslServer->sslProtocol();
}

void QHttpsServer::setSslLocalCertificate(const QSslCertificate &certificate)
{
    SslServer *sslServer = static_cast<SslServer*>(m_tcpServer);
    sslServer->setSslLocalCertificate(certificate);
}

bool QHttpsServer::setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format)
{
    SslServer *sslServer = static_cast<SslServer*>(m_tcpServer);
    return sslServer->setSslLocalCertificate(path, format);
}

void QHttpsServer::setSslPrivateKey(const QSslKey &key)
{
    SslServer *sslServer = static_cast<SslServer*>(m_tcpServer);
    sslServer->setSslPrivateKey(key);
}

bool QHttpsServer::setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat format, const QByteArray &passPhrase)
{
    SslServer *sslServer = static_cast<SslServer*>(m_tcpServer);
    return sslServer->setSslPrivateKey(fileName, algorithm, format, passPhrase);
}

void QHttpsServer::setSslProtocol(QSsl::SslProtocol protocol)
{
    SslServer *sslServer = static_cast<SslServer*>(m_tcpServer);
    sslServer->setSslProtocol(protocol);
}

bool QHttpsServer::listen(const QHostAddress &address, quint16 port)
{
    SslServer *sslServer = static_cast<SslServer*>(m_tcpServer);
    bool couldBindToPort = sslServer->listen(address, port);
    if (!couldBindToPort) {
        qWarning() << "can't bind to port" << address << port;
    }
    return couldBindToPort;
}
