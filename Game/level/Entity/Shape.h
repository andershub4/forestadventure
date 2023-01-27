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

#include "Abilities/AnimationAbility.h"
#include "Abilities/ImageAbility.h"
#include "Fwd/SfmlFwd.h"
#include "StateType.h"

namespace FA {

namespace Entity {

struct Body;

class Shape
{
public:
    Shape(Body &body);

    void RegisterAnimation(std::shared_ptr<AnimationAbility> animation);
    void RegisterImage(std::shared_ptr<ImageAbility> image);

    void Enter();
    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget &renderTarget);

    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float rotation);

private:
    std::vector<std::shared_ptr<AnimationAbility>> animations_;
    std::vector<std::shared_ptr<ImageAbility>> images_;
#ifdef _DEBUG
    sf::RectangleShape rShape_;
#endif
    Body &body_;
};

}  // namespace Entity

}  // namespace FA
