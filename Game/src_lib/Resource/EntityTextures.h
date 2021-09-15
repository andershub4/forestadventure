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
};

const std::vector<TextureData> textures = {
    {TextureId::HeroWalkSide, "hero/walk/hero-walk-side.png"},
    {TextureId::HeroWalkFront, "hero/walk/hero-walk-front.png"},
    {TextureId::HeroWalkBack, "hero/walk/hero-back-walk.png"},
    {TextureId::HeroAttackSide, "hero/attack/hero-attack-side.png"},
    {TextureId::HeroAttackFront, "hero/attack/hero-attack-front.png"},
    {TextureId::HeroAttackBack, "hero/attack/hero-attack-back.png"},
    {TextureId::HeroAttackWeaponSide, "hero/attack-weapon/hero-attack-side-weapon.png"},
    {TextureId::HeroAttackWeaponFront, "hero/attack-weapon/hero-attack-front-weapon.png"},
    {TextureId::HeroAttackWeaponBack, "hero/attack-weapon/hero-attack-back-weapon.png"},
    {TextureId::HeroIdleSide, "hero/idle/hero-idle-side.png"},
    {TextureId::HeroIdleFront, "hero/idle/hero-idle-front.png"},
    {TextureId::HeroIdleBack, "hero/idle/hero-idle-back.png"},
    {TextureId::MoleWalkSide, "mole/walk/mole-walk-side.png"},
    {TextureId::MoleWalkFront, "mole/walk/mole-walk-front.png"},
    {TextureId::MoleWalkBack, "mole/walk/mole-walk-back.png"},
    {TextureId::MoleIdleSide, "mole/idle/mole-idle-side.png"},
    {TextureId::MoleIdleFront, "mole/idle/mole-idle-front.png"},
    {TextureId::MoleIdleBack, "mole/idle/mole-idle-back.png"}};

}  // namespace FA
