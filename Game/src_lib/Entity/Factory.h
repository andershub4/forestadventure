/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "Enum/EntityType.h"
#include "Id.h"

namespace FA {

class MessageBus;
class CameraManager;
class AnimationDb;

namespace Entity {

class BasicEntity;

class Factory
{
public:
    Factory(MessageBus& messageBus);
    ~Factory();

    std::unique_ptr<BasicEntity> Create(EntityType type, CameraManager& cameraManager,
                                        const AnimationDb& animationDb) const;

private:
    mutable Entity::EntityId id_{0};
    MessageBus& messageBus_;
};

}  // namespace Entity

}  // namespace FA
