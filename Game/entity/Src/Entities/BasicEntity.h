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
#include "Id.h"
#include "LayerType.h"
#include "PropertyData.h"
#include "PropertyStore.h"
#include "StateMachine.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Shared {

class Message;
enum class MessageType;
struct MapData;

}  // namespace Shared

namespace Entity {

class BasicEntity
{
public:
    BasicEntity(EntityId id, const PropertyData& data, const Shared::MapData& mapData, const EntityService& service);
    virtual ~BasicEntity();

    virtual EntityType Type() const = 0;
    virtual LayerType GetLayer() const = 0;

    void Destroy();
    void Init();
    void Update(float deltaTime);
    void DrawTo(Graphic::RenderTargetIf& renderTarget) const;
    bool Intersect(const BasicEntity& otherEntity) const;
    void HandleCollision(const BasicEntity& otherEntity) {}
    EntityId GetId() const { return id_; }

protected:
    PropertyStore propertyStore_;
    EntityService service_;
    Body body_{};
    sf::FloatRect mapRect_;

protected:
    virtual std::vector<Shared::MessageType> Messages() const { return {}; }

    void HandleEvent(std::shared_ptr<BasicEvent> event);
    void ChangeStateTo(StateType stateType, std::shared_ptr<BasicEvent> event);
    std::shared_ptr<State> RegisterState(StateType stateType);
    void SendMessage(std::shared_ptr<Shared::Message> message);

private:
    EntityId id_ = InvalidEntityId;
    const PropertyData data_;
    StateMachine stateMachine_;

private:
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
    {}
    virtual void RegisterProperties() {}
    virtual void ReadProperties(const std::unordered_map<std::string, std::string>& properties) {}
    virtual void OnMessage(std::shared_ptr<Shared::Message> msg) {}
    virtual void OnInit() {}
    virtual void OnBeginIdle() {}
    virtual void OnBeginDie() {}

    void InitCB();
    void DestroyCB();
    void Subscribe(const std::vector<Shared::MessageType>& messageTypes);
    void Unsubscribe(const std::vector<Shared::MessageType>& messageTypes);
    void RegisterUninitializedState();
    std::shared_ptr<State> RegisterDeadState();
};

}  // namespace Entity

}  // namespace FA
