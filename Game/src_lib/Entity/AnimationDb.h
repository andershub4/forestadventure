/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <tuple>

#include "Animation/Animation.h"
#include "Enum/EntityType.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"

namespace FA {

class TextureManager;

namespace Entity {

class AnimationDb
{
public:
    AnimationDb(const TextureManager &textureManager);
    void Init();
    Animation GetAnimation(EntityType entityType, FrameType frameType, FaceDirection faceDir) const;

private:
    using Key = std::tuple<EntityType, FrameType, FaceDirection>;
    std::map<Key, Animation> map_;
    const TextureManager &textureManager_;

private:
    void AddAnimation(Key k, const Animation &animation);
    const sf::Texture *GetTexture(const std::string &name) const;

    void InitPlayer();
    void InitPlayerMove();
    void InitPlayerIdle();
    void InitPlayerAttack();
    void InitPlayerAttackWeapon();

    void InitMole();
    void InitMoleMove();
    void InitMoleIdle();
};

}  // namespace Entity

}  // namespace FA
