/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <map>
#include <ostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#pragma once

namespace FA {

template <class K, class V>
inline std::ostream& operator<<(std::ostream& os, const std::pair<K, V>& p)
{
    os << "{" << p.first << ", " << p.second << "}";

    return os;
}

template <class T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    std::string separator;
    for (const auto& entry : v) {
        os << separator << "{" << entry << "}";
        separator = ", ";
    }
    os << "]";

    return os;
}

template <class K, class V, class P = std::less<K>>
inline std::ostream& operator<<(std::ostream& os, const std::map<K, V, P>& m)
{
    os << "[";
    std::string separator;
    for (const auto& entry : m) {
        os << separator << entry;
        separator = ", ";
    }
    os << "]";

    return os;
}

template <class K, class V>
inline std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& m)
{
    os << "[";
    std::string separator;
    for (const auto& entry : m) {
        os << separator << entry;
        separator = ", ";
    }
    os << "]";

    return os;
}

}  // namespace FA

#define DETAIL_FORMAT(name, arg) "{" << name << ": " << arg << "}"

#define OUT(arg) DETAIL_FORMAT(#arg, arg);
#define OUT2(name, arg) DETAIL_FORMAT(name, arg)

#define DUMP(arg)              \
    [&]() {                    \
        std::ostringstream os; \
        os << OUT(arg);        \
        return os.str();       \
    }()                        \
        .c_str()

#define DUMP2(name, arg)       \
    [&]() {                    \
        std::ostringstream os; \
        os << OUT2(name, arg); \
        return os.str();       \
    }()                        \
        .c_str()

#define DELIM ", "
