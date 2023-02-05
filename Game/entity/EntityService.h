/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Enum/EntityType.h"
#include "Id.h"
#include "MapData.h"

namespace FA {

namespace Shared {

class CameraManager;
class Camera;
class Animation;
class Image;
class SheetManager;
struct AnimationData;
struct ImageData;
class MessageBus;
class Message;
enum class MessageType;

}  // namespace Shared

namespace Entity {

struct PropertyData;
class EntityManager;

class EntityService
{
public:
    EntityService(Shared::MessageBus &messageBus, const Shared::SheetManager &sheetManager,
                  const Shared::CameraManager &cameraManager, EntityManager &entityManager,
                  const Shared::MapData &mapData);
    ~EntityService();

    Shared::Animation MakeAnimation(const Shared::AnimationData &data) const;
    Shared::Image MakeImage(const Shared::ImageData &data) const;

    void SendMessage(std::shared_ptr<Shared::Message> msg);
    void AddSubscriber(const std::string &subscriber, const std::vector<Shared::MessageType> &messageTypes,
                       std::function<void(std::shared_ptr<Shared::Message>)> onMessage);

    void RemoveSubscriber(const std::string &subscriber, const std::vector<Shared::MessageType> &messageTypes);
    Shared::Camera &GetCamera() const;
    bool IsInsideMap(const sf::Vector2f &pos) const;
    void CreateEntity(const PropertyData &data);
    void DeleteEntity(EntityId id);

private:
    Shared::MessageBus &messageBus_;
    const Shared::SheetManager &sheetManager_;
    const Shared::CameraManager &cameraManager_;
    EntityManager &entityManager_;
    Shared::MapData mapData_;
};

}  // namespace Entity

}  // namespace FA
