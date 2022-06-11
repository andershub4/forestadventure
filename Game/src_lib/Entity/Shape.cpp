/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "AnimationSprite.h"
#include "ImageSprite.h"

namespace FA {

namespace Entity {

Shape::Shape(std::function<void(StateType, Shape &)> beginShape, std::function<void(Shape &)> updateShape)
    : beginShape_(beginShape)
    , updateShape_(updateShape)
{
#ifdef _DEBUG
    rShape_.setSize({1.0, 1.0});
#endif
}

Shape::~Shape() = default;

void Shape::OnEnterShape(StateType stateType)
{
    beginShape_(stateType, *this);  // call entity's OnBeginShape method
}

void Shape::OnExitShape(StateType stateType)
{}

void Shape::OnUpdateShape(float deltaTime)
{
    for (auto a : animations_) {
        a.second->Update(deltaTime);
    }

    for (auto i : images_) {
        i.second->Update(deltaTime);
    }

    updateShape_(*this);  // call entity's OnUpdateShape method
}

void Shape::OnDrawShape(sf::RenderTarget &renderTarget)
{
    for (auto a : animations_) {
        a.second->DrawTo(renderTarget);
    }

    for (auto i : images_) {
        i.second->DrawTo(renderTarget);
    }

#ifdef _DEBUG
    renderTarget.draw(rShape_);
#endif
}

void Shape::SetPosition(const sf::Vector2f &pos)
{
    for (auto sprite : animations_) {
        sprite.second->ApplyTo([pos](sf::Sprite &sprite) { sprite.setPosition(pos); });
    }

    for (auto sprite : images_) {
        sprite.second->ApplyTo([pos](sf::Sprite &sprite) { sprite.setPosition(pos); });
    }

#ifdef _DEBUG
    rShape_.setPosition(pos);
#endif
}

std::shared_ptr<AnimationSprite> Shape::GetAnimationSprite(const std::string &name)
{
    return animations_.at(name);
}

std::shared_ptr<ImageSprite> Shape::GetImageSprite(const std::string &name)
{
    return images_.at(name);
}

void Shape::RegisterAnimationSprite(const std::string &name, std::shared_ptr<AnimationSprite> s)
{
    animations_[name] = s;
}

void Shape::RegisterImageSprite(const std::string &name, std::shared_ptr<ImageSprite> s)
{
    images_[name] = s;
}

}  // namespace Entity

}  // namespace FA
