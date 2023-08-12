/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityService.h"

#include "Camera.h"
#include "CameraManager.h"
#include "Constant/Entity.h"
#include "EntityManager.h"
#include "Message/MessageBus.h"
#include "Resource/Animation.h"
#include "Resource/AnimationData.h"
#include "Resource/Image.h"
#include "Resource/ImageData.h"
#include "Resource/SheetManager.h"

namespace FA {

namespace Entity {

EntityService::EntityService(Shared::MessageBus& messageBus, const Shared::SheetManager& sheetManager,
                             const Shared::CameraManager& cameraManager, EntityManager& entityManager)
    : messageBus_(messageBus)
    , sheetManager_(sheetManager)
    , cameraManager_(cameraManager)
    , entityManager_(entityManager)
{}

EntityService::~EntityService() = default;

Shared::Animation EntityService::MakeAnimation(const Shared::AnimationData& data) const
{
    float t = Constant::stdSwitchTime;
    auto frames = sheetManager_.MakeFrames(data);
    return Shared::Animation(frames, data.locationData_.defaultIndex_, t);
}

Shared::Image EntityService::MakeImage(const Shared::ImageData& data) const
{
    auto frame = sheetManager_.MakeFrame(data);
    return Shared::Image(frame);
}

void EntityService::SendMessage(std::shared_ptr<Shared::Message> msg)
{
    messageBus_.SendMessage(msg);
}

void EntityService::AddSubscriber(const std::string& subscriber, const std::vector<Shared::MessageType>& messageTypes,
                                  std::function<void(std::shared_ptr<Shared::Message>)> onMessage)
{
    messageBus_.AddSubscriber(subscriber, messageTypes, onMessage);
}

void EntityService::RemoveSubscriber(const std::string& subscriber,
                                     const std::vector<Shared::MessageType>& messageTypes)
{
    messageBus_.RemoveSubscriber(subscriber, messageTypes);
}

Shared::Camera& EntityService::GetCamera() const
{
    return cameraManager_.GetCamera();
}

void EntityService::CreateEntity(const PropertyData& data, const Shared::MapData& mapData)
{
    entityManager_.CreateEntity(data, mapData);
}

void EntityService::DeleteEntity(EntityId id)
{
    entityManager_.DeleteEntity(id);
}

}  // namespace Entity

}  // namespace FA
