/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "Fwd/SfmlFwd.h"

namespace FA {

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    void Add(const std::string& name, const std::string& path);
    const sf::Texture* Get(const std::string& name) const;

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures_;
};

}  // namespace FA
