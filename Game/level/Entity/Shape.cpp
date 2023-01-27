/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Body.h"

namespace FA {

namespace Entity {

Shape::Shape(Body& body)
    : body_(body)
{
#ifdef _DEBUG
    rShape_.setSize({1.0, 1.0});
#endif
}

void Shape::Enter()
{
    for (auto animation : animations_) {
        animation->Enter();
    }
    for (auto image : images_) {
        image->Enter();
    }
}

void Shape::Update(float deltaTime)
{
    for (auto animation : animations_) {
        animation->SetPosition(body_.position_);
        animation->SetRotation(body_.rotation_);
        animation->Update(deltaTime);
    }
    for (auto image : images_) {
        image->SetPosition(body_.position_);
        image->SetRotation(body_.rotation_);
        image->Update(deltaTime);
    }
}

void Shape::RegisterAnimation(std::shared_ptr<AnimationAbility> animation)
{
    animations_.push_back(animation);
}

void Shape::RegisterImage(std::shared_ptr<ImageAbility> image)
{
    images_.push_back(image);
}

void Shape::DrawTo(sf::RenderTarget& renderTarget)
{
    for (auto animation : animations_) {
        animation->DrawTo(renderTarget);
    }
    for (auto image : images_) {
        image->DrawTo(renderTarget);
    }
#ifdef _DEBUG
    renderTarget.draw(rShape_);
#endif
}

}  // namespace Entity

}  // namespace FA
