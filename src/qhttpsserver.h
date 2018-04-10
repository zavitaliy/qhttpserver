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

#ifndef QHTTPSSERVER_H
#define QHTTPSSERVER_H

#include <QSsl>
#include <QSslCertificate>
#include <QSslKey>

#include "qhttpserver.h"

class SslServer;
class QHTTPSERVER_API QHttpsServer : public QHttpServer
{
    Q_OBJECT
public:

    /// Construct a new QHttpsServer.
    /** @param parent Parent QObject for the server. */
    explicit QHttpsServer(QObject *parent = nullptr);

    ~QHttpsServer();

    const QSslCertificate &sslLocalCertificate() const;
    const QSslKey &sslPrivateKey() const;
    QSsl::SslProtocol sslProtocol() const;

    /*!
      Sets the local certificate to \p certificate.

      \note
      This member function should be called before QHttpsServer::listen
      */
    void setSslLocalCertificate(const QSslCertificate &certificate);
    bool setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format = QSsl::Pem);

    /*!
      Sets the private key to \p key.

      \warning
      Remember that encryption security relies on the fact that no one knows
      your private key.

      \note
      This member function should be called before QHttpsServer::listen
      */

    void setSslPrivateKey(const QSslKey &key);
    bool setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm = QSsl::Rsa, QSsl::EncodingFormat format = QSsl::Pem, const QByteArray &passPhrase = QByteArray());
    void setSslProtocol(QSsl::SslProtocol protocol);

    virtual bool listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 80) Q_DECL_OVERRIDE;

};

#endif // QHTTPSSERVER_H
