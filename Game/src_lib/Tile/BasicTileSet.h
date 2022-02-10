/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "Fwd/SfmlFwd.h"
#include "Resource/FrameHandler.h"

namespace FA {

struct Frame;
class SheetManager;

namespace Tile {

struct FrameData;

class BasicTileSet
{
public:
    BasicTileSet(SheetManager &sheetManager);
    virtual ~BasicTileSet();

    virtual void Load() = 0;
    virtual FrameData GetFrameData(int id) const = 0;

protected:
    void LoadSheet(const std::string &filePath, const sf::Vector2u &size);
    Frame GetFrame(const sf::Vector2u &uvCoord) const;

private:
    SheetManager &sheetManager_;
    const FrameHandler frameHandler_;
    std::string name_;
};

}  // namespace Tile

}  // namespace FA
