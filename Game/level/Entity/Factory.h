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

class CameraManager;

namespace Shared {

class MessageBus;
class SheetManager;

}  // namespace Shared

class Level;

namespace Entity {

class BasicEntity;

class Factory
{
public:
    Factory(Shared::MessageBus& messageBus, const Shared::SheetManager& sheetManager,
            const CameraManager& cameraManager, Level& level);
    ~Factory();

    std::unique_ptr<BasicEntity> Create(EntityType type) const;

private:
    mutable Entity::EntityId id_{0};
    Shared::MessageBus& messageBus_;
    const Shared::SheetManager& sheetManager_;
    const CameraManager& cameraManager_;
    Level& level_;
};

}  // namespace Entity

}  // namespace FA
