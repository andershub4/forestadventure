/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <vector>

#include "SheetId.h"

namespace FA {

struct SheetData
{
    std::string name_;
    std::string path_;
    sf::Vector2u size_;
};

const std::vector<SheetData> sheetData = {
    {SheetId::HeroWalkSide, "hero/walk/hero-walk-side.png", {6, 1}},
    {SheetId::HeroWalkFront, "hero/walk/hero-walk-front.png", {6, 1}},
    {SheetId::HeroWalkBack, "hero/walk/hero-back-walk.png", {6, 1}},
    {SheetId::HeroAttackSide, "hero/attack/hero-attack-side.png", {3, 1}},
    {SheetId::HeroAttackFront, "hero/attack/hero-attack-front.png", {3, 1}},
    {SheetId::HeroAttackBack, "hero/attack/hero-attack-back.png", {3, 1}},
    {SheetId::HeroAttackWeaponSide, "hero/attack-weapon/hero-attack-side-weapon.png", {3, 1}},
    {SheetId::HeroAttackWeaponFront, "hero/attack-weapon/hero-attack-front-weapon.png", {3, 1}},
    {SheetId::HeroAttackWeaponBack, "hero/attack-weapon/hero-attack-back-weapon.png", {3, 1}},
    {SheetId::HeroIdleSide, "hero/idle/hero-idle-side.png", {1, 1}},
    {SheetId::HeroIdleFront, "hero/idle/hero-idle-front.png", {1, 1}},
    {SheetId::HeroIdleBack, "hero/idle/hero-idle-back.png", {1, 1}},
    {SheetId::MoleWalkSide, "mole/walk/mole-walk-side.png", {6, 1}},
    {SheetId::MoleWalkFront, "mole/walk/mole-walk-front.png", {6, 1}},
    {SheetId::MoleWalkBack, "mole/walk/mole-walk-back.png", {6, 1}},
    {SheetId::MoleIdleSide, "mole/idle/mole-idle-side.png", {1, 1}},
    {SheetId::MoleIdleFront, "mole/idle/mole-idle-front.png", {1, 1}},
    {SheetId::MoleIdleBack, "mole/idle/mole-idle-back.png", {1, 1}}};

}  // namespace FA
