/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "Frame.h"
#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class Image
{
public:
    Image(std::shared_ptr<sf::Sprite> sprite, const Frame &frame);
    Image() = default;

    void Update(float deltaTime);
    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float rot);
    void DrawTo(sf::RenderTarget &renderTarget);
    void Center();
    bool IsValid() const;

private:
    std::shared_ptr<sf::Sprite> sprite_;
    Frame frame_;
    bool isValid_ = false;
};

}  // namespace Shared

}  // namespace FA
