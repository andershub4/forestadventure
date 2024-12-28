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

#include "Id.h"
#include "Resource/TextureManager.h"

namespace FA {

namespace Shared {

class CameraViews;
class CameraView;
class SheetManager;
struct ImageData;
struct ColliderData;
struct ImageFrame;
struct ColliderFrame;
class MessageBus;
class Message;
enum class MessageType;
struct TextureRect;
template <class T>
class SequenceIf;
template <class T>
class AnimationIf;
struct EntityData;

}  // namespace Shared

namespace Entity {

class EntityDb;
class EntityLifeHandler;
class EntityIf;
class ObjIdTranslator;

class EntityService
{
public:
    EntityService(Shared::MessageBus &messageBus, const Shared::TextureManager &textureManager,
                  const Shared::SheetManager &sheetManager, const Shared::CameraViews &cameraViews,
                  const EntityDb &entityDb, EntityLifeHandler &entityLifeHandler,
                  const ObjIdTranslator &objIdTranslator);
    ~EntityService();

    std::shared_ptr<Shared::AnimationIf<Shared::ImageFrame>> CreateImageAnimation(
        const std::vector<Shared::ImageData> &images);
    std::shared_ptr<Shared::AnimationIf<Shared::ColliderFrame>> CreateColliderAnimation(
        const std::vector<Shared::ColliderData> &colliders);

    void SendMessage(std::shared_ptr<Shared::Message> msg);
    void AddSubscriber(const std::string &subscriber, const std::vector<Shared::MessageType> &messageTypes,
                       std::function<void(std::shared_ptr<Shared::Message>)> onMessage);

    void RemoveSubscriber(const std::string &subscriber, const std::vector<Shared::MessageType> &messageTypes);
    Shared::CameraView &GetCameraView() const;
    void AddToCreationPool(const Shared::EntityData &data);
    void AddToDeletionPool(EntityId id);
    EntityIf &GetEntity(EntityId id) const;
    EntityId ObjIdToEntityId(int objId) const;

private:
    Shared::MessageBus &messageBus_;
    const Shared::TextureManager &textureManager_;
    const Shared::SheetManager &sheetManager_;
    const Shared::CameraViews &cameraViews_;
    const EntityDb &entityDb_;
    EntityLifeHandler &entityLifeHandler_;
    const ObjIdTranslator &objIdTranslator_;

private:
    std::shared_ptr<Shared::SequenceIf<Shared::ImageFrame>> CreateSequence(
        const std::vector<Shared::ImageData> &images) const;
    std::shared_ptr<Shared::SequenceIf<Shared::ColliderFrame>> CreateSequence(
        const std::vector<Shared::ColliderData> &colliders) const;
    Shared::TextureRect MirrorX(const Shared::TextureRect &textureRect) const;
};

}  // namespace Entity

}  // namespace FA
