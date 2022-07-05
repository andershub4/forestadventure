/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Entity/EntityService.h"
#include "Entity/Id.h"
#include "Entity/LayerType.h"
#include "Entity/PropertyManager.h"
#include "Entity/Shape.h"
#include "Entity/StateMachine.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class MessageBus;
class Message;
enum class MessageType;
class CameraManager;
class SheetManager;

namespace Entity {

struct PropertyData;
class EntityManager;

class BasicEntity
{
public:
    BasicEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                EntityManager& entityManager, MessageBus& messageBus, const sf::Vector2u& mapSize);
    virtual ~BasicEntity();

    virtual std::string Name() const = 0;
    virtual EntityType Type() const = 0;
    virtual LayerType GetLayer() const = 0;

    void Create(const PropertyData& data);
    void Destroy();
    void Init();
    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);
    void QueueInitEvents(std::shared_ptr<BasicEvent> event);
    EntityId GetId() const { return id_; }

protected:
    PropertyManager propertyManager_;
    EntityService entityService_;
    Shape shape_;
    sf::Vector2f position_;
    float rotation_{0.0};

protected:
    virtual std::vector<MessageType> Messages() const { return {}; }

    void HandleEvent(std::shared_ptr<BasicEvent> event);
    void ChangeState(StateType stateType, std::shared_ptr<BasicEvent> event);
    Shape CreateShape();
    std::shared_ptr<State> RegisterState(StateType stateType, bool startState = false);
    void SendMessage(std::shared_ptr<Message> message);

private:
    EntityId id_ = InvalidEntityId;
    MessageBus& messageBus_;
    StateMachine stateMachine_;

private:
    virtual void RegisterStates(const PropertyData& data) {}
    virtual void RegisterProperties() {}
    virtual void RegisterShape() {}
    virtual void Start() {}
    virtual void OnMessage(std::shared_ptr<Message> msg) {}
    virtual void OnDying() {}

    void OnCreate(std::shared_ptr<BasicEvent> event);
    void OnDestroy(std::shared_ptr<BasicEvent> event);
    void OnUpdateShape();
    void Subscribe(const std::vector<MessageType>& messageTypes);
    void Unsubscribe(const std::vector<MessageType>& messageTypes);
    void RegisterDeadState();
};

}  // namespace Entity

}  // namespace FA
