/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#ifdef _DEBUG
#include <SFML/Graphics/RectangleShape.hpp>
#endif
#include <SFML/Graphics/Sprite.hpp>

#include "Fwd/SfmlFwd.h"
#include "Resource/Animation.h"
#include "Resource/Image.h"

namespace FA {

namespace Entity {

class TransformAttribute;
class FaceDirectionAttribute;
class EntityService;

class Shape
{
public:
    Shape(const EntityService *entityService);
    virtual ~Shape();

    void Register();
    void Update(float deltaTime);

    void DrawTo(sf::RenderTarget &renderTarget);
    bool AnimationIsCompleted() const;

    void SetAnimation(const Animation &animation);
    void SetImage(const Image &image);

private:
    const EntityService *entityService_ = nullptr;
    std::shared_ptr<TransformAttribute> transform_ = nullptr;
    std::shared_ptr<FaceDirectionAttribute> faceDirection_ = nullptr;

#ifdef _DEBUG
    sf::RectangleShape rShape_;
#endif
    sf::Sprite animationSprite_;
    sf::Sprite imageSprite_;
    Animation currentAnimation_;
    Image currentImage_;
};

}  // namespace Entity

}  // namespace FA
