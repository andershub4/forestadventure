/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <tuple>

#include "Draw/Image.h"
#include "Enum/EntityType.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"

namespace FA {

class SheetManager;

struct ImageData
{
    std::string sheetId_;
    sf::Vector2u position_;
    float rotation_;
    FrameType frameType_;
    FaceDirection dir_;
};

class ImageDb
{
public:
    ImageDb(const SheetManager &sheetManager);
    void AddImage(EntityType entityType, const ImageData &data);
    Image GetImage(EntityType entityType, FrameType frameType, FaceDirection faceDir) const;

private:
    using Key = std::tuple<EntityType, FrameType, FaceDirection>;
    std::map<Key, Image> map_;
    const SheetManager &sheetManager_;

private:
    void AddImage(Key k, const Image &image);
};

}  // namespace FA
