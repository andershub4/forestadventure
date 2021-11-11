
/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicState.h"

#include "Entity/EntityService.h"
#include "Entity/Events/AttackEvent.h"
#include "Entity/Events/AttackWeapon.h"
#include "Entity/Events/StartMoveEvent.h"
#include "Entity/Events/StopMoveEvent.h"
#include "Entity/StateController.h"
#include "Enum/KeyboardKey.h"

namespace FA {

namespace Entity {

BasicState::BasicState(StateController& stateController, StateData& stateData, EntityService& entityService)
    : stateController_(stateController)
    , stateData_(stateData)
    , entityService_(entityService)
{}

BasicState::~BasicState() = default;

void BasicState::HandleIsKeyPressed(Keyboard::Key key)
{
    std::shared_ptr<BasicEvent> event = nullptr;

    if (key == Keyboard::Key::Right) {
        event = std::make_shared<StartMoveEvent>(MoveDirection::Right, FaceDirection::Right);
    }
    else if (key == Keyboard::Key::Left) {
        event = std::make_shared<StartMoveEvent>(MoveDirection::Left, FaceDirection::Left);
    }
    else if (key == Keyboard::Key::Up) {
        event = std::make_shared<StartMoveEvent>(MoveDirection::Up, FaceDirection::Up);
    }
    else if (key == Keyboard::Key::Down) {
        event = std::make_shared<StartMoveEvent>(MoveDirection::Down, FaceDirection::Down);
    }

    if (event) stateController_.HandleEvent(GetModeType(), event);
}

void BasicState::HandleIsKeyReleased(Keyboard::Key key)
{
    stateController_.HandleEvent(GetModeType(), std::make_shared<StopMoveEvent>());
}

void BasicState::HandleKeyPressed(Keyboard::Key key)
{
    std::shared_ptr<BasicEvent> event = nullptr;

    if (key == Keyboard::Key::RControl) {
        event = std::make_shared<AttackEvent>();
    }
    else if (key == Keyboard::Key::Space) {
        event = std::make_shared<AttackWeaponEvent>();
    }

    if (event) stateController_.HandleEvent(GetModeType(), event);
}

std::shared_ptr<Shape> BasicState::GetShape() const
{
    return entityService_.GetShape();
}

void BasicState::Update()
{
    stateController_.Update(GetModeType(), entityService_.GetShape());
}

void BasicState::InternalCreate(const PropertyData& data)
{
    stateController_.Create(data);
}

void BasicState::Start()
{
    stateController_.Start();
}

void BasicState::InternalEnter(std::shared_ptr<BasicEvent> event)
{
    stateController_.GetMode(GetModeType())->Enter(event);
}

void BasicState::InternalExit()
{
    stateController_.GetMode(GetModeType())->Exit();
}

void BasicState::InternalUpdate(float deltaTime)
{
    stateController_.GetMode(GetModeType())->Update(deltaTime);
}

}  // namespace Entity

}  // namespace FA
