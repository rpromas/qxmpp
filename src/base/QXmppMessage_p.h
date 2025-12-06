// SPDX-FileCopyrightText: 2025 Linus Jahn <lnj@kaidan.im>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef QXMPPMESSAGE_P_H
#define QXMPPMESSAGE_P_H

#include "QXmppMessage.h"

#include "Enums.h"

namespace QXmpp::Private {

template<>
struct Enums::Data<QXmppMessage::Type> {
    using enum QXmppMessage::Type;
    static constexpr auto Values = makeValues<QXmppMessage::Type>({
        { Error, u"error" },
        { Normal, u"normal" },
        { Chat, u"chat" },
        { GroupChat, u"groupchat" },
        { Headline, u"headline" },
    });
};

}  // namespace QXmpp::Private

#endif  // QXMPPMESSAGE_P_H
