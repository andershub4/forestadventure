/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "BasicMode.h"

namespace FA {

enum class MoveDirection;
enum class FaceDirection;

namespace Entity {

class BasicState;
class TransformAttribute;
class VelocityAttribute;
class FaceDirectionAttribute;

class MoveMode : public BasicMode
{
public:
    MoveMode(EntityService *owner);

    virtual void Awake() override;
    virtual void Update(float deltaTime) override;
    virtual FrameType GetFrameType() const override { return FrameType::Move; }

    void SetDirection(MoveDirection direction, FaceDirection faceDirection);
    void Execute(BasicState &oldState);

private:
    sf::Vector2f movementVector_{};
    std::shared_ptr<TransformAttribute> transform_ = nullptr;
    std::shared_ptr<VelocityAttribute> velocity_ = nullptr;
    std::shared_ptr<FaceDirectionAttribute> faceDirection_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
