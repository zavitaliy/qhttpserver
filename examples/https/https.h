#include "qhttpserverfwd.h"

#include <QObject>

/// HelloWorld

class HttpsHelloWorld : public QObject
{
    Q_OBJECT

public:
    HttpsHelloWorld();

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);
};
