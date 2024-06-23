/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityService.h"

#include "CameraView.h"
#include "CameraViews.h"
#include "Colliders/Collider.h"
#include "Constant/Entity.h"
#include "EntityManager.h"
#include "Enum/EntityType.h"
#include "Message/MessageBus.h"
#include "Resource/ColliderData.h"
#include "Resource/ColliderFrame.h"
#include "Resource/ImageData.h"
#include "Resource/SheetId.h"
#include "Resource/SheetItem.h"
#include "Resource/SheetManager.h"
#include "Resource/TextureManager.h"
#include "Resource/TextureRect.h"
#include "Sequence.h"
#include "Sprites/AnimationSprite.h"

namespace FA {

namespace Entity {

EntityService::EntityService(Shared::MessageBus& messageBus, const Shared::TextureManager& textureManager,
                             const Shared::SheetManager& sheetManager, const Shared::CameraViews& cameraViews,
                             EntityManager& entityManager)
    : messageBus_(messageBus)
    , textureManager_(textureManager)
    , sheetManager_(sheetManager)
    , cameraViews_(cameraViews)
    , entityManager_(entityManager)
{}

EntityService::~EntityService() = default;

Shared::AnimationSprite EntityService::MakeAnimation(const std::vector<Shared::ImageData>& data) const
{
    float t = Constant::stdSwitchTime;
    auto seq = std::make_shared<Shared::Sequence<Shared::Frame>>(t);
    Shared::AnimationSprite animation(seq);

    for (const auto& item : data) {
        auto textureRect = sheetManager_.GetTextureRect(item.sheetItem_);
        auto textureSize = sf::Vector2i(textureRect.rect_.width, textureRect.rect_.height);
        textureRect = item.mirror_ ? MirrorX(textureRect) : textureRect;
        const auto* texture = textureManager_.Get(textureRect.id_);
        sf::Vector2i center = textureSize / 2;
        animation.AddFrame({texture, textureRect.rect_, static_cast<sf::Vector2f>(center)});
    }

    return animation;
}

Shared::Collider EntityService::MakeCollider(const std::vector<Shared::ColliderData>& data) const
{
    float t = Constant::stdSwitchTime;
    auto seq = std::make_shared<Shared::Sequence<Shared::ColliderFrame>>(t);
    Shared::Collider collider(seq);

    for (const auto& item : data) {
        Shared::ColliderFrame frame{};
        sf::Vector2i colliderSize{};
        sf::Vector2i center{};

        if (item.sheetItem_.id_ == Shared::SheetId::Unknown) {
            colliderSize = {item.rect_.width, item.rect_.height};
            center = colliderSize / 2;
        }
        else {
            auto textureRect = sheetManager_.GetTextureRect(item.sheetItem_);
            sf::Vector2i spriteSize{textureRect.rect_.width, textureRect.rect_.height};
            colliderSize = spriteSize;

            if (item.rect_ != sf::IntRect{}) {
                colliderSize = {item.rect_.width, item.rect_.height};
            }
            center = spriteSize / 2;
            center.x -= item.rect_.left;
            center.y -= item.rect_.top;
        }

        frame = {static_cast<sf::Vector2f>(colliderSize), static_cast<sf::Vector2f>(center)};
        collider.AddRect(frame);
    }

    return collider;
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

Shared::CameraView& EntityService::GetCameraView() const
{
    return cameraViews_.GetCameraView();
}

void EntityService::CreateEntity(const PropertyData& data, const Shared::MapData& mapData)
{
    entityManager_.CreateEntity(data, mapData);
}

void EntityService::DeleteEntity(EntityId id)
{
    entityManager_.DeleteEntity(id);
}

EntityType EntityService::GetType(EntityId id) const
{
    return entityManager_.GetType(id);
}

Shared::TextureRect EntityService::MirrorX(const Shared::TextureRect& textureRect) const
{
    Shared::TextureRect mirrorRect = textureRect;
    mirrorRect.rect_.left = mirrorRect.rect_.left + mirrorRect.rect_.width;
    mirrorRect.rect_.width = -textureRect.rect_.width;

    return mirrorRect;
}

}  // namespace Entity

}  // namespace FA
