/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Abilities/BasicAbility.h"
#include "Entity/Events/CreateEvent.h"
#include "Entity/Events/DestroyEvent.h"
#include "Entity/Events/InitEvent.h"
#include "Entity/Shape.h"
#include "Message/BroadcastMessage/EntityCreatedMessage.h"
#include "Message/BroadcastMessage/EntityDestroyedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

BasicEntity::BasicEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                         EntityManager& entityManager, MessageBus& messageBus)
    : id_(id)
    , messageBus_(messageBus)
    , entityService_(cameraManager, sheetManager, entityManager)
    , stateMachine_(*this, shape_)
{
    stateMachine_.RegisterCreateCB([this](std::shared_ptr<BasicEvent> event) { OnCreate(event); });
    stateMachine_.RegisterDestroyCB([this](std::shared_ptr<BasicEvent> event) { OnDestroy(event); });
}

BasicEntity::~BasicEntity() = default;

void BasicEntity::OnEnterAbility(const std::string& ability, std::shared_ptr<BasicEvent> event)
{
    auto a = abilities_[ability];
    a->Enter(event);
}

void BasicEntity::OnExitAbility(const std::string& ability)
{
    auto a = abilities_[ability];
    a->Exit();
}

void BasicEntity::OnUpdateAbility(const std::string& ability, float deltaTime)
{
    auto a = abilities_[ability];
    a->Update(deltaTime);
}

void BasicEntity::Create(const PropertyData& data)
{
    HandleEvent(std::make_shared<CreateEvent>(data));
}

void BasicEntity::Destroy()
{
    HandleEvent(std::make_shared<DestroyEvent>());
}

void BasicEntity::Init()
{
    HandleEvent(std::make_shared<InitEvent>());
    stateMachine_.HandleQueuedInitEvents();
}

void BasicEntity::Update(float deltaTime)
{
    stateMachine_.Update(deltaTime);
}

void BasicEntity::DrawTo(sf::RenderTarget& renderTarget)
{
    stateMachine_.DrawTo(renderTarget);
}

void BasicEntity::QueueInitEvents(std::shared_ptr<BasicEvent> event)
{
    stateMachine_.QueueInitEvents(event);
}

void BasicEntity::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    stateMachine_.HandleEvent(event);
}

void BasicEntity::ChangeState(StateType stateType, std::shared_ptr<BasicEvent> event)
{
    stateMachine_.ChangeStateTo(stateType, event);
}

void BasicEntity::RegisterAbility(const std::string& name, std::shared_ptr<BasicAbility> ability)
{
    abilities_[name] = ability;
}

void BasicEntity::RegisterAnimationSprite(const std::string& name, std::shared_ptr<AnimationSprite> sprite)
{
    shape_.RegisterAnimationSprite(name, sprite);
}

void BasicEntity::RegisterImageSprite(const std::string& name, std::shared_ptr<ImageSprite> sprite)
{
    shape_.RegisterImageSprite(name, sprite);
}

std::shared_ptr<BasicState> BasicEntity::RegisterState(StateType stateType, bool startState)
{
    return stateMachine_.RegisterState(stateType, startState);
}

void BasicEntity::OnCreate(std::shared_ptr<BasicEvent> event)
{
    auto c = std::dynamic_pointer_cast<CreateEvent>(event);
    auto data = c->data_;

    RegisterProperties();
    RegisterStates();

    // ReadObjectData
    propertyManager_.Set<sf::Vector2f>("Position", data.position_);

    for (const auto& p : data.properties_) {
        propertyManager_.ReadCustomProperty(p.first, p.second);
    }

    RegisterShape(data);
    RegisterAbilities();
    Subscribe(Messages());
    Start(entityService_);  // must do this after setting position
    messageBus_.SendMessage(std::make_shared<EntityCreatedMessage>());
}

void BasicEntity::OnDestroy(std::shared_ptr<BasicEvent> event)
{
    Unsubscribe(Messages());
    messageBus_.SendMessage(std::make_shared<EntityDestroyedMessage>());
}

void BasicEntity::Subscribe(const std::vector<MessageType>& messageTypes)
{
    messageBus_.AddSubscriber(Name(), messageTypes, [this](std::shared_ptr<Message> message) {
        if (enableInput_) OnMessage(message);
    });
}

void BasicEntity::Unsubscribe(const std::vector<MessageType>& messageTypes)
{
    messageBus_.RemoveSubscriber(Name(), messageTypes);
}

}  // namespace Entity

}  // namespace FA
