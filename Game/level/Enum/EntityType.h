/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

enum class EntityType { Unknown, Static, Player, Mole, Arrow, Tile, Coin };

inline std::ostream& operator<<(std::ostream& os, const EntityType& e)
{
    std::string str;
    switch (e) {
        case EntityType::Arrow:
            str = "Arrow";
            break;
        case EntityType::Coin:
            str = "Coin";
            break;
        case EntityType::Mole:
            str = "Mole";
            break;
        case EntityType::Player:
            str = "Player";
            break;
        case EntityType::Static:
            str = "Static";
            break;
        case EntityType::Tile:
            str = "Tile";
            break;
        case EntityType::Unknown:
            str = "Unknown";
            break;
    }

    os << str;

    return os;
}

}  // namespace FA
