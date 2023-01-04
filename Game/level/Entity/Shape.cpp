/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace FA {

namespace Entity {

Shape::Shape() = default;

Shape::Shape(std::function<void()> updateShape)
    : updateShape_(updateShape)
{
#ifdef _DEBUG
    rShape_.setSize({1.0, 1.0});
#endif
}

void Shape::Update()
{
    updateShape_();
}

void Shape::AddSprite(const std::string& name)
{
    // check if not exist
    sprites_[name] = sf::Sprite();
}

sf::Sprite& Shape::GetSprite(const std::string& name)
{
    return sprites_.at(name);
}

void Shape::Draw(sf::RenderTarget& renderTarget)
{
    for (auto& sprite : sprites_) {
        renderTarget.draw(sprite.second);
    }
#ifdef _DEBUG
    renderTarget.draw(rShape_);
#endif
}

void Shape::SetPosition(const sf::Vector2f& position)
{
    for (auto& sprite : sprites_) {
        sprite.second.setPosition(position);
    }
#ifdef _DEBUG
    rShape_.setPosition(position);
#endif
}

void Shape::SetRotation(float rotation)
{
    for (auto& sprite : sprites_) {
        sprite.second.setRotation(rotation);
    }
#ifdef _DEBUG
    rShape_.setRotation(rotation);
#endif
}

}  // namespace Entity

}  // namespace FA
