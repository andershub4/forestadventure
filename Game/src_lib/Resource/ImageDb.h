/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <string>
#include <tuple>

#include "Draw/Image.h"

namespace FA {

class SheetManager;

struct ImageData
{
    std::string key_;
    std::string sheetId_;
    sf::Vector2u position_;
    float rotation_;
};

class ImageDb
{
public:
    ImageDb(const SheetManager &sheetManager);
    void AddImage(const ImageData &data);
    Image GetImage(const std::string &k) const;

private:
    std::map<std::string, Image> map_;
    const SheetManager &sheetManager_;

private:
    void AddImage(const std::string &k, const Image &image);
};

}  // namespace FA
