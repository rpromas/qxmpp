// SPDX-FileCopyrightText: 2025 Linus Jahn <lnj@kaidan.im>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef XMLWRITER_H
#define XMLWRITER_H

#include "QXmppUtils_p.h"

#include "StringLiterals.h"

#include <optional>

#include <QDateTime>
#include <QMimeType>
#include <QUrl>
#include <QUuid>
#include <QXmlStreamWriter>

namespace QXmpp::Private {

template<typename T>
concept IsXmlTag =
    requires {
        typename std::tuple_size<T>::type;
    } &&
    std::tuple_size_v<T> == 2 &&
    std::convertible_to<std::tuple_element_t<0, T>, QStringView> &&
    std::convertible_to<std::tuple_element_t<1, T>, QStringView>;

class XmlWriter;

template<typename T>
struct StringSerializer {
    static decltype(auto) serialize(auto &&s) { return std::forward<decltype(s)>(s); }
    static bool hasValue(auto &&s) { return !s.isEmpty(); }
};

template<typename T>
concept IsOptionalStringSerializable = requires(const T &value) {
    { StringSerializer<T>::hasValue(value) } -> std::convertible_to<bool>;
};

template<typename U>
struct StringSerializer<std::optional<U>> {
    static auto serialize(auto &&value)
    {
        if (value) {
            return StringSerializer<U>::serialize(*value);
        }
        return std::remove_cvref_t<decltype(StringSerializer<U>::serialize(*value))> {};
    }
    static bool hasValue(const auto &value) { return value.has_value(); }
};

template<>
struct StringSerializer<bool> {
    static auto serialize(bool value) { return value ? u"true"_s : u"false"_s; }
    static bool hasValue(bool) { return true; }
};

template<typename Number>
    requires std::is_integral_v<Number> || std::is_floating_point_v<Number>
struct StringSerializer<Number> {
    static auto serialize(Number value) { return QString::number(value); }
};

template<typename Enum>
    requires std::is_enum_v<Enum>
struct StringSerializer<Enum> {
    static auto serialize(Enum value) { return Enums::toString(value); }
    static bool hasValue(Enum value)
        requires Enums::NullableEnum<Enum>
    {
        return value != Enums::Data<Enum>::NullValue;
    }
};

template<>
struct StringSerializer<QDateTime> {
    static QString serialize(const QDateTime &datetime);
    static bool hasValue(const QDateTime &datetime) { return datetime.isValid(); }
};

template<>
struct StringSerializer<QUuid> {
    static auto serialize(QUuid uuid) { return uuid.toString(QUuid::WithoutBraces); }
    static bool hasValue(QUuid uuid) { return !uuid.isNull(); }
};

template<>
struct StringSerializer<QUrl> {
    static auto serialize(const QUrl &url) { return url.toString(); }
    static bool hasValue(const QUrl &url) { return !url.isEmpty(); }
};

template<>
struct StringSerializer<QMimeType> {
    static auto serialize(const QMimeType &mimeType) { return mimeType.name(); }
    static bool hasValue(const QMimeType &mimeType) { return mimeType.isValid(); }
};

struct Base64 {
    const QByteArray &data;

    static Base64 fromByteArray(const QByteArray &d) { return { d }; }
};

template<>
struct StringSerializer<Base64> {
    static auto serialize(Base64 value) { return value.data.toBase64(); }
    static bool hasValue(Base64 value) { return !value.data.isEmpty(); }
};

struct DefaultedBool {
    bool value;
    bool defaultValue;
};

template<>
struct StringSerializer<DefaultedBool> {
    static auto serialize(auto &&v) { return v.value ? u"true"_s : u"false"_s; }
    static bool hasValue(auto &&v) { return v.value != v.defaultValue; }
};

// Serializes value to string and converts to type writeable to QXmlStreamWriter
template<typename T>
decltype(auto) xmlS(T &&value)
{
    return toString65(StringSerializer<std::decay_t<T>>::serialize(std::forward<T>(value)));
}

template<typename T>
concept XmlSerializeable = XmlWriterSerializeable<T> || QXmlStreamSerializeable<T>;

template<typename T>
concept XmlSerializeableRange =
    std::ranges::range<T> && XmlSerializeable<std::ranges::range_value_t<T>>;

enum XmlnsPresence {
    WithXmlns,
    WithoutXmlns,
};

class XmlWriter
{
public:
    explicit XmlWriter(QXmlStreamWriter *writer) noexcept : w(writer) { }
    operator QXmlStreamWriter *() const noexcept { return w; }
    QXmlStreamWriter *writer() const noexcept { return w; }

    template<XmlSerializeable T>
    void write(T &&value)
    {
        value.toXml(*this);
    }
    template<IsStdOptional T>
    void write(T &&opt)
    {
        if (opt) {
            write(*opt);
        }
    }
    template<typename Container>
        requires(XmlSerializeableRange<Container> && !XmlSerializeable<Container>)
    void write(Container &&container)
    {
        for (const auto &value : container) {
            write(value);
        }
    }
    template<std::invocable Function>
    void write(Function &&f)
    {
        f();
    }

private:
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    using String = QAnyStringView;
#else
    using String = const QString &;
#endif

