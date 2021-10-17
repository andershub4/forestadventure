/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Entity/Id.h"
#include "Entity/EntityService.h"
#include "Entity/StateMachine.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class MessageBus;
class Message;
enum class MessageType;
class CameraManager;

namespace Keyboard {
enum class Key;
}

namespace Entity {

struct PropertyData;

class BasicEntity
{
public:
    BasicEntity(EntityId id, EntityType entityType, CameraManager& cameraManager, MessageBus& messageBus);
    virtual ~BasicEntity();

    virtual std::string Name() const = 0;
    virtual void OnCreate(EntityService& handler, const PropertyData& data) {}
    virtual void OnDestroy() {}
    virtual void OnInit(const AnimationDb& animationDb) {}

    void Create(const PropertyData& data);
    void Update(float deltaTime);
    void Awake();
    void LateUpdate();
    void DrawTo(sf::RenderTarget& renderTarget);
    void EnableInput(bool enable) { enableInput_ = enable; }
    EntityId GetId() const { return id_; }

protected:
    void InitStateData(const AnimationDb& animationDb);
    void Subscribe(const std::vector<MessageType>& messageTypes);
    void Unsubscribe(const std::vector<MessageType>& messageTypes);
    void StartMove(MoveDirection moveDir, FaceDirection faceDir);
    void StopMove();
    void Attack();
    void AttackWeapon();

    virtual void OnIsKeyPressed(Keyboard::Key key) {}
    virtual void OnIsKeyReleased(Keyboard::Key key) {}
    virtual void OnKeyPressed(Keyboard::Key key) {}

private:
    EntityId id_ = InvalidEntityId;
    MessageBus& messageBus_;
    BasicState::StateData stateData_;
    EntityService entityService_;
    StateMachine stateMachine_;
    bool enableInput_ = true;

private:
    void OnMessage(std::shared_ptr<Message> msg);
    void HandleMessage(std::shared_ptr<Message> msg);
};

}  // namespace Entity

}  // namespace FA
