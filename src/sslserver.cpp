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

#include "SslServer.h"

#include <QFile>
#include <QSslSocket>

SslServer::SslServer(QObject *parent) : QTcpServer(parent),
    m_sslLocalCertificate(),
    m_sslPrivateKey(),
    m_sslProtocol(QSsl::AnyProtocol)
{
}

void SslServer::incomingConnection(qintptr socketDescriptor)
{
    // Create socket
    QSslSocket *sslSocket = new QSslSocket(this);
    sslSocket->setLocalCertificate(m_sslLocalCertificate);
    sslSocket->setPrivateKey(m_sslPrivateKey);
    sslSocket->setProtocol(m_sslProtocol);

    if (!sslSocket->setSocketDescriptor(socketDescriptor)) {
        qWarning() << "can't set socket descriptor" << sslSocket->errorString();
        delete sslSocket;
        return;
    }

    QList<QSslError> expectedSslErrors;
    expectedSslErrors.append(QSslError(QSslError::SelfSignedCertificate,m_sslLocalCertificate));
    expectedSslErrors.append(QSslError(QSslError::HostNameMismatch, m_sslLocalCertificate));
    sslSocket->ignoreSslErrors(expectedSslErrors);

    connect(sslSocket, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(socketSslErrors(QList<QSslError>)));
    connect(sslSocket, SIGNAL(peerVerifyError(QSslError)),
            this, SLOT(socketPeerVerifyError(QSslError)));

    // Add to the internal list of pending connections (see Qt doc: http://qt-project.org/doc/qt-5/qtcpserver.html#addPendingConnection)
    this->addPendingConnection(sslSocket);

    sslSocket->startServerEncryption();
}

void SslServer::socketPeerVerifyError(const QSslError &error)
{
    qWarning() << "peer verify error" << error;
}

void SslServer::socketSslErrors(const QList<QSslError> &errors)
{
    qWarning() << "ssl errors" << errors;
}

const QSslCertificate &SslServer::sslLocalCertificate() const
{
    return m_sslLocalCertificate;
}

const QSslKey &SslServer::sslPrivateKey() const
{
    return m_sslPrivateKey;
}

QSsl::SslProtocol SslServer::sslProtocol() const
{
    return m_sslProtocol;
}

void SslServer::setSslLocalCertificate(const QSslCertificate &certificate)
{
    m_sslLocalCertificate = certificate;
}

bool SslServer::setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format)
{
    QFile certificateFile(path);

    if (!certificateFile.open(QIODevice::ReadOnly))
        return false;

    m_sslLocalCertificate = QSslCertificate(certificateFile.readAll(), format);
    return true;
}

void SslServer::setSslPrivateKey(const QSslKey &key)
{
    m_sslPrivateKey = key;
}

bool SslServer::setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat format, const QByteArray &passPhrase)
{
    QFile keyFile(fileName);

    if (!keyFile.open(QIODevice::ReadOnly))
        return false;

    m_sslPrivateKey = QSslKey(keyFile.readAll(), algorithm, format, QSsl::PrivateKey, passPhrase);
    return true;
}

void SslServer::setSslProtocol(QSsl::SslProtocol protocol)
{
    m_sslProtocol = protocol;
}
