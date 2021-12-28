/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <tuple>
#include <unordered_map>

#include "Animation/Animation.h"
#include "Enum/EntityType.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"
#include "Resource/SpriteSheet.h"
#include "Resource/TextureManager.h"

namespace FA {

struct AnimationData
{
    std::string sheetId_;
    struct FrameData
    {
        sf::Vector2u start_;
        unsigned int n_;
        unsigned int defaultIndex_;
        bool mirror_;
    };

    FrameData data_;
    FrameType frameType_;
    FaceDirection dir_;
};

class AnimationDb
{
public:
    AnimationDb(TextureManager &textureManager);
    void Load(EntityType entityType, const std::vector<AnimationData> &animationData);
    Animation GetAnimation(EntityType entityType, FrameType frameType, FaceDirection faceDir) const;

private:
    using Key = std::tuple<EntityType, FrameType, FaceDirection>;
    std::map<Key, Animation> map_;
    TextureManager &textureManager_;
    std::unordered_map<std::string, SpriteSheet> sheetMap_;

private:
    void AddAnimation(Key k, const Animation &animation);
    SpriteSheet GetSheet(const std::string &name) const;
    void LoadTextures();
    void Init(EntityType entityType, const std::vector<AnimationData> &animationData);

    //void InitPlayer();
    //void InitMole();
};

}  // namespace FA
