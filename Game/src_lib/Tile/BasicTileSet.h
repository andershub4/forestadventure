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

struct Image
{
    sf::Vector2i size_;
    sf::IntRect uvRect_;
    const sf::Texture *texture_ = nullptr;
};

struct Animation
{
    struct Frame
    {
        sf::IntRect uvRect_;
        const sf::Texture *texture_ = nullptr;
        float switchTime_{};
    };

    std::vector<Frame> frames_;
};

struct Tile
{
    Image image_;
    Animation animation;
};

class BasicTileSet
{
public:
    BasicTileSet(SheetManager &sheetManager);
    virtual ~BasicTileSet();

    virtual void Load() = 0;
    virtual Tile GetTile(int id) const = 0;

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
