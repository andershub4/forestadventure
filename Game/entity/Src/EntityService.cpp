/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityService.h"

#include "Animation/Animation.h"
#include "CameraView.h"
#include "CameraViews.h"
#include "Constant/Entity.h"
#include "Entities/BasicEntity.h"
#include "EntityDb.h"
#include "EntityLifeHandler.h"
#include "EntityType.h"
#include "Message/MessageBus.h"
#include "ObjIdTranslator.h"
#include "Resource/ColliderData.h"
#include "Resource/ColliderFrame.h"
#include "Resource/ImageData.h"
#include "Resource/ImageFrame.h"
#include "Resource/SheetId.h"
#include "Resource/SheetItem.h"
#include "Resource/SheetManager.h"
#include "Resource/TextureManager.h"
#include "Resource/TextureRect.h"
#include "Sequence.h"

namespace FA {

namespace Entity {

EntityService::EntityService(Shared::MessageBus& messageBus, const Shared::TextureManager& textureManager,
                             const Shared::SheetManager& sheetManager, const Shared::CameraViews& cameraViews,
                             const EntityDb& entityDb, EntityLifeHandler& entityLifeHandler,
                             const ObjIdTranslator& objIdTranslator)
    : messageBus_(messageBus)
    , textureManager_(textureManager)
    , sheetManager_(sheetManager)
    , cameraViews_(cameraViews)
    , entityDb_(entityDb)
    , entityLifeHandler_(entityLifeHandler)
    , objIdTranslator_(objIdTranslator)
{}

EntityService::~EntityService() = default;

std::shared_ptr<Shared::AnimationIf<Shared::ImageFrame>> EntityService::CreateImageAnimation(
    const std::vector<Shared::ImageData>& images)
{
    return std::make_shared<Shared::Animation<Shared::ImageFrame>>(CreateSequence(images));
}

std::shared_ptr<Shared::AnimationIf<Shared::ColliderFrame>> EntityService::CreateColliderAnimation(
    const std::vector<Shared::ColliderData>& colliders)
{
    return std::make_shared<Shared::Animation<Shared::ColliderFrame>>(CreateSequence(colliders));
}

std::shared_ptr<Shared::SequenceIf<Shared::ImageFrame>> EntityService::CreateSequence(
    const std::vector<Shared::ImageData>& images) const
{
    float t = Constant::stdSwitchTime;
    auto seq = std::make_shared<Shared::Sequence<Shared::ImageFrame>>(t);

    for (const auto& image : images) {
        auto textureRect = sheetManager_.GetTextureRect(image.sheetItem_);
        auto textureSize = sf::Vector2i(textureRect.rect_.width, textureRect.rect_.height);
        textureRect = image.mirror_ ? MirrorX(textureRect) : textureRect;
        const auto* texture = textureManager_.Get(textureRect.id_);
        sf::Vector2i center = textureSize / 2;
        seq->Add({texture, textureRect.rect_, static_cast<sf::Vector2f>(center)});
    }

    return seq;
}

std::shared_ptr<Shared::SequenceIf<Shared::ColliderFrame>> EntityService::CreateSequence(
    const std::vector<Shared::ColliderData>& colliders) const
{
    float t = Constant::stdSwitchTime;
    auto seq = std::make_shared<Shared::Sequence<Shared::ColliderFrame>>(t);

    for (const auto& collider : colliders) {
        Shared::ColliderFrame frame{};
        sf::Vector2i colliderSize{};
        sf::Vector2i center{};

        if (collider.sheetItem_.id_ == Shared::SheetId::Unknown) {
            colliderSize = {collider.rect_.width, collider.rect_.height};
            center = colliderSize / 2;
        }
        else {
            auto textureRect = sheetManager_.GetTextureRect(collider.sheetItem_);
            sf::Vector2i spriteSize{textureRect.rect_.width, textureRect.rect_.height};
            colliderSize = spriteSize;

            if (collider.rect_ != sf::IntRect{}) {
                colliderSize = {collider.rect_.width, collider.rect_.height};
            }
            center = spriteSize / 2;
            center.x -= collider.rect_.left;
            center.y -= collider.rect_.top;
        }

        frame = {static_cast<sf::Vector2f>(colliderSize), static_cast<sf::Vector2f>(center)};
        seq->Add(frame);
    }

    return seq;
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

void EntityService::AddToCreationPool(const Shared::EntityData& data)
{
    entityLifeHandler_.AddToCreationPool(data);
}

void EntityService::AddToDeletionPool(EntityId id)
{
    entityLifeHandler_.AddToDeletionPool(id);
}

EntityIf& EntityService::GetEntity(EntityId id) const
{
    return entityDb_.GetEntity(id);
}

EntityId EntityService::ObjIdToEntityId(int objId) const
{
    return objIdTranslator_.ObjIdToEntityId(objId);
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
