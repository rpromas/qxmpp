// SPDX-FileCopyrightText: 2012 Manjeet Dahiya <manjeetdahiya@gmail.com>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "example_1_echoClient.h"

#include "QXmppLogger.h"
#include "QXmppMessage.h"
#include "QXmppTask.h"

#include <QCoreApplication>

echoClient::echoClient(QObject *parent)
    : QXmppClient(parent)
{
    connect(this, &QXmppClient::messageReceived, this, &echoClient::messageReceived);
}

echoClient::~echoClient() = default;

void echoClient::messageReceived(const QXmppMessage &message)
{
    send(QXmppMessage({}, message.from(), u"Your message: " + message.body()));
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    echoClient client;
    client.logger()->setLoggingType(QXmppLogger::StdoutLogging);
    client.connectToServer("qxmpp.test1@qxmpp.org", "qxmpp123");

    return app.exec();
}
