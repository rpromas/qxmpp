// SPDX-FileCopyrightText: 2025 Linus Jahn <lnj@kaidan.im>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef QXMPPPUBSUBNODECONFIG_P_H
#define QXMPPPUBSUBNODECONFIG_P_H

#include "QXmppPubSubNodeConfig.h"

#include "Enums.h"

namespace QXmpp::Private {

template<>
struct Enums::Data<QXmppPubSubNodeConfig::AccessModel> {
    using enum QXmppPubSubNodeConfig::AccessModel;
    static constexpr auto Values = makeValues<QXmppPubSubNodeConfig::AccessModel>({
        { Open, u"open" },
        { Presence, u"presence" },
        { Roster, u"roster" },
        { Authorize, u"authorize" },
        { Allowlist, u"whitelist" },
    });
};

template<>
struct Enums::Data<QXmppPubSubNodeConfig::PublishModel> {
    using enum QXmppPubSubNodeConfig::PublishModel;
    static constexpr auto Values = makeValues<QXmppPubSubNodeConfig::PublishModel>({
        { Publishers, u"publishers" },
        { Subscribers, u"subscribers" },
        { Anyone, u"open" },
    });
};

template<>
struct Enums::Data<QXmppPubSubNodeConfig::ChildAssociationPolicy> {
    using enum QXmppPubSubNodeConfig::ChildAssociationPolicy;
    static constexpr auto Values = makeValues<QXmppPubSubNodeConfig::ChildAssociationPolicy>({
        { All, u"all" },
        { Owners, u"owners" },
        { Whitelist, u"whitelist" },
    });
};

template<>
struct Enums::Data<QXmppPubSubNodeConfig::ItemPublisher> {
    using enum QXmppPubSubNodeConfig::ItemPublisher;
    static constexpr auto Values = makeValues<QXmppPubSubNodeConfig::ItemPublisher>({
        { NodeOwner, u"owner" },
        { Publisher, u"publisher" },
    });
};

template<>
struct Enums::Data<QXmppPubSubNodeConfig::NodeType> {
    using enum QXmppPubSubNodeConfig::NodeType;
    static constexpr auto Values = makeValues<QXmppPubSubNodeConfig::NodeType>({
        { Leaf, u"leaf" },
        { Collection, u"collection" },
    });
};

template<>
struct Enums::Data<QXmppPubSubNodeConfig::NotificationType> {
    using enum QXmppPubSubNodeConfig::NotificationType;
    static constexpr auto Values = makeValues<QXmppPubSubNodeConfig::NotificationType>({
        { Normal, u"normal" },
        { Headline, u"headline" },
    });
};

template<>
struct Enums::Data<QXmppPubSubNodeConfig::SendLastItemType> {
    using enum QXmppPubSubNodeConfig::SendLastItemType;
    static constexpr auto Values = makeValues<QXmppPubSubNodeConfig::SendLastItemType>({
        { Never, u"never" },
        { OnSubscription, u"on_sub" },
        { OnSubscriptionAndPresence, u"on_sub_and_presence" },
    });
};

}  // namespace QXmpp::Private

#endif  // QXMPPPUBSUBNODECONFIG_P_H
