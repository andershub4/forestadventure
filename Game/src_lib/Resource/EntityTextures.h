/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <vector>

#include "TextureId.h"

namespace FA {

struct TextureData
{
    std::string name_;
    std::string path_;
    sf::Vector2u size_;
};

const std::vector<TextureData> textures = {
    {TextureId::HeroWalkSide, "hero/walk/hero-walk-side.png", {6, 1}},
    {TextureId::HeroWalkFront, "hero/walk/hero-walk-front.png", {6, 1}},
    {TextureId::HeroWalkBack, "hero/walk/hero-back-walk.png", {6, 1}},
    {TextureId::HeroAttackSide, "hero/attack/hero-attack-side.png", {3, 1}},
    {TextureId::HeroAttackFront, "hero/attack/hero-attack-front.png", {3, 1}},
    {TextureId::HeroAttackBack, "hero/attack/hero-attack-back.png", {3, 1}},
    {TextureId::HeroAttackWeaponSide, "hero/attack-weapon/hero-attack-side-weapon.png", {3, 1}},
    {TextureId::HeroAttackWeaponFront, "hero/attack-weapon/hero-attack-front-weapon.png", {3, 1}},
    {TextureId::HeroAttackWeaponBack, "hero/attack-weapon/hero-attack-back-weapon.png", {3, 1}},
    {TextureId::HeroIdleSide, "hero/idle/hero-idle-side.png", {1, 1}},
    {TextureId::HeroIdleFront, "hero/idle/hero-idle-front.png", {1, 1}},
    {TextureId::HeroIdleBack, "hero/idle/hero-idle-back.png", {1, 1}},
    {TextureId::MoleWalkSide, "mole/walk/mole-walk-side.png", {6, 1}},
    {TextureId::MoleWalkFront, "mole/walk/mole-walk-front.png", {6, 1}},
    {TextureId::MoleWalkBack, "mole/walk/mole-walk-back.png", {6, 1}},
    {TextureId::MoleIdleSide, "mole/idle/mole-idle-side.png", {1, 1}},
    {TextureId::MoleIdleFront, "mole/idle/mole-idle-front.png", {1, 1}},
    {TextureId::MoleIdleBack, "mole/idle/mole-idle-back.png", {1, 1}}};

}  // namespace FA