    void writeStartElement(String name) { w->writeStartElement(name); }
    void writeStartElement(String name, String xmlns);
    void writeEndElement() { w->writeEndElement(); }
    void writeEmptyElement(String name) { w->writeEmptyElement(name); }
    void writeEmptyElement(String name, String xmlns);
    void writeTextOrEmptyElement(String name, String value);
    void writeTextOrEmptyElement(String name, String xmlns, String value);
    void writeSingleAttributeElement(String name, String attribute, String value);

    template<XmlnsPresence, typename NameType, typename... Values>
    friend class Element;

    template<IsOptionalStringSerializable Enum>
    friend class OptionalEnumElement;

    template<typename T, XmlnsPresence>
    friend class TextElement;

    template<typename T, XmlnsPresence>
    friend class OptionalTextElement;

    template<typename Enum, XmlnsPresence>
    friend class EnumElement;

    template<std::ranges::range Container>
    friend class SingleAttributeElements;

    QXmlStreamWriter *w;
};

template<XmlnsPresence Xmlns, typename NameType, typename... Values>
struct Element {
    NameType name;
    std::conditional_t<Xmlns == WithXmlns, QStringView, std::monostate> xmlns;
    std::tuple<Values...> values;

    Element(NameType name, Values... values)
        requires(Xmlns == WithoutXmlns)
        : name(name), values(std::forward<Values>(values)...)
    {
    }

    Element(NameType name, QStringView xmlns, Values... values)
        requires(Xmlns == WithXmlns)
        : name(name), xmlns(xmlns), values(std::forward<Values>(values)...)
    {
    }

    template<IsXmlTag XmlTag>
    Element(XmlTag xmlTag, Values... values)
        requires(Xmlns == WithXmlns)
        : name(std::get<0>(xmlTag)), xmlns(std::get<1>(xmlTag)), values(std::forward<Values>(values)...)
    {
    }

    void toXml(XmlWriter &w)
    {
        if constexpr (sizeof...(Values) == 0) {
            if constexpr (Xmlns == WithXmlns) {
                w.writeEmptyElement(xmlS(name), xmlS(xmlns));
            } else {
                w.writeEmptyElement(xmlS(name));
            }
        } else {
            if constexpr (Xmlns == WithXmlns) {
                w.writeStartElement(xmlS(name), xmlS(xmlns));
            } else {
                w.writeStartElement(xmlS(name));
            }
            std::apply([&w](auto &&...value) { (w.write(value), ...); }, values);
            w.writeEndElement();
        }
    }
};

template<typename Name, typename... Values>
Element(Name, Values &&...) -> Element<WithoutXmlns, Name, Values...>;

template<IsXmlTag XmlTag, typename... Values>
Element(XmlTag, Values &&...) -> Element<WithXmlns, QStringView, Values...>;

template<typename Name, std::convertible_to<QStringView> S, typename... Values>
Element(Name, S, Values &&...) -> Element<WithXmlns, Name, Values...>;

template<typename T>
struct Attribute {
    QStringView name;
    T value;

    void toXml(XmlWriter &w) const
    {
        w.writer()->writeAttribute(xmlS(name), xmlS(value));
    }
};

template<typename T>
Attribute(QStringView, T &&) -> Attribute<T>;

template<IsOptionalStringSerializable T>
struct OptionalAttribute {
    QStringView name;
    T value;

    void toXml(QXmlStreamWriter *w) const
    {
        if (StringSerializer<std::decay_t<T>>::hasValue(value)) {
            w->writeAttribute(xmlS(name), xmlS(value));
        }
    }
};

template<typename T>
OptionalAttribute(QStringView, T &&) -> OptionalAttribute<T>;

template<typename T>
struct Characters {
    T value;

    void toXml(QXmlStreamWriter *w) const
    {
        w->writeCharacters(xmlS(value));
    }
};

template<typename T>
Characters(T &&) -> Characters<T>;

template<IsOptionalStringSerializable T>
struct OptionalCharacters {
    T value;

    void toXml(QXmlStreamWriter *w) const
    {
        if (StringSerializer<std::decay_t<T>>::hasValue(value)) {
            w->writeCharacters(xmlS(value));
        }
    }
};

template<typename T>
OptionalCharacters(T &&) -> OptionalCharacters<T>;

struct DefaultNamespace {
    QStringView xmlns;

    void toXml(QXmlStreamWriter *w) const
    {
        w->writeDefaultNamespace(xmlS(xmlns));
    }
};

struct Namespace {
    QStringView prefix;
    QStringView xmlns;

    void toXml(QXmlStreamWriter *w) const
    {
        w->writeNamespace(xmlS(xmlns), xmlS(prefix));
    }
};

template<IsOptionalStringSerializable T>
struct OptionalEnumElement {
    T enumeration;
    QStringView xmlns = {};

