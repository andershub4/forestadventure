/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Body.h"
#include "EntityService.h"
#include "Enum/EntityType.h"
#include "Fwd/SfmlFwd.h"
#include "Id.h"
#include "LayerType.h"
#include "PropertyStore.h"
#include "StateMachine.h"

namespace FA {

namespace Shared {

class Message;
enum class MessageType;

}  // namespace Shared

namespace Entity {

struct PropertyData;

class BasicEntity
{
public:
    BasicEntity(EntityId id, const EntityService& service);
    virtual ~BasicEntity();

    virtual EntityType Type() const = 0;
    virtual LayerType GetLayer() const = 0;

    void Create(const PropertyData& data);
    void Destroy();
    void Init();
    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);
    EntityId GetId() const { return id_; }

protected:
    PropertyStore propertyStore_;
    EntityService entityService_;
    Body body_;

protected:
    virtual std::vector<Shared::MessageType> Messages() const { return {}; }

    void HandleEvent(std::shared_ptr<BasicEvent> event);
    void ChangeStateTo(StateType stateType, std::shared_ptr<BasicEvent> event);
    std::shared_ptr<State> RegisterState(StateType stateType);
    void SendMessage(std::shared_ptr<Shared::Message> message);

private:
    EntityId id_ = InvalidEntityId;
    StateMachine stateMachine_;

private:
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
    {}
    virtual void RegisterProperties() {}
    virtual void ReadProperties(const std::unordered_map<std::string, std::string>& properties) {}
    virtual void Start() {}
    virtual void OnMessage(std::shared_ptr<Shared::Message> msg) {}
    virtual void OnBeginIdle() {}
    virtual void OnBeginDie() {}

    void Subscribe(const std::vector<Shared::MessageType>& messageTypes);
    void Unsubscribe(const std::vector<Shared::MessageType>& messageTypes);
    void RegisterUninitializedState();
    std::shared_ptr<State> RegisterDeadState();
};

}  // namespace Entity

}  // namespace FA
