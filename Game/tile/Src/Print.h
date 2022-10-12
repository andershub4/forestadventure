/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <map>
#include <ostream>
#include <unordered_map>
#include <vector>

#pragma once

namespace FA {

namespace Tile {

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

}  // namespace Tile

}  // namespace FA
