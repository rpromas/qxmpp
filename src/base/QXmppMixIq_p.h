// SPDX-FileCopyrightText: 2023 Melvin Keskin <melvo@olomono.de>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef QXMPPMIXIQ_P_H
#define QXMPPMIXIQ_P_H

#include "QXmppIq.h"
#include "QXmppMixConfigItem.h"
#include "QXmppMixInvitation.h"

#include "Enums.h"

class QXMPP_EXPORT QXmppMixSubscriptionUpdateIq : public QXmppIq
{
public:
    QXmppMixSubscriptionUpdateIq();

    QXMPP_PRIVATE_DECLARE_RULE_OF_SIX(QXmppMixSubscriptionUpdateIq)

    QXmppMixConfigItem::Nodes additions() const;
    void setAdditions(QXmppMixConfigItem::Nodes);

    QXmppMixConfigItem::Nodes removals() const;
    void setRemovals(QXmppMixConfigItem::Nodes);

    static bool isMixSubscriptionUpdateIq(const QDomElement &);

protected:
    void parseElementFromChild(const QDomElement &) override;
    void toXmlElementFromChild(QXmlStreamWriter *) const override;

private:
    QXmppMixConfigItem::Nodes m_additions;
    QXmppMixConfigItem::Nodes m_removals;
};

class QXMPP_EXPORT QXmppMixInvitationRequestIq : public QXmppIq
{
public:
    QXmppMixInvitationRequestIq();

    QXMPP_PRIVATE_DECLARE_RULE_OF_SIX(QXmppMixInvitationRequestIq)

    QString inviteeJid() const;
    void setInviteeJid(const QString &);

    static bool isMixInvitationRequestIq(const QDomElement &);

protected:
    void parseElementFromChild(const QDomElement &) override;
    void toXmlElementFromChild(QXmlStreamWriter *) const override;

private:
    QString m_inviteeJid;
};

class QXMPP_EXPORT QXmppMixInvitationResponseIq : public QXmppIq
{
public:
    QXmppMixInvitationResponseIq();

    QXMPP_PRIVATE_DECLARE_RULE_OF_SIX(QXmppMixInvitationResponseIq)

    QXmppMixInvitation invitation() const;
    void setInvitation(const QXmppMixInvitation &);

    static bool isMixInvitationResponseIq(const QDomElement &);

protected:
    void parseElementFromChild(const QDomElement &) override;
    void toXmlElementFromChild(QXmlStreamWriter *) const override;

private:
    QXmppMixInvitation m_invitation;
};

namespace QXmpp::Private {

template<>
struct Enums::Data<QXmppMixConfigItem::Node> {
    using enum QXmppMixConfigItem::Node;
    static constexpr bool IsFlags = true;
    static constexpr auto Values = makeValues<QXmppMixConfigItem::Node>({
        { AllowedJids, ns_mix_node_allowed },
        { AvatarData, ns_user_avatar_data },
        { AvatarMetadata, ns_user_avatar_metadata },
        { BannedJids, ns_mix_node_banned },
        { Configuration, ns_mix_node_config },
        { Information, ns_mix_node_info },
        { JidMap, ns_mix_node_jidmap },
        { Messages, ns_mix_node_messages },
        { Participants, ns_mix_node_participants },
        { Presence, ns_mix_node_presence },
    });
};

}  // namespace QXmpp::Private

#endif  // QXMPPMIXIQ_P_H
