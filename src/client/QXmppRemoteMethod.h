// SPDX-FileCopyrightText: 2009 Ian Reinhart Geiser <geiseri@kde.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef QXMPPREMOTEMETHOD_H
#define QXMPPREMOTEMETHOD_H

#include "QXmppRpcIq.h"

#include <QObject>
#include <QVariant>

class QXmppClient;

#if QXMPP_DEPRECATED_SINCE(1, 12)
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED

struct [[deprecated("Removed from public API (unmaintained)")]] QXmppRemoteMethodResult {
    QXmppRemoteMethodResult() : hasError(false), code(0) { }
    bool hasError;
    int code;
    QString errorMessage;
    QVariant result;
};

class QXMPP_EXPORT [[deprecated("Removed from public API (unmaintained)")]] QXmppRemoteMethod : public QObject
{
    Q_OBJECT
public:
    QXmppRemoteMethod(const QString &jid, const QString &method, const QVariantList &args, QXmppClient *client);
    QXmppRemoteMethodResult call();

private Q_SLOTS:
    void gotError(const QXmppRpcErrorIq &iq);
    void gotResult(const QXmppRpcResponseIq &iq);

Q_SIGNALS:
    void callDone();

private:
    QXmppRpcInvokeIq m_payload;
    QXmppClient *m_client;
    QXmppRemoteMethodResult m_result;
};

QT_WARNING_POP
#endif

#endif  // QXMPPREMOTEMETHOD_H
