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

class TransformAttribute;
class VelocityAttribute;
class FaceDirectionAttribute;

class MoveMode : public BasicMode
{
public:
    MoveMode(EntityService& entityService, ModeController& modeController);

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;

    virtual void Register() override;
    virtual void Update(float deltaTime) override;
    virtual ModeType GetModeType() const override { return ModeType::Move; }

private:
    sf::Vector2f movementVector_{};
    std::shared_ptr<TransformAttribute> transform_ = nullptr;
    std::shared_ptr<VelocityAttribute> velocity_ = nullptr;
    std::shared_ptr<FaceDirectionAttribute> faceDirection_ = nullptr;
    std::shared_ptr<Shape> shape_ = nullptr;

private:
    void SetDirection(MoveDirection direction, FaceDirection faceDirection);
};

}  // namespace Entity

}  // namespace FA
