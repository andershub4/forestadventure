/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Entity/StateMachine.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class MessageBus;
class Message;
enum class MessageType;

namespace Keyboard {
enum class Key;
}

namespace Entity {

class BasicSprite;

class BasicEntity
{
public:
    BasicEntity(MessageBus& messageBus, std::unique_ptr<BasicSprite> sprite, FaceDirection faceDir, float speed);
    virtual ~BasicEntity();

    virtual std::string Name() const = 0;
    virtual void OnCreate() {}
    virtual void OnDestroy() {}

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);
    void EnableInput(bool enable) { enableInput_ = enable; }
    sf::Vector2f GetPosition() const;

protected:
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
    MessageBus& messageBus_;
    std::unique_ptr<BasicSprite> sprite_;
    StateMachine stateMachine_;
    bool enableInput_ = true;

private:
    void OnMessage(std::shared_ptr<Message> msg);
    void HandleMessage(std::shared_ptr<Message> msg);
};

}  // namespace Entity

}  // namespace FA
