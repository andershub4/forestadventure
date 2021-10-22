/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

class TransformAttribute;
class FaceDirectionAttribute;
class EntityService;
class AnimationShape;

class Shape
{
public:
    Shape(EntityService *owner);
    virtual ~Shape();

    void Awake();
    void Update(float deltaTime);

    void DrawTo(sf::RenderTarget &renderTarget);
    void Set(FrameType frameType);
    void AddAnimation(std::shared_ptr<AnimationShape> animation);
    bool AnimationIsCompleted() const;

private:
    EntityService *entityService_ = nullptr;
    sf::Sprite sprite_;
    std::shared_ptr<TransformAttribute> transform_ = nullptr;
    std::shared_ptr<FaceDirectionAttribute> faceDirection_ = nullptr;
    std::shared_ptr<AnimationShape> animation_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
