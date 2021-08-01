/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Animation/Animation.h"
#include "Animation/AnimationDB.h"

namespace FA {

namespace Entity {

class TransformComponent;

class SpriteComponent
{
public:
    SpriteComponent() = default;
    SpriteComponent(const TransformComponent &transform, const AnimationDB &animationDB);
    virtual ~SpriteComponent();

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget &renderTarget);
    void Apply(const TransformComponent &transform);
    void StartAnimation();
    void SetAnimation(FrameType frameType, FaceDirection faceDir);
    bool AnimationIsCompleted() const;

private:
    sf::Sprite sprite_;
    AnimationDB animationDB_;
    Animation animation_;
};

}  // namespace Entity

}  // namespace FA
