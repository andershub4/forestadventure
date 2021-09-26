/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "BasicComponent.h"

namespace FA {

enum class MoveDirection;

namespace Entity {

class BasicState;
class TransformComponent;

class MovementComponent : public BasicComponent
{
public:
    MovementComponent(ComponentHandler *owner);

    virtual void Awake() override;
    virtual void Update(float deltaTime) override;

    void SetVelocity(float velocity) { velocity_ = velocity; }
    void SetDirection(MoveDirection direction);
    void Execute(BasicState &oldState);

private:
    float velocity_{};
    sf::Vector2f movementVector_{};
    std::shared_ptr<TransformComponent> transform_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
