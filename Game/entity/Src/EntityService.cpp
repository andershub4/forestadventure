/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <SFML/Graphics/Sprite.hpp>

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
#include "Resource/TextureManager.h"
#include "Resource/TextureRect.h"

namespace FA {

namespace Entity {

EntityService::EntityService(Shared::MessageBus& messageBus, const Shared::TextureManager& textureManager,
                             const Shared::SheetManager& sheetManager, const Shared::CameraManager& cameraManager,
                             EntityManager& entityManager)
    : messageBus_(messageBus)
    , textureManager_(textureManager)
    , sheetManager_(sheetManager)
    , cameraManager_(cameraManager)
    , entityManager_(entityManager)
{}

EntityService::~EntityService() = default;

Shared::Animation EntityService::MakeAnimation(const Shared::AnimationData& data) const
{
    float t = Constant::stdSwitchTime;
    auto sprite = std::make_shared<sf::Sprite>();
    Shared::Animation animation(sprite, data.locationData_.defaultIndex_, t);
    auto rects = sheetManager_.MakeRects(data);

    for (const auto& rect : rects) {
        const auto* texture = textureManager_.Get(rect.id_);
        animation.AddFrame({texture, {rect.position_.x, rect.position_.y, rect.size_.x, rect.size_.y}});
    }

    return animation;
}

Shared::Image EntityService::MakeImage(const Shared::ImageData& data) const
{
    auto rect = sheetManager_.MakeRect(data);
    const auto* texture = textureManager_.Get(rect.id_);
    auto sprite = std::make_shared<sf::Sprite>();

    return Shared::Image(sprite, {texture, {rect.position_.x, rect.position_.y, rect.size_.x, rect.size_.y}});
}

Shared::TextureRect EntityService::MakeRect(const Shared::ImageData& data) const
{
    return sheetManager_.MakeRect(data);
}

const sf::Texture* EntityService::GetTexture(Shared::ResourceId id) const
{
    return textureManager_.Get(id);
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
