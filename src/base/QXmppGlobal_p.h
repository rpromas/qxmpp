// SPDX-FileCopyrightText: 2022 Linus Jahn <lnj@kaidan.im>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef QXMPPGLOBAL_P_H
#define QXMPPGLOBAL_P_H

#include "QXmppConstants_p.h"
#include "QXmppGlobal.h"

#include "Enums.h"

namespace QXmpp::Private {

template<>
struct Enums::Data<EncryptionMethod> {
    using enum EncryptionMethod;
    static constexpr auto Values = makeValues<EncryptionMethod>({
        { NoEncryption, {} },
        { UnknownEncryption, {} },
        { Otr, ns_otr },
        { LegacyOpenPGP, ns_legacy_openpgp },
        { Ox, ns_ox },
        { Omemo0, ns_omemo },
        { Omemo1, ns_omemo_1 },
        { Omemo2, ns_omemo_2 },
    });
};

}  // namespace QXmpp::Private

#endif  // QXMPPGLOBAL_P_H
