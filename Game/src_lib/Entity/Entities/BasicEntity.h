/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Entity/Id.h"
#include "Entity/StateMachine.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class MessageBus;
class TextureManager;
class Message;
enum class MessageType;

namespace Keyboard {
enum class Key;
}

namespace Entity {

class BasicEntity
{
public:
    BasicEntity(EntityId id, MessageBus& messageBus, const TextureManager& textureManager);
    virtual ~BasicEntity();

    virtual std::string Name() const = 0;
    virtual void OnCreate(const Configuration& configuration) {}
    virtual void OnDestroy() {}

    void Update(float deltaTime);
    void LateUpdate();
    void DrawTo(sf::RenderTarget& renderTarget);
    void EnableInput(bool enable) { enableInput_ = enable; }
    sf::Vector2f GetPosition() const;
    EntityId GetId() const { return id_; }

protected:
    void InitStateData(const Configuration& configuration, const AnimationComponent& animation);
    void Subscribe(const std::vector<MessageType>& messageTypes);
    void Unsubscribe(const std::vector<MessageType>& messageTypes);
    void StartMove(MoveDirection moveDir, FaceDirection faceDir);
    void StopMove();
    void Attack();
    void AttackWeapon();
    const sf::Texture* GetTexture(const std::string& name) const;

    virtual void OnIsKeyPressed(Keyboard::Key key) {}
    virtual void OnIsKeyReleased(Keyboard::Key key) {}
    virtual void OnKeyPressed(Keyboard::Key key) {}

private:
    EntityId id_ = InvalidEntityId;
    MessageBus& messageBus_;
    const TextureManager& textureManager_;
    BasicState::StateData stateData_;
    StateMachine stateMachine_;
    bool enableInput_ = true;

private:
    void OnMessage(std::shared_ptr<Message> msg);
    void HandleMessage(std::shared_ptr<Message> msg);
};

}  // namespace Entity

}  // namespace FA
