/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Body.h"
#include "EntityIf.h"
#include "EntityService.h"
#include "Id.h"
#include "LayerType.h"
#include "PropertyStore.h"
#include "Resource/EntityData.h"
#include "StateMachine.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Shared {

class Message;
enum class MessageType;

}  // namespace Shared

namespace Entity {

class BasicEntity : public EntityIf
{
public:
    BasicEntity(EntityId id, const Shared::EntityData& data, std::unique_ptr<EntityService> service);
    virtual ~BasicEntity();

    void Destroy() final;
    void Init() final;
    void Update(float deltaTime) final;
    void DrawTo(Graphic::RenderTargetIf& renderTarget) const final;
    bool Intersect(const EntityIf& otherEntity) const final;
    bool IsOutsideTileMap(const sf::FloatRect& rect) const final;
    void HandleCollision(const EntityId id) final;
    void HandleOutsideTileMap() final;
    EntityId GetId() const final { return id_; }

protected:
    PropertyStore propertyStore_;
    std::unique_ptr<EntityService> service_;
    Body body_{};

protected:
    virtual std::vector<Shared::MessageType> Messages() const { return {}; }

    void HandleEvent(std::shared_ptr<BasicEvent> event);
    void ChangeStateTo(StateType stateType, std::shared_ptr<BasicEvent> event);
    std::shared_ptr<State> RegisterState(StateType stateType);
    void SendMessage(std::shared_ptr<Shared::Message> message);

    template <class T>
    void GetProperty(const BasicEntity& entity, const std::string& name, T& value) const
    {
        entity.propertyStore_.Get(name, value);
    }

    sf::Vector2f GetPosition(const BasicEntity& entity) const { return entity.body_.position_; }

private:
    EntityId id_ = InvalidEntityId;
    const Shared::EntityData data_;
    StateMachine stateMachine_;

private:
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const Shared::EntityData& data)
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
