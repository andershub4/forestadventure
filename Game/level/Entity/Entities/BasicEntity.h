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
#include "Enum/EntityType.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Shared {

class MessageBus;
class Message;
enum class MessageType;
class SheetManager;

}  // namespace Shared

class Level;

namespace Entity {

struct PropertyData;

class BasicEntity
{
public:
    BasicEntity(EntityId id, Level& level, const Shared::SheetManager& sheetManager, Shared::MessageBus& messageBus);
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
    Level& level_;
    Shape shape_;
    sf::Vector2f position_;
    float rotation_{0.0};

protected:
    virtual std::vector<Shared::MessageType> Messages() const { return {}; }

    void HandleEvent(std::shared_ptr<BasicEvent> event);
    void ChangeStateTo(StateType stateType, std::shared_ptr<BasicEvent> event);
    Shape CreateShape();
    std::shared_ptr<State> RegisterState(StateType stateType);
    void SendMessage(std::shared_ptr<Shared::Message> message);

private:
    EntityId id_ = InvalidEntityId;
    Shared::MessageBus& messageBus_;
    StateMachine stateMachine_;
    std::vector<std::shared_ptr<BasicEvent>> queuedInitEvents_;

private:
    virtual void RegisterStates(std::shared_ptr<State> idleState, const PropertyData& data) {}
    virtual void RegisterProperties() {}
    virtual void RegisterShape() {}
    virtual void Start() {}
    virtual void OnMessage(std::shared_ptr<Shared::Message> msg) {}
    virtual void OnDying() {}

    void OnUpdateShape();
    void Subscribe(const std::vector<Shared::MessageType>& messageTypes);
    void Unsubscribe(const std::vector<Shared::MessageType>& messageTypes);
    void RegisterUninitializedState();
    void RegisterDeadState();
};

}  // namespace Entity

}  // namespace FA
