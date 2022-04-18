/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Events/AttackEvent.h"
#include "Entity/Events/AttackWeapon.h"
#include "Entity/Events/StartMoveEvent.h"
#include "Entity/Events/StopMoveEvent.h"
#include "Entity/PropertyData.h"
#include "Entity/Shape.h"
#include "Entity/States/AttackState.h"
#include "Entity/States/AttackWeaponState.h"
#include "Entity/States/IdleState.h"
#include "Entity/States/MoveState.h"
#include "Enum/KeyboardKey.h"
#include "Enum/MessageType.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<FaceDirection, sf::Vector2f> arrowOffset = {{FaceDirection::Down, {0.0, 15.0}},
                                                                     {FaceDirection::Left, {-15.0, 5.0}},
                                                                     {FaceDirection::Right, {15.0, 5.0}},
                                                                     {FaceDirection::Up, {0.0, -15.0}}};

const std::unordered_map<FaceDirection, float> arrowRotation = {{FaceDirection::Down, 180.0f},
                                                                {FaceDirection::Left, 270.0f},
                                                                {FaceDirection::Right, 90.0f},
                                                                {FaceDirection::Up, 0.0f}};

const std::unordered_map<StateType, std::unordered_map<FaceDirection, AnimationData>> animationDatas = {
    {StateType::Move,
     {{FaceDirection::Left, {SheetId::HeroWalkSide, {{0, 0}, 6, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroWalkSide, {{0, 0}, 6, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroWalkFront, {{0, 0}, 6, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroWalkBack, {{0, 0}, 6, 0}, false}}}},
    {StateType::Idle,
     {{FaceDirection::Left, {SheetId::HeroIdleSide, {{0, 0}, 1, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroIdleSide, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroIdleFront, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroIdleBack, {{0, 0}, 1, 0}, false}}}},
    {StateType::Attack,
     {{FaceDirection::Left, {SheetId::HeroAttackSide, {{0, 0}, 3, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroAttackSide, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroAttackFront, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroAttackBack, {{0, 0}, 3, 0}, false}}}},
    {StateType::AttackWeapon,
     {{FaceDirection::Left, {SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroAttackWeaponFront, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroAttackWeaponBack, {{0, 0}, 3, 0}, false}}}}};

}  // namespace

PlayerEntity::PlayerEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                           EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

PlayerEntity::~PlayerEntity() = default;

std::vector<MessageType> PlayerEntity::Messages() const
{
    return {MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed};
}

void PlayerEntity::OnMessage(std::shared_ptr<Message> msg)
{
    if (msg->GetMessageType() == MessageType::IsKeyPressed) {
        auto m = std::dynamic_pointer_cast<IsKeyPressedMessage>(msg);
        auto key = m->GetKey();
        if (key == Keyboard::Key::Right) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Right, FaceDirection::Right, 0.0f));
        }
        else if (key == Keyboard::Key::Left) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Left, FaceDirection::Left, 0.0f));
        }
        else if (key == Keyboard::Key::Down) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Down, FaceDirection::Down, 0.0f));
        }
        else if (key == Keyboard::Key::Up) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Up, FaceDirection::Up, 0.0f));
        }
    }
    else if (msg->GetMessageType() == MessageType::IsKeyReleased) {
        auto m = std::dynamic_pointer_cast<IsKeyReleasedMessage>(msg);
        auto key = m->GetKey();
        if (key == Keyboard::Key::Right || key == Keyboard::Key::Left || key == Keyboard::Key::Down ||
            key == Keyboard::Key::Up) {
            HandleEvent(std::make_shared<StopMoveEvent>());
        }
    }
    else if (msg->GetMessageType() == MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<KeyPressedMessage>(msg);
        auto key = m->GetKey();
        if (key == Keyboard::Key::RControl) {
            HandleEvent(std::make_shared<AttackEvent>());
        }
        else if (key == Keyboard::Key::Space) {
            HandleEvent(std::make_shared<AttackWeaponEvent>(EntityType::Arrow, arrowOffset, arrowRotation));
        }
    }
}

