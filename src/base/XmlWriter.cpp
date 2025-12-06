// SPDX-FileCopyrightText: 2025 Linus Jahn <lnj@kaidan.im>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "XmlWriter.h"

#include "QXmppUtils.h"
#include "QXmppUtils_p.h"

using namespace QXmpp::Private;

QString QXmpp::Private::StringSerializer<QDateTime>::serialize(const QDateTime &datetime)
{
    if (datetime.time().msec() != 0) {
        return datetime.toString(Qt::ISODateWithMs);
    }
    return datetime.toString(Qt::ISODate);
}

void QXmpp::Private::XmlWriter::writeStartElement(String name, String xmlns)
{
    w->writeStartElement(name);
    w->writeDefaultNamespace(xmlns);
}

void QXmpp::Private::XmlWriter::writeEmptyElement(String name, String xmlns)
{
    w->writeStartElement(name);
    w->writeDefaultNamespace(xmlns);
    w->writeEndElement();
}

void QXmpp::Private::XmlWriter::writeTextOrEmptyElement(String name, String value)
{
    if (!value.isEmpty()) {
        w->writeTextElement(name, value);
    } else {
        w->writeEmptyElement(name);
    }
}

void QXmpp::Private::XmlWriter::writeTextOrEmptyElement(String name, String xmlns, String value)
{
    w->writeStartElement(name);
    w->writeDefaultNamespace(xmlns);
    if (!value.isEmpty()) {
        w->writeCharacters(value);
    }
    w->writeEndElement();
}

void QXmpp::Private::XmlWriter::writeSingleAttributeElement(String name, String attribute, String value)
{
    w->writeStartElement(name);
    w->writeAttribute(attribute, value);
    w->writeEndElement();
}
