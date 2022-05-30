/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Entity/EntityService.h"
#include "Entity/Id.h"
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
class BasicAbility;
class Shape;
class AnimationSprite;
class ImageSprite;

class BasicEntity
{
public:
    BasicEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                EntityManager& entityManager, MessageBus& messageBus);
    virtual ~BasicEntity();

    virtual std::string Name() const = 0;
    virtual EntityType Type() const = 0;

    void OnEnterAbility(const std::string& ability, std::shared_ptr<BasicEvent> event);
    void OnExitAbility(const std::string& ability);
    void OnUpdateAbility(const std::string& ability, float deltaTime);

    void Create(const PropertyData& data);
    void Destroy();
    void Init();
    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);
    void QueueInitEvents(std::shared_ptr<BasicEvent> event);
    void EnableInput(bool enable) { enableInput_ = enable; }
    EntityId GetId() const { return id_; }

protected:
    PropertyManager propertyManager_;
    EntityService entityService_;

protected:
    virtual std::vector<MessageType> Messages() const { return {}; }

    void HandleEvent(std::shared_ptr<BasicEvent> event);
    void ChangeState(StateType stateType, std::shared_ptr<BasicEvent> event);
    void RegisterAbility(const std::string& name, std::shared_ptr<BasicAbility> ability);
    void RegisterAnimationSprite(const std::string& name, std::shared_ptr<AnimationSprite> sprite);
    void RegisterImageSprite(const std::string& name, std::shared_ptr<ImageSprite> sprite);
    std::shared_ptr<BasicState> RegisterState(StateType stateType, bool startState = false);

private:
    EntityId id_ = InvalidEntityId;
    MessageBus& messageBus_;
    std::unordered_map<std::string, std::shared_ptr<BasicAbility>> abilities_;
    bool enableInput_ = true;
    Shape shape_;
    StateMachine stateMachine_;

private:
    virtual void RegisterStates() {}
    virtual void RegisterProperties() {}
    virtual void RegisterShape(const PropertyData& data) {}
    virtual void RegisterAbilities() {}
    virtual void Start(EntityService& entityService) {}
    virtual void OnMessage(std::shared_ptr<Message> msg) {}

    void OnCreate(std::shared_ptr<BasicEvent> event);
    void OnDestroy(std::shared_ptr<BasicEvent> event);
    void Subscribe(const std::vector<MessageType>& messageTypes);
    void Unsubscribe(const std::vector<MessageType>& messageTypes);
};

}  // namespace Entity

}  // namespace FA
