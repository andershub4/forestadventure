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

namespace FA {

class CameraManager;
class Camera;

namespace Shared {

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

class EntityService
{
public:
    EntityService(Shared::MessageBus &messageBus, const Shared::SheetManager &sheetManager,
                  const CameraManager &cameraManager);
    ~EntityService();

    Shared::Animation MakeAnimation(const Shared::AnimationData &data) const;
    Shared::Image MakeImage(const Shared::ImageData &data) const;

    void SendMessage(std::shared_ptr<Shared::Message> msg);
    void AddSubscriber(const std::string &subscriber, const std::vector<Shared::MessageType> &messageTypes,
                       std::function<void(std::shared_ptr<Shared::Message>)> onMessage);

    void RemoveSubscriber(const std::string &subscriber, const std::vector<Shared::MessageType> &messageTypes);
    Camera &GetCamera() const;

private:
    Shared::MessageBus &messageBus_;
    const Shared::SheetManager &sheetManager_;
    const CameraManager &cameraManager_;
};

}  // namespace Entity

}  // namespace FA
