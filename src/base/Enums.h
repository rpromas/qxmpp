// SPDX-FileCopyrightText: 2025 Linus Jahn <lnj@kaidan.im>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef ENUMS_H
#define ENUMS_H

#include <optional>

#include <QString>

namespace QXmpp::Private::Enums {

template<typename Enum>
struct Values;

template<typename Enum>
concept SerializableEnum = requires(Enum value) {
    typename Values<Enum>;

    requires std::ranges::random_access_range<decltype(Values<Enum>::STRINGS)>;
    requires std::same_as<
        std::ranges::range_value_t<decltype(Values<Enum>::STRINGS)>,
        QStringView>;
};

template<typename Enum>
concept NullableEnum = requires(Enum value) {
    { Values<Enum>::NullValue } -> std::same_as<Enum>;
};

template<typename Enum>
std::optional<Enum> fromString(QStringView str)
    requires SerializableEnum<Enum>
{
    constexpr auto values = Values<Enum>::STRINGS;

    if (auto itr = std::ranges::find(values, str); itr != values.end()) {
        return Enum(std::distance(values.begin(), itr));
    }
    return {};
}

template<typename Enum>
QStringView toString(Enum value)
    requires SerializableEnum<Enum>
{
    return Values<Enum>::STRINGS.at(size_t(value));
};

}  // namespace QXmpp::Private::Enums

#endif  // ENUMS_H
