/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Animation/AnimationFactory.h"
#include "BasicSprite.h"

namespace FA {

namespace Entity {

class AnimatedSprite : public BasicSprite
{
public:
    AnimatedSprite(const sf::Vector2u &position, unsigned int scale, const AnimationFactory &animationFactory);
    virtual ~AnimatedSprite();

    virtual void Update(float deltaTime) override;
    virtual void DrawTo(sf::RenderTarget &renderTarget) override;
    virtual sf::Vector2f GetPosition() const override;
    virtual void Move(const Movement &movement) override;

    virtual void StartAnimation() override;
    virtual void SetAnimation(FrameType frameType, FaceDirection faceDir) override;
    virtual bool AnimationIsCompleted() const override;

private:
    sf::Sprite sprite_;
    AnimationFactory animationFactory_;
    std::unique_ptr<Animation> animation_{};
};

}  // namespace Entity

}  // namespace FA