    void toXml(XmlWriter &w) const
    {
        if (StringSerializer<T>::hasValue(enumeration)) {
            if (xmlns.isNull()) {
                w.writeEmptyElement(xmlS(enumeration));
            } else {
                w.writeEmptyElement(xmlS(enumeration), xmlS(xmlns));
            }
        }
    }
};

template<typename T, XmlnsPresence>
struct TextElement;

template<typename T>
struct TextElement<T, WithXmlns> {
    QStringView name;
    QStringView xmlns;
    T value;

    TextElement(QStringView name, QStringView xmlns, T value)
        : name(name), xmlns(xmlns), value(std::forward<T>(value)) { }

    template<IsXmlTag XmlTag>
    TextElement(XmlTag xmlTag, T value)
        : name(std::get<0>(xmlTag)), xmlns(std::get<1>(xmlTag)), value(std::forward<T>(value))
    {
    }

    void toXml(XmlWriter &w)
    {
        w.writeTextOrEmptyElement(xmlS(name), xmlS(xmlns), xmlS(value));
    }
};

template<typename T>
struct TextElement<T, WithoutXmlns> {
    QStringView name;
    T value;

    TextElement(QStringView name, T value)
        : name(name), value(std::forward<T>(value)) { }

    void toXml(XmlWriter &w)
    {
        w.writeTextOrEmptyElement(xmlS(name), xmlS(value));
    }
};

template<typename T>
TextElement(QStringView, T &&) -> TextElement<T, WithoutXmlns>;

template<IsXmlTag XmlTag, typename T>
TextElement(XmlTag, T &&) -> TextElement<T, WithXmlns>;

template<typename T>
TextElement(QStringView, QStringView, T &&) -> TextElement<T, WithXmlns>;

template<std::ranges::range Range>
struct TextElements {
    QStringView name;
    Range values;

    TextElements(QStringView name, Range values) : name(name), values(std::forward<Range>(values)) { }

    void toXml(XmlWriter &w)
    {
        for (const auto &value : values) {
            w.write(TextElement { name, value });
        }
    }
};

template<typename Range>
TextElements(QStringView, Range &&) -> TextElements<Range>;

template<typename T, XmlnsPresence>
struct OptionalTextElement;

template<IsOptionalStringSerializable T>
struct OptionalTextElement<T, WithXmlns> {
    QStringView name;
    QStringView xmlns;
    T value;

    OptionalTextElement(QStringView name, QStringView xmlns, T value) : name(name), xmlns(xmlns), value(std::forward<T>(value)) { }

    template<IsXmlTag XmlTag>
    OptionalTextElement(XmlTag xmlTag, T value)
        : name(std::get<0>(xmlTag)), xmlns(std::get<1>(xmlTag)), value(std::forward<T>(value))
    {
    }

    void toXml(XmlWriter &w)
    {
        if (StringSerializer<std::decay_t<T>>::hasValue(value)) {
            w.writeTextOrEmptyElement(xmlS(name), xmlS(xmlns), xmlS(value));
        }
    }
};

template<IsOptionalStringSerializable T>
struct OptionalTextElement<T, WithoutXmlns> {
    QStringView name;
    T value;

    void toXml(XmlWriter &w)
    {
        if (StringSerializer<std::decay_t<T>>::hasValue(value)) {
            w.writeTextOrEmptyElement(xmlS(name), xmlS(value));
        }
    }
};

template<typename T>
OptionalTextElement(QStringView, T &&) -> OptionalTextElement<T, WithoutXmlns>;

template<IsXmlTag XmlTag, typename T>
OptionalTextElement(XmlTag, T &&) -> OptionalTextElement<T, WithXmlns>;

template<typename T>
OptionalTextElement(QStringView, QStringView, T &&) -> OptionalTextElement<T, WithXmlns>;

template<std::ranges::range Range>
struct SingleAttributeElements {
    QStringView name;
    QStringView attribute;
    Range values;

    template<typename R>
    SingleAttributeElements(QStringView name, QStringView attribute, R &&values)
        : name(name), attribute(attribute), values(std::forward<R>(values)) { }

    void toXml(XmlWriter &w)
    {
        for (const auto &value : values) {
            using ValueType = std::ranges::range_value_t<Range>;
            w.writeSingleAttributeElement(xmlS(name), xmlS(attribute), xmlS(value));
        }
    }
};

template<typename Range>
SingleAttributeElements(QStringView, QStringView, Range &&) -> SingleAttributeElements<Range>;

template<typename... Values>
struct OptionalContent {
    bool condition;
    std::tuple<Values...> values;

    template<std::convertible_to<bool> Condition, typename... V>
    OptionalContent(Condition condition, V &&...values)
        : condition(condition), values(std::forward<V>(values)...) { }

    void toXml(XmlWriter &w)
    {
        if (condition) {
            std::apply([&w](auto &&...value) { (w.write(value), ...); }, values);
        }
    }
};

template<std::convertible_to<bool> Condition, typename... Values>
OptionalContent(Condition, Values &&...) -> OptionalContent<Values...>;

}  // namespace QXmpp::Private

#endif  // XMLWRITER_H
