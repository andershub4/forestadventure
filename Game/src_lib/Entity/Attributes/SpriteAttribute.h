/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "AnimationAttribute.h"
#include "BasicAttribute.h"

namespace FA {

namespace Entity {

class TransformAttribute;
class FaceDirectionAttribute;

class SpriteAttribute : public BasicAttribute
{
public:
    SpriteAttribute(PropertyHandler *owner);
    virtual ~SpriteAttribute();

    virtual void Awake() override;
    virtual void Update(float deltaTime) override;

    void DrawTo(sf::RenderTarget &renderTarget);
    void Set(FrameType frameType);
    void AddAnimation(std::shared_ptr<AnimationAttribute> animation) { animation_ = animation; }
    bool AnimationIsCompleted() const;

private:
    sf::Sprite sprite_;
    std::shared_ptr<TransformAttribute> transform_ = nullptr;
    std::shared_ptr<FaceDirectionAttribute> faceDirection_ = nullptr;
    std::shared_ptr<AnimationAttribute> animation_;
};

}  // namespace Entity

}  // namespace FA
