/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>

#include "Id.h"

namespace FA {

namespace Entity {

class ObjIdTranslator
{
public:
    ~ObjIdTranslator();

    void Add(EntityId entityId, int objId);
    void Remove(EntityId id);
    EntityId ObjIdToEntityId(int objId) const;

private:
    std::unordered_map<EntityId, int> translationMap_;
};

}  // namespace Entity

}  // namespace FA
