/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Id.h"
#include "Resource/EntityData.h"
#include "SfmlFwd.h"

namespace FA {

namespace Entity {

class EntityLifeHandler
{
public:
    ~EntityLifeHandler();

    void AddToCreationPool(const Shared::EntityData &data);
    void AddToDeletionPool(EntityId id);
    std::vector<Shared::EntityData> &&MoveCreationPool();
    std::unordered_set<EntityId> &&MoveDeletionPool();

private:
    std::vector<Shared::EntityData> creationPool_;
    std::unordered_set<EntityId> deletionPool_;
};

}  // namespace Entity

}  // namespace FA
