/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>

#include "Id.h"
#include "LayerType.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Entity {

class EntityDb;

class DrawHandler
{
public:
    DrawHandler(const EntityDb &entityDb);
    ~DrawHandler();

    void AddDrawable(EntityId id);
    void RemoveDrawable(EntityId id);
    void DrawTo(Graphic::RenderTargetIf &renderTarget) const;

private:
    struct DrawableInfo
    {
        LayerType layer_{};
        EntityId id_{};
    };

private:
    const EntityDb &entityDb_;
    std::map<std::string, DrawableInfo> drawables_;
};

}  // namespace Entity

}  // namespace FA
