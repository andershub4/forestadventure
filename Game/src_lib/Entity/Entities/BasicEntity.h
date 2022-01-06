/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Entity/EntityService.h"
#include "Entity/Id.h"
#include "Entity/ModeController.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Keyboard {
enum class Key;
}

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
                EntityManager& entityManager, MessageBus& messageBus);
    virtual ~BasicEntity();

    virtual std::string Name() const = 0;
    virtual EntityType Type() const = 0;

    void Create(const PropertyData& data);
    void Destroy();
    void Init();
    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);
    void QueueInitEvents(std::shared_ptr<BasicEvent> event);
    void EnableInput(bool enable) { enableInput_ = enable; }
    EntityId GetId() const { return id_; }

protected:
    virtual void HandleIsKeyPressed(Keyboard::Key key) {}
    virtual void HandleIsKeyReleased(Keyboard::Key key) {}
    virtual void HandleKeyPressed(Keyboard::Key key) {}
    virtual std::vector<MessageType> Messages() const { return {}; }
    virtual std::vector<AnimationData> Animations() const { return {}; }
    virtual std::vector<ImageData> Images() const { return {}; }

    void HandleEvent(std::shared_ptr<BasicEvent> event);

private:
    EntityId id_ = InvalidEntityId;
    MessageBus& messageBus_;
    EntityService entityService_;
    ModeController modeController_;
    bool enableInput_ = true;

private:
    virtual void DefineProperties(EntityService& entityService, const PropertyData& data) {}
    virtual void DefineModes(ModeController& modeController) {}
    virtual void DefineShape(EntityService& entityService, Shape& shape) {}

    void OnCreate(std::shared_ptr<BasicEvent> event);
    void OnDestroy(std::shared_ptr<BasicEvent> event);
    void Subscribe(const std::vector<MessageType>& messageTypes);
    void Unsubscribe(const std::vector<MessageType>& messageTypes);
    void OnMessage(std::shared_ptr<Message> msg);
    void HandleMessage(std::shared_ptr<Message> msg);
};

}  // namespace Entity

}  // namespace FA
