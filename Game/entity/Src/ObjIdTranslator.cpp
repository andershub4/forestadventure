/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ObjIdTranslator.h"

#include "Logging.h"

namespace FA {

namespace Entity {

ObjIdTranslator::~ObjIdTranslator() = default;

void ObjIdTranslator::Add(EntityId entityId, int objId)
{
    translationMap_[entityId] = objId;
}

void ObjIdTranslator::Remove(EntityId id)
{
    translationMap_.erase(id);
}

EntityId ObjIdTranslator::ObjIdToEntityId(int objId) const
{
    EntityId result = InvalidEntityId;

    auto it = std::find_if(translationMap_.begin(), translationMap_.end(),
                           [objId](const auto &p) { return p.second == objId; });
    if (it != translationMap_.end()) {
        result = it->first;
    }
    else {
        LOG_ERROR("%s does not exist", DUMP(objId));
    }

    return result;
}

}  // namespace Entity

}  // namespace FA
