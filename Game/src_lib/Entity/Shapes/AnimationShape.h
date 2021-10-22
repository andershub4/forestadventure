/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>

#include <SFML/Graphics/Sprite.hpp>

#include "Animation/Animator.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

class AnimationShape
{
public:
    AnimationShape(std::function<std::string(FrameType, FaceDirection)> lookupKeyFunc);

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget &renderTarget);

    void AddAnimation(FrameType frameType, FaceDirection faceDir, const Animation &animation);
    void SetAnimation(FrameType frameType, FaceDirection faceDir);
    void SetTransform(const sf::Vector2f &position, float scale);
    bool IsCompleted() const;

private:
    Animator animator_;
    sf::Sprite sprite_;
    Animation currentAnimation_;
    std::function<std::string(FrameType, FaceDirection)> lookupKeyFunc_;
};

}  // namespace Entity

}  // namespace FA
