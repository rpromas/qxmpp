// SPDX-FileCopyrightText: 2009 Manjeet Dahiya <manjeetdahiya@gmail.com>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "QXmppClient_p.h"
#include "QXmppMessage.h"
#include "QXmppPacket_p.h"
#include "QXmppRosterManager.h"
#include "QXmppStreamManagement_p.h"
#include "QXmppVCardManager.h"
#include "QXmppVersionManager.h"

#include "StringLiterals.h"

///
/// \brief You need to implement this method to process incoming XMPP
/// stanzas.
///
/// You should return true if the stanza was handled and no further
/// processing should occur, or false to let other extensions process
/// the stanza.
///
/// End-to-end encrypted stanzas are not passed to this overload, for that
/// purpose use the new overload instead.
///
/// \deprecated This is deprecated since QXmpp 1.5. Please use
/// QXmppClientExtension::handleStanza(const QDomElement &stanza,
/// const std::optional<QXmppE2eeMetadata> &e2eeMetadata).
/// Currently both methods are called by the client, so only implement one!
///
bool QXmppClientExtension::handleStanza(const QDomElement &)
{
    return false;
}

///
/// Returns the reference to QXmppRosterManager object of the client.
///
/// \return Reference to the roster object of the connected client. Use this to
/// get the list of friends in the roster and their presence information.
///
/// \deprecated This method is deprecated since QXmpp 1.1. Use
/// \c QXmppClient::findExtension<QXmppRosterManager>() instead.
///
QXmppRosterManager &QXmppClient::rosterManager()
{
    return *findExtension<QXmppRosterManager>();
}

///
/// Returns the reference to QXmppVCardManager, implementation of \xep{0054}.
///
/// \deprecated This method is deprecated since QXmpp 1.1. Use
/// \c QXmppClient::findExtension<QXmppVCardManager>() instead.
///
QXmppVCardManager &QXmppClient::vCardManager()
{
    return *findExtension<QXmppVCardManager>();
}

///
/// Returns the reference to QXmppVersionManager, implementation of \xep{0092}.
///
/// \deprecated This method is deprecated since QXmpp 1.1. Use
/// \c QXmppClient::findExtension<QXmppVersionManager>() instead.
///
QXmppVersionManager &QXmppClient::versionManager()
{
    return *findExtension<QXmppVersionManager>();
}

///
/// After successfully connecting to the server use this function to send
/// stanzas to the server. This function can solely be used to send various kind
/// of stanzas to the server. QXmppStanza is a parent class of all the stanzas
/// QXmppMessage, QXmppPresence, QXmppIq, QXmppBind, QXmppRosterIq, QXmppSession
/// and QXmppVCard.
///
/// This function does not end-to-end encrypt the packets.
///
/// \return Returns true if the packet was sent, false otherwise.
///
/// Following code snippet illustrates how to send a message using this function:
/// \code
/// QXmppMessage message(from, to, message);
/// client.sendPacket(message);
/// \endcode
///
/// \param packet A valid XMPP stanza. It can be an iq, a message or a presence stanza.
///
/// \deprecated
///
bool QXmppClient::sendPacket(const QXmppNonza &packet)
{
    return d->stream->streamAckManager().sendPacketCompat(packet);
}

///
/// Utility function to send message to all the resources associated with the
/// specified bareJid. If there are no resources available, that is the contact
/// is offline or not present in the roster, it will still send a message to
/// the bareJid.
///
/// \note Usage of this method is discouraged because most modern clients use
/// carbon messages (\xep{0280, Message Carbons}) and MAM (\xep{0313, Message
/// Archive Management}) and so could possibly receive messages multiple times
/// or not receive them at all.
/// \c QXmppClient::sendPacket() should be used instead with a \c QXmppMessage.
///
/// \param bareJid bareJid of the receiving entity
/// \param message Message string to be sent.
///
/// \deprecated
///
void QXmppClient::sendMessage(const QString &bareJid, const QString &message)
{
    QXmppRosterManager *rosterManager = findExtension<QXmppRosterManager>();

    const QStringList resources = rosterManager
        ? rosterManager->getResources(bareJid)
        : QStringList();

    if (!resources.isEmpty()) {
        for (const auto &resource : resources) {
            send(QXmppMessage({}, bareJid + u"/"_s + resource, message));
        }
    } else {
        send(QXmppMessage({}, bareJid, message));
    }
}