void PlayerEntity::RegisterStates(StateMachine& stateMachine)
{
    auto idleState = stateMachine.RegisterState<IdleState>(true);
    idleState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    idleState->BindAction(Action::ChangeTo(StateType::Attack), EventType::Attack);
    idleState->BindAction(Action::ChangeTo(StateType::AttackWeapon), EventType::AttackWeapon);
    idleState->BindAction(Action::Ignore(), EventType::Collision);

    auto moveState = stateMachine.RegisterState<MoveState>();
    moveState->BindAction(Action::ChangeTo(StateType::Idle), EventType::StopMove);
    moveState->BindAction(Action::Ignore(), EventType::StartMove);
    moveState->BindAction(Action::Ignore(), EventType::Attack);
    moveState->BindAction(Action::Ignore(), EventType::AttackWeapon);

    auto condition = [](std::shared_ptr<Shape> shape) { return shape->AnimationIsCompleted(); };

    auto attackState = stateMachine.RegisterState<AttackState>();
    attackState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    attackState->BindAction(Action::Ignore(), EventType::Attack);
    attackState->BindAction(Action::Ignore(), EventType::AttackWeapon);
    attackState->BindActionDuringUpdate(Action::ChangeTo(StateType::Idle), condition);

    auto attackWeaponState = stateMachine.RegisterState<AttackWeaponState>();
    attackWeaponState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    attackWeaponState->BindAction(Action::Ignore(), EventType::Attack);
    attackWeaponState->BindAction(Action::Ignore(), EventType::AttackWeapon);
    attackWeaponState->BindActionDuringUpdate(Action::ChangeTo(StateType::Idle), condition);
}

void PlayerEntity::RegisterProperties(EntityService& entityService)
{
    entityService.RegisterProperty<float>("Rotation", 0.0);
    entityService.RegisterProperty<float>("Scale", 1.0);
    entityService.RegisterProperty<sf::Vector2f>("Position", {0.0, 0.0});
    entityService.RegisterProperty<float>("Velocity", constant::Entity::stdVelocity);
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Down);
    entityService.RegisterProperty<std::vector<FaceDirection>>(
        "FaceDirections", {FaceDirection::Down, FaceDirection::Up, FaceDirection::Left, FaceDirection::Right});
}

void PlayerEntity::Start(EntityService& entityService)
{
    entityService.AddCamera();
}

void PlayerEntity::BuildAnimations(const EntityService& entityService, StateType stateType)
{
    auto directions = entityService.GetProperty<std::vector<FaceDirection>>("FaceDirections");
    auto stateData = animationDatas.at(stateType);
    auto& m = animations_[stateType];

    for (auto direction : directions) {
        m[direction] = entityService.MakeAnimation(stateData.at(direction));
    }
}

Animation PlayerEntity::GetAnimation(const EntityService& entityService, StateType stateType) const
{
    auto dir = entityService.GetProperty<FaceDirection>("FaceDirection");

    return animations_.at(stateType).at(dir);
}

void PlayerEntity::InitState(std::shared_ptr<BasicState> state, const std::vector<FaceDirection>& directions,
                             const EntityService& entityService)
{
    auto stateType = state->GetStateType();

    BuildAnimations(entityService, stateType);
    state->SetAnimationFn(
        [this, stateType](const EntityService& entityService) { return GetAnimation(entityService, stateType); });
}

void PlayerEntity::InitStates(const StateMachine& stateMachine, const EntityService& entityService,
                              const PropertyData& data)
{
    auto directions = entityService.GetProperty<std::vector<FaceDirection>>("FaceDirections");

    InitState(stateMachine.GetState(StateType::Idle), directions, entityService);
    InitState(stateMachine.GetState(StateType::Move), directions, entityService);
    InitState(stateMachine.GetState(StateType::Attack), directions, entityService);
    InitState(stateMachine.GetState(StateType::AttackWeapon), directions, entityService);
}

}  // namespace Entity

}  // namespace FA
