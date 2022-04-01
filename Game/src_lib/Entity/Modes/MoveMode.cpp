/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveMode.h"

#include <unordered_map>

#include "Entity/EntityService.h"
#include "Entity/Events/StartMoveEvent.h"
#include "Entity/Shape.h"
#include "Enum/MoveDirection.h"

namespace {

const std::unordered_map<FA::MoveDirection, sf::Vector2f> dirToVector = {{FA::MoveDirection::None, {0.0, 0.0}},
                                                                         {FA::MoveDirection::Up, {0.0, -1.0}},
                                                                         {FA::MoveDirection::Right, {1.0, 0.0}},
                                                                         {FA::MoveDirection::Down, {0.0, 1.0}},
                                                                         {FA::MoveDirection::Left, {-1.0, 0.0}}};

}  // namespace

namespace FA {

namespace Entity {

MoveMode::MoveMode(EntityService& entityService, ModeController& modeController)
    : BasicMode(entityService, modeController)
{}

void MoveMode::Enter(std::shared_ptr<BasicEvent> event)
{
    auto m = std::dynamic_pointer_cast<StartMoveEvent>(event);
    SetDirection(m->moveDirection_, m->faceDirection_);

    auto dir = Service().GetProperty<FaceDirection>("FaceDirection");
    shape_->SetAnimation(GetAnimation(dir));
    shape_->SetImage(GetImage(dir));
}

void MoveMode::Register()
{
    shape_ = Service().GetShape();
}

void MoveMode::Update(float deltaTime)
{
    shape_->Update(deltaTime);

    sf::Vector2f offset = {movementVector_.x * deltaTime, movementVector_.y * deltaTime};
    auto current = Service().GetProperty<sf::Vector2f>("Position");
    auto n = current + offset;
    Service().SetProperty<sf::Vector2f>("Position", n);

    BasicUpdate();
}

void MoveMode::SetDirection(MoveDirection direction, FaceDirection faceDir)
{
    auto velocity = Service().GetProperty<float>("Velocity");
    auto it = dirToVector.find(direction);
    if (it != dirToVector.end()) {
        movementVector_ = it->second * velocity;
    }

    Service().SetProperty("FaceDirection", faceDir);
}

}  // namespace Entity

}  // namespace FA
