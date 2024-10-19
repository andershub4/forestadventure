/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "DrawHandler.h"

#include <sstream>

#include "EntityIf.h"
#include "EntityDb.h"

namespace FA {

namespace Entity {

DrawHandler::DrawHandler(const EntityDb &entityDb)
    : entityDb_(entityDb)
{}

void DrawHandler::AddDrawable(EntityId id)
{
    const auto &entity = entityDb_.GetEntity(id);
    auto layer = entity.GetLayer();

    std::stringstream ss;
    int l = static_cast<int>(layer);
    ss << l << "_" << id;
    drawables_[ss.str()] = {layer, id};
}

void DrawHandler::RemoveDrawable(EntityId id)
{
    auto it = std::find_if(drawables_.begin(), drawables_.end(), [id](const auto &p) { return p.second.id_ == id; });
    if (it != drawables_.end()) {
        drawables_.erase(it);
    }
}

void DrawHandler::DrawTo(Graphic::RenderTargetIf &renderTarget) const
{
    for (auto p : drawables_) {
        auto id = p.second.id_;
        entityDb_.GetEntity(id).DrawTo(renderTarget);
    }
}

}  // namespace Entity

}  // namespace FA
