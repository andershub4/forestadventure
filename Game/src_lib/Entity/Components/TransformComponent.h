/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "BasicComponent.h"

namespace FA {

namespace Entity {

class TransformComponent : public BasicComponent
{
public:
    TransformComponent(ComponentHandler *owner);

    virtual void Update(float deltaTime) override{};

    void Move(const sf::Vector2f &offset);
    void SetPosition(const sf::Vector2f &position) { position_ = position; }
    const sf::Vector2f& GetPosition() const { return position_; }
    void SetScale(float scale) { scale_ = scale; }
    float GetScale() const { return scale_; }

private:
    sf::Vector2f position_{};
    float scale_{};
};

}  // namespace Entity

}  // namespace FA
