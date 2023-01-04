/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#ifdef _DEBUG
#include <SFML/Graphics/RectangleShape.hpp>
#endif
#include <SFML/Graphics/Sprite.hpp>

#include "Fwd/SfmlFwd.h"
#include "StateType.h"

namespace FA {

namespace Entity {

class Shape
{
public:
    Shape();
    Shape(std::function<void()> updateShape);

    void AddSprite(const std::string &name);
    sf::Sprite &GetSprite(const std::string &name);

    void Update();
    void Draw(sf::RenderTarget &renderTarget);

    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float rotation);

private:
    std::function<void()> updateShape_;
    std::unordered_map<std::string, sf::Sprite> sprites_;
#ifdef _DEBUG
    sf::RectangleShape rShape_;
#endif
};

}  // namespace Entity

}  // namespace FA
